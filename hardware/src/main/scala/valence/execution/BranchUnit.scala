package valence.execution

import chisel3._
import chisel3.util._

object BranchUnit {
  val BEQ  = 0
  val BNE  = 1
  val BLT  = 2
  val BGE  = 3
  val BLTU = 4
  val BGEU = 5
}

class BranchUnit(xlen: Int) extends Module {
  val io = IO(new Bundle {
    val op     = Input(UInt(3.W))
    val rs1    = Input(UInt(xlen.W))
    val rs2    = Input(UInt(xlen.W))
    val pc     = Input(UInt(xlen.W))
    val imm    = Input(UInt(xlen.W))
    val taken  = Output(Bool())
    val target = Output(UInt(xlen.W))
  })

  // branch target is always pc + imm
  io.target := io.pc + io.imm

  // signed comparison
  val s1 = io.rs1.asSInt
  val s2 = io.rs2.asSInt

  io.taken := MuxLookup(io.op, false.B)(Seq(
    BranchUnit.BEQ.U  -> (io.rs1 === io.rs2),
    BranchUnit.BNE.U  -> (io.rs1 =/= io.rs2),
    BranchUnit.BLT.U  -> (s1 < s2),
    BranchUnit.BGE.U  -> (s1 >= s2),
    BranchUnit.BLTU.U -> (io.rs1 < io.rs2),
    BranchUnit.BGEU.U -> (io.rs1 >= io.rs2),
  ))
}