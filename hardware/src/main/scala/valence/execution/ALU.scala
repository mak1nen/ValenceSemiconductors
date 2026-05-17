package valence.execution

import chisel3._
import chisel3.util._

object ALU {
  val ADD  = 0
  val SUB  = 1
  val AND  = 2
  val OR   = 3
  val XOR  = 4
  val SLL  = 5
  val SRL  = 6
  val SRA  = 7
  val SLT  = 8
  val SLTU = 9
}

class ALU(xlen: Int) extends Module {
  val io = IO(new Bundle {
    val op     = Input(UInt(4.W))
    val rs1    = Input(UInt(xlen.W))
    val rs2    = Input(UInt(xlen.W))
    val result = Output(UInt(xlen.W))
    val zero   = Output(Bool())
  })

  val shamt = io.rs2(log2Ceil(xlen) - 1, 0)

  io.result := MuxLookup(io.op, 0.U)(Seq(
    ALU.ADD.U  -> (io.rs1 + io.rs2),
    ALU.SUB.U  -> (io.rs1 - io.rs2),
    ALU.AND.U  -> (io.rs1 & io.rs2),
    ALU.OR.U   -> (io.rs1 | io.rs2),
    ALU.XOR.U  -> (io.rs1 ^ io.rs2),
    ALU.SLL.U  -> (io.rs1 << shamt)(xlen - 1, 0),
    ALU.SRL.U  -> (io.rs1 >> shamt),
    ALU.SRA.U  -> (io.rs1.asSInt >> shamt).asUInt,
    ALU.SLT.U  -> (io.rs1.asSInt < io.rs2.asSInt).asUInt,
    ALU.SLTU.U -> (io.rs1 < io.rs2).asUInt,
  ))

  io.zero := io.result === 0.U
}