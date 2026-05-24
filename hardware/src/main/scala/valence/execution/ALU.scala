package valence.execution

import chisel3._
import chisel3.util._

object ALU {
  // 64-bit ops
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

  // 32-bit W ops (RV64I): operate on low 32 bits, sign-extend bit 31 to xlen
  val ADDW = 10
  val SUBW = 11
  val SLLW = 12
  val SRLW = 13
  val SRAW = 14
}

class ALU(xlen: Int) extends Module {
  require(xlen == 64, "ALU W-ops assume xlen == 64")

  val io = IO(new Bundle {
    val op     = Input(UInt(5.W))
    val rs1    = Input(UInt(xlen.W))
    val rs2    = Input(UInt(xlen.W))
    val result = Output(UInt(xlen.W))
    val zero   = Output(Bool())
  })

  // ---- 64-bit shift amount: low 6 bits of rs2 ----
  val shamt64 = io.rs2(log2Ceil(xlen) - 1, 0)

  // ---- 32-bit operands and shamt for W-ops ----
  val rs1w   = io.rs1(31, 0)
  val rs2w   = io.rs2(31, 0)
  val shamt5 = io.rs2(4, 0)            // SLLW/SRLW/SRAW: low 5 bits only

  // ---- W-op raw 32-bit results ----
  val addw32 = (rs1w + rs2w)(31, 0)
  val subw32 = (rs1w - rs2w)(31, 0)
  val sllw32 = (rs1w << shamt5)(31, 0)
  val srlw32 = rs1w >> shamt5
  val sraw32 = (rs1w.asSInt >> shamt5).asUInt(31, 0)

  // Sign-extend bit 31 of a 32-bit result to xlen.
  def sext32(x: UInt): UInt = x.asSInt.pad(xlen).asUInt

  io.result := MuxLookup(io.op, 0.U)(Seq(
    ALU.ADD.U  -> (io.rs1 + io.rs2),
    ALU.SUB.U  -> (io.rs1 - io.rs2),
    ALU.AND.U  -> (io.rs1 & io.rs2),
    ALU.OR.U   -> (io.rs1 | io.rs2),
    ALU.XOR.U  -> (io.rs1 ^ io.rs2),
    ALU.SLL.U  -> (io.rs1 << shamt64)(xlen - 1, 0),
    ALU.SRL.U  -> (io.rs1 >> shamt64),
    ALU.SRA.U  -> (io.rs1.asSInt >> shamt64).asUInt,
    ALU.SLT.U  -> (io.rs1.asSInt < io.rs2.asSInt).asUInt,
    ALU.SLTU.U -> (io.rs1 < io.rs2).asUInt,

    ALU.ADDW.U -> sext32(addw32),
    ALU.SUBW.U -> sext32(subw32),
    ALU.SLLW.U -> sext32(sllw32),
    ALU.SRLW.U -> sext32(srlw32),
    ALU.SRAW.U -> sext32(sraw32),
  ))

  io.zero := io.result === 0.U
}