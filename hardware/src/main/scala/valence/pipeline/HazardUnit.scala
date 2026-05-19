package valence.pipeline

import chisel3._
import chisel3.util._

// HazardUnit — detects pipeline hazards and generates stall/flush signals
//
// Hazards handled:
//
// 1. EX-stage load-use:
//      load rd, ...
//      use  rd immediately in following instruction
//
// 2. MEM-stage load-use:
//      load result is in/near memory stage and may not yet be safely
//      visible to decode/register-read for consumers such as jalr/ret,
//      stores, branches, and ALU ops.
//
// 3. Branch/jump redirect:
//      flush wrong-path frontend/decode state.

class HazardUnit extends Module {
  val io = IO(new Bundle {
    // from ID stage — source registers of current instruction
    val id_rs1 = Input(UInt(5.W))
    val id_rs2 = Input(UInt(5.W))

    // from EX stage — destination + type of instruction in EX
    val ex_rd      = Input(UInt(5.W))
    val ex_is_load = Input(Bool())

    // from MEM stage — destination + type of instruction in MEM
    val mem_rd      = Input(UInt(5.W))
    val mem_wen     = Input(Bool())
    val mem_is_load = Input(Bool())

    // from branch unit
    val branch_taken = Input(Bool())

    // outputs
    val stall = Output(Bool())
    val flush = Output(Bool())
  })

  val ex_load_use_rs1 =
    io.ex_is_load &&
    io.ex_rd =/= 0.U &&
    io.ex_rd === io.id_rs1

  val ex_load_use_rs2 =
    io.ex_is_load &&
    io.ex_rd =/= 0.U &&
    io.ex_rd === io.id_rs2

  val mem_load_use_rs1 =
    io.mem_is_load &&
    io.mem_rd =/= 0.U &&
    io.mem_rd === io.id_rs1

  val mem_load_use_rs2 =
    io.mem_is_load &&
    io.mem_rd =/= 0.U &&
    io.mem_rd === io.id_rs2

  val load_use_hazard =
    ex_load_use_rs1 || ex_load_use_rs2 ||
    mem_load_use_rs1 || mem_load_use_rs2

  io.flush := io.branch_taken

  // If a branch/jump is redirecting, flushing wins over stalling.
  io.stall := load_use_hazard && !io.branch_taken
}