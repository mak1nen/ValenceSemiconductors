package valence.pipeline

import chisel3._
import chisel3.util._

// HazardUnit — detects pipeline hazards and generates stall/flush signals
//
// Two hazard types:
//
// 1. Load-use hazard:
//    LOAD r1, 0(r2)   ← EX stage (is_load=true, rd=r1)
//    ADD  r3, r1, r4  ← ID stage (needs r1)
//    Data not available until end of MEM stage
//    Cannot be resolved by forwarding alone
//    → stall pipeline for one cycle
//
// 2. Branch taken:
//    Instructions fetched after branch are wrong
//    → flush IF and ID stage registers

class HazardUnit extends Module {
  val io = IO(new Bundle {
    // from ID stage — source registers of current instruction
    val id_rs1      = Input(UInt(5.W))
    val id_rs2      = Input(UInt(5.W))

    // from EX stage — destination + type of instruction in EX
    val ex_rd       = Input(UInt(5.W))
    val ex_is_load  = Input(Bool())

    // from MEM stage
    val mem_rd      = Input(UInt(5.W))
    val mem_wen     = Input(Bool())

    // from branch unit
    val branch_taken = Input(Bool())

    // outputs
    val stall       = Output(Bool())
    val flush       = Output(Bool())
  })

  // load-use hazard detection
  // stall if EX is a load AND it writes to a register
  // that the current ID instruction needs
  val load_use_rs1 = io.ex_is_load &&
                     io.ex_rd =/= 0.U &&
                     io.ex_rd === io.id_rs1

  val load_use_rs2 = io.ex_is_load &&
                     io.ex_rd =/= 0.U &&
                     io.ex_rd === io.id_rs2

  val load_use_hazard = load_use_rs1 || load_use_rs2

  // flush on branch taken — kill wrongly fetched instructions
  io.flush := io.branch_taken

  // stall on load-use — but not if we are also flushing
  io.stall := load_use_hazard && !io.branch_taken
}