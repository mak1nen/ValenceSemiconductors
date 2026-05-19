package valence.pipeline

import chisel3._
import chisel3.util._

// =============================================================================
// ForwardingUnit — resolves RAW hazards without stalling
//
// Forwards results from later pipeline stages back to the ID/EX input
// so dependent instructions don't read stale register file values.
//
// Three forwarding paths (priority: EX > MEM > WB):
//
//   EX forwarding  (FWD_EX):
//     Instruction in EX stage just computed a result.
//     Forward directly to the next instruction entering EX.
//     Covers 1-cycle gaps:
//       addi sp, sp, -16   ← EX (result ready this cycle)
//       sd   ra, 8(sp)     ← ID (needs sp)
//
//   MEM forwarding (FWD_MEM):
//     Instruction passed through EX, result in EX/MEM register.
//     Covers 2-cycle gaps.
//
//   WB forwarding  (FWD_WB):
//     Instruction in MEM/WB stage, about to write back.
//     Covers 3-cycle gaps.
//
// Load-use hazards (1-cycle gap after a load) cannot be forwarded —
// the HazardUnit inserts a stall bubble instead.
//
// Forward select encoding:
//   NO_FWD  = 0 → use register file output
//   FWD_EX  = 1 → use EX stage result
//   FWD_MEM = 2 → use MEM stage result
//   FWD_WB  = 3 → use WB stage result
// =============================================================================

object ForwardingUnit {
  val NO_FWD  = 0
  val FWD_EX  = 1
  val FWD_MEM = 2
  val FWD_WB  = 3
}

class ForwardingUnit extends Module {
  val io = IO(new Bundle {
    // source registers of instruction currently in ID (about to enter EX)
    val ex_rs1  = Input(UInt(5.W))
    val ex_rs2  = Input(UInt(5.W))

    // EX stage destination (id_ex register output)
    val ex_rd   = Input(UInt(5.W))
    val ex_wen  = Input(Bool())

    // MEM stage destination (ex_mem register output)
    val mem_rd  = Input(UInt(5.W))
    val mem_wen = Input(Bool())

    // WB stage destination (mem_wb register output)
    val wb_rd   = Input(UInt(5.W))
    val wb_wen  = Input(Bool())

    // forward select for ALU inputs A and B
    val fwd_a   = Output(UInt(2.W))
    val fwd_b   = Output(UInt(2.W))
  })

  // forward A (rs1) — EX takes priority over MEM over WB
  io.fwd_a := MuxCase(ForwardingUnit.NO_FWD.U, Seq(
    (io.ex_wen  && io.ex_rd  =/= 0.U && io.ex_rd  === io.ex_rs1) -> ForwardingUnit.FWD_EX.U,
    (io.mem_wen && io.mem_rd =/= 0.U && io.mem_rd === io.ex_rs1) -> ForwardingUnit.FWD_MEM.U,
    (io.wb_wen  && io.wb_rd  =/= 0.U && io.wb_rd  === io.ex_rs1) -> ForwardingUnit.FWD_WB.U,
  ))

  // forward B (rs2)
  io.fwd_b := MuxCase(ForwardingUnit.NO_FWD.U, Seq(
    (io.ex_wen  && io.ex_rd  =/= 0.U && io.ex_rd  === io.ex_rs2) -> ForwardingUnit.FWD_EX.U,
    (io.mem_wen && io.mem_rd =/= 0.U && io.mem_rd === io.ex_rs2) -> ForwardingUnit.FWD_MEM.U,
    (io.wb_wen  && io.wb_rd  =/= 0.U && io.wb_rd  === io.ex_rs2) -> ForwardingUnit.FWD_WB.U,
  ))
}