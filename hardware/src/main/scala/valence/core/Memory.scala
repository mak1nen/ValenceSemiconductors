package valence.core

import chisel3._
import chisel3.util._

class MemoryIn extends Bundle {
  val result       = UInt(64.W)
  val rd           = UInt(5.W)
  val rs2_val      = UInt(64.W)
  val isLoad       = Bool()
  val isStore      = Bool()
  val valid        = Bool()
}

class MemoryOut extends Bundle {
  val result  = UInt(64.W)
  val rd      = UInt(5.W)
  val valid   = Bool()
}

class Memory extends Module {
  val io = IO(new Bundle {
    val in    = Input(new MemoryIn)
    val out   = Output(new MemoryOut)

    // DCache interface
    val dcache_addr  = Output(UInt(64.W))
    val dcache_wen   = Output(Bool())
    val dcache_wdata = Output(UInt(64.W))
    val dcache_valid = Output(Bool())
    val dcache_rdata = Input(UInt(64.W))
    val dcache_stall = Input(Bool())
  })

  io.dcache_addr  := io.in.result
  io.dcache_wen   := io.in.isStore
  io.dcache_wdata := io.in.rs2_val
  io.dcache_valid := (io.in.isLoad || io.in.isStore) && io.in.valid

  io.out.result := Mux(io.in.isLoad, io.dcache_rdata, io.in.result)
  io.out.rd     := io.in.rd
  io.out.valid  := io.in.valid && !io.dcache_stall
}