package valence.core

import chisel3._
import chisel3.util._

class MemoryIn extends Bundle {
  val result  = UInt(64.W) // effective address for loads/stores, ALU result otherwise
  val rd      = UInt(5.W)
  val rs2_val = UInt(64.W)
  val memOp   = UInt(3.W)  // LOAD/STORE funct3: width + signedness
  val isLoad  = Bool()
  val isStore = Bool()
  val valid   = Bool()
}

class MemoryOut extends Bundle {
  val result = UInt(64.W)
  val rd     = UInt(5.W)
  val valid  = Bool()
}

class Memory extends Module {
  val io = IO(new Bundle {
    val in  = Input(new MemoryIn)
    val out = Output(new MemoryOut)

    // DCache interface
    val dcache_addr  = Output(UInt(64.W))
    val dcache_wen   = Output(Bool())
    val dcache_wdata = Output(UInt(64.W))
    val dcache_wstrb = Output(UInt(8.W))
    val dcache_valid = Output(Bool())
    val dcache_rdata = Input(UInt(64.W))
    val dcache_stall = Input(Bool())
  })

  val byteOffset = io.in.result(2, 0)
  val bitShift   = byteOffset << 3

  // Store width from RISC-V STORE funct3:
  //   000 SB, 001 SH, 010 SW, 011 SD
  val storeMask = MuxLookup(io.in.memOp, 0.U(8.W))(Seq(
    "b000".U -> (1.U(8.W) << byteOffset),        // SB
    "b001".U -> (3.U(8.W) << byteOffset),        // SH
    "b010".U -> ("h0f".U(8.W) << byteOffset),    // SW
    "b011".U -> "hff".U(8.W)                     // SD
  ))

  val shiftedStoreData = io.in.rs2_val << bitShift

  // Load width/sign from RISC-V LOAD funct3:
  //   000 LB, 001 LH, 010 LW, 011 LD, 100 LBU, 101 LHU, 110 LWU
  val shiftedLoad = io.dcache_rdata >> bitShift
  val loadResult = MuxLookup(io.in.memOp, io.dcache_rdata)(Seq(
    "b000".U -> Cat(Fill(56, shiftedLoad(7)),  shiftedLoad(7, 0)),   // LB
    "b001".U -> Cat(Fill(48, shiftedLoad(15)), shiftedLoad(15, 0)),  // LH
    "b010".U -> Cat(Fill(32, shiftedLoad(31)), shiftedLoad(31, 0)),  // LW
    "b011".U -> shiftedLoad,                                         // LD
    "b100".U -> Cat(0.U(56.W), shiftedLoad(7, 0)),                   // LBU
    "b101".U -> Cat(0.U(48.W), shiftedLoad(15, 0)),                  // LHU
    "b110".U -> Cat(0.U(32.W), shiftedLoad(31, 0))                   // LWU
  ))

  io.dcache_addr  := io.in.result
  io.dcache_wen   := io.in.isStore
  io.dcache_wdata := shiftedStoreData
  io.dcache_wstrb := Mux(io.in.isStore, storeMask, 0.U(8.W))
  io.dcache_valid := (io.in.isLoad || io.in.isStore) && io.in.valid

  io.out.result := Mux(io.in.isLoad, loadResult, io.in.result)
  io.out.rd     := io.in.rd
  io.out.valid  := io.in.valid && !io.dcache_stall
}
