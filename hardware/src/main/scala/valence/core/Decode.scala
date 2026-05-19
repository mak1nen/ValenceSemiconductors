package valence.core

import chisel3._
import chisel3.util._
import valence.execution.ALU

// Instruction opcodes
object Opcode {
  val LUI    = "b0110111".U(7.W)
  val AUIPC  = "b0010111".U(7.W)
  val JAL    = "b1101111".U(7.W)
  val JALR   = "b1100111".U(7.W)
  val BRANCH = "b1100011".U(7.W)
  val LOAD   = "b0000011".U(7.W)
  val STORE  = "b0100011".U(7.W)
  val OP_IMM = "b0010011".U(7.W)
  val OP     = "b0110011".U(7.W)
  val SYSTEM = "b1110011".U(7.W)
  val FENCE  = "b0001111".U(7.W)
}

class DecodeOut extends Bundle {
  val rs1      = UInt(5.W)
  val rs2      = UInt(5.W)
  val rd       = UInt(5.W)
  val imm      = UInt(64.W)
  val aluOp    = UInt(4.W)
  val brOp     = UInt(3.W)
  val memOp    = UInt(3.W) // LOAD/STORE funct3: width + signedness
  val isLoad   = Bool()
  val isStore  = Bool()
  val isBranch = Bool()
  val isJal    = Bool()
  val isJalr   = Bool()
  val isLui    = Bool()
  val isAuipc  = Bool()
  val isCsr    = Bool()
  val useImm   = Bool()
  val valid    = Bool()
}

class Decode extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val out   = Output(new DecodeOut)
  })

  val instr  = io.instr
  val opcode = instr(6, 0)
  val rd     = instr(11, 7)
  val funct3 = instr(14, 12)
  val rs1    = instr(19, 15)
  val rs2    = instr(24, 20)
  val funct7 = instr(31, 25)

  // Immediate decode
  val immI = Cat(Fill(52, instr(31)), instr(31, 20))
  val immS = Cat(Fill(52, instr(31)), instr(31, 25), instr(11, 7))
  val immB = Cat(Fill(51, instr(31)), instr(31), instr(7), instr(30, 25), instr(11, 8), 0.U(1.W))
  val immU = Cat(Fill(32, instr(31)), instr(31, 12), 0.U(12.W))
  val immJ = Cat(Fill(43, instr(31)), instr(31), instr(19, 12), instr(20), instr(30, 21), 0.U(1.W))

  val writesRd =
    opcode === Opcode.LUI    ||
    opcode === Opcode.AUIPC  ||
    opcode === Opcode.JAL    ||
    opcode === Opcode.JALR   ||
    opcode === Opcode.LOAD   ||
    opcode === Opcode.OP_IMM ||
    opcode === Opcode.OP

  val out = io.out

  out.rs1      := rs1
  out.rs2      := rs2
  out.rd       := Mux(writesRd, rd, 0.U)
  out.memOp    := funct3

  out.isLoad   := opcode === Opcode.LOAD
  out.isStore  := opcode === Opcode.STORE
  out.isBranch := opcode === Opcode.BRANCH
  out.isJal    := opcode === Opcode.JAL
  out.isJalr   := opcode === Opcode.JALR
  out.isLui    := opcode === Opcode.LUI
  out.isAuipc  := opcode === Opcode.AUIPC
  out.isCsr    := opcode === Opcode.SYSTEM
  out.valid    := true.B

  // Immediate selection
  out.imm := MuxCase(immI, Seq(
    (opcode === Opcode.STORE)  -> immS,
    (opcode === Opcode.BRANCH) -> immB,
    (opcode === Opcode.LUI)    -> immU,
    (opcode === Opcode.AUIPC)  -> immU,
    (opcode === Opcode.JAL)    -> immJ
  ))

  // Use immediate for ALU?
  out.useImm := opcode === Opcode.OP_IMM ||
                opcode === Opcode.LOAD   ||
                opcode === Opcode.STORE  ||
                opcode === Opcode.JALR

  // ALU op decode
  out.aluOp := MuxCase(ALU.ADD.U, Seq(
    (opcode === Opcode.LUI)                                -> ALU.ADD.U,
    (opcode === Opcode.AUIPC)                              -> ALU.ADD.U,

    // SUB is only OP, not OP_IMM. OP_IMM funct3=000 is ADDI.
    ((opcode === Opcode.OP) &&
      funct3 === "b000".U && funct7 === "b0100000".U)      -> ALU.SUB.U,

    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b111".U)                                 -> ALU.AND.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b110".U)                                 -> ALU.OR.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b100".U)                                 -> ALU.XOR.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b001".U)                                 -> ALU.SLL.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b101".U && funct7 === "b0000000".U)      -> ALU.SRL.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b101".U && funct7 === "b0100000".U)      -> ALU.SRA.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b010".U)                                 -> ALU.SLT.U,
    ((opcode === Opcode.OP || opcode === Opcode.OP_IMM) &&
      funct3 === "b011".U)                                 -> ALU.SLTU.U
  ))

  // Branch op uses raw RISC-V funct3.
  out.brOp := funct3
}