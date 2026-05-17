package valence.pipeline

import chisel3._
import chisel3.util._

// ForwardingUnit — resolves RAW hazards without stalling
//
// When EX stage needs a value that hasn't been written back yet,
// forward it directly from the pipeline register that has it:
//
//   ADD r1, r2, r3   ← MEM stage (result ready)
//   ADD r4, r1, r5   ← EX  stage (needs r1)
//   → forward MEM result directly to ALU input A
//
// Priority: MEM forwarding > WB forwarding
// (MEM is more recent than WB)
//
// Forward select encoding:
//   NO_FWD = 0 → use register file output
//   FWD_MEM = 1 → use MEM stage result
//   FWD_WB  = 2 → use WB stage result

object ForwardingUnit {
  val NO_FWD  = 0
  val FWD_MEM = 1
  val FWD_WB  = 2
}

class ForwardingUnit extends Module {
  val io = IO(new Bundle {
    // source registers of instruction in EX stage
    val ex_rs1  = Input(UInt(5.W))
    val ex_rs2  = Input(UInt(5.W))

    // MEM stage destination
    val mem_rd  = Input(UInt(5.W))
    val mem_wen = Input(Bool())

    // WB stage destination
    val wb_rd   = Input(UInt(5.W))
    val wb_wen  = Input(Bool())

    // forward select for ALU inputs A and B
    val fwd_a   = Output(UInt(2.W))
    val fwd_b   = Output(UInt(2.W))
  })

  // forward A (rs1)
  io.fwd_a := MuxCase(ForwardingUnit.NO_FWD.U, Seq(
    // MEM takes priority — most recent result
    (io.mem_wen && io.mem_rd =/= 0.U &&
     io.mem_rd === io.ex_rs1)            -> ForwardingUnit.FWD_MEM.U,
    // WB next
    (io.wb_wen && io.wb_rd =/= 0.U &&
     io.wb_rd === io.ex_rs1)             -> ForwardingUnit.FWD_WB.U,
  ))

  // forward B (rs2)
  io.fwd_b := MuxCase(ForwardingUnit.NO_FWD.U, Seq(
    (io.mem_wen && io.mem_rd =/= 0.U &&
     io.mem_rd === io.ex_rs2)            -> ForwardingUnit.FWD_MEM.U,
    (io.wb_wen && io.wb_rd =/= 0.U &&
     io.wb_rd === io.ex_rs2)             -> ForwardingUnit.FWD_WB.U,
  ))
}