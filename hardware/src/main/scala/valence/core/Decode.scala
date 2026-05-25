package valence.core

import chisel3._
import chisel3.util._
import valence.execution.{ALU, MulDivOp}

// Instruction opcodes
object Opcode {
  val LUI        = "b0110111".U(7.W)
  val AUIPC      = "b0010111".U(7.W)
  val JAL        = "b1101111".U(7.W)
  val JALR       = "b1100111".U(7.W)
  val BRANCH     = "b1100011".U(7.W)
  val LOAD       = "b0000011".U(7.W)
  val STORE      = "b0100011".U(7.W)
  val OP_IMM     = "b0010011".U(7.W)
  val OP         = "b0110011".U(7.W)
  val OP_IMM_32  = "b0011011".U(7.W)  // ADDIW, SLLIW, SRLIW, SRAIW
  val OP_32      = "b0111011".U(7.W)  // ADDW, SUBW, SLLW, SRLW, SRAW, MULW, DIVW, ...
  val SYSTEM     = "b1110011".U(7.W)
  val FENCE      = "b0001111".U(7.W)
}

class DecodeOut extends Bundle {
  val rs1      = UInt(5.W)
  val rs2      = UInt(5.W)
  val rd       = UInt(5.W)
  val imm      = UInt(64.W)
  val aluOp    = UInt(5.W)
  val mulDivOp = UInt(5.W)
  val brOp     = UInt(3.W)
  val memOp    = UInt(3.W)
  val csrAddr  = UInt(12.W)

  val isLoad   = Bool()
  val isStore  = Bool()
  val isBranch = Bool()
  val isJal    = Bool()
  val isJalr   = Bool()
  val isLui    = Bool()
  val isAuipc  = Bool()
  val isCsr    = Bool()
  val isMulDiv = Bool()

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
  val funct6 = instr(31, 26) // RV64 OP-IMM shift-immediate function field

  val isOp      = opcode === Opcode.OP
  val isOpImm   = opcode === Opcode.OP_IMM
  val isOp32    = opcode === Opcode.OP_32
  val isOpImm32 = opcode === Opcode.OP_IMM_32

  // CSR instructions are SYSTEM with funct3 != 000.
  // SYSTEM/funct3 == 000 is ECALL/EBREAK/MRET/etc, not normal CSR read/write.
  val isCsrInstr = opcode === Opcode.SYSTEM && funct3 =/= "b000".U

  val isMulDivInstr =
    (isOp || isOp32) &&
    funct7 === "b0000001".U

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
    isOpImm                  ||
    isOp                     ||
    isOpImm32                ||
    isOp32                   ||
    isCsrInstr

  val out = io.out

  out.rs1      := rs1
  out.rs2      := rs2
  out.rd       := Mux(writesRd, rd, 0.U)
  out.memOp    := funct3
  out.csrAddr  := instr(31, 20)

  out.isLoad   := opcode === Opcode.LOAD
  out.isStore  := opcode === Opcode.STORE
  out.isBranch := opcode === Opcode.BRANCH
  out.isJal    := opcode === Opcode.JAL
  out.isJalr   := opcode === Opcode.JALR
  out.isLui    := opcode === Opcode.LUI
  out.isAuipc  := opcode === Opcode.AUIPC
  out.isCsr    := isCsrInstr
  out.isMulDiv := isMulDivInstr
  out.valid    := true.B

  // Immediate selection
  out.imm := MuxCase(immI, Seq(
    (opcode === Opcode.STORE)  -> immS,
    (opcode === Opcode.BRANCH) -> immB,
    (opcode === Opcode.LUI)    -> immU,
    (opcode === Opcode.AUIPC)  -> immU,
    (opcode === Opcode.JAL)    -> immJ
    // OP_IMM, OP_IMM_32, LOAD, JALR all use immI by default
  ))

  // Use immediate for ALU input B?
  out.useImm := isOpImm                  ||
                isOpImm32                ||
                opcode === Opcode.LOAD   ||
                opcode === Opcode.STORE  ||
                opcode === Opcode.JALR

  // ALU op decode
  out.aluOp := MuxCase(ALU.ADD.U, Seq(
    // LUI/AUIPC can use ADD-style datapath handling.
    (opcode === Opcode.LUI)                                -> ALU.ADD.U,
    (opcode === Opcode.AUIPC)                              -> ALU.ADD.U,

    // ---- 64-bit OP ----
    ((isOp) &&
      funct3 === "b000".U && funct7 === "b0000000".U)      -> ALU.ADD.U,

    ((isOp) &&
      funct3 === "b000".U && funct7 === "b0100000".U)      -> ALU.SUB.U,

    ((isOp) &&
      funct3 === "b111".U && funct7 === "b0000000".U)      -> ALU.AND.U,

    ((isOp) &&
      funct3 === "b110".U && funct7 === "b0000000".U)      -> ALU.OR.U,

    ((isOp) &&
      funct3 === "b100".U && funct7 === "b0000000".U)      -> ALU.XOR.U,

    ((isOp) &&
      funct3 === "b001".U && funct7 === "b0000000".U)      -> ALU.SLL.U,

    ((isOp) &&
      funct3 === "b101".U && funct7 === "b0000000".U)      -> ALU.SRL.U,

    ((isOp) &&
      funct3 === "b101".U && funct7 === "b0100000".U)      -> ALU.SRA.U,

    ((isOp) &&
      funct3 === "b010".U && funct7 === "b0000000".U)      -> ALU.SLT.U,

    ((isOp) &&
      funct3 === "b011".U && funct7 === "b0000000".U)      -> ALU.SLTU.U,

    // ---- 64-bit OP-IMM ----
    ((isOpImm) &&
      funct3 === "b000".U)                                 -> ALU.ADD.U,  // ADDI

    ((isOpImm) &&
      funct3 === "b111".U)                                 -> ALU.AND.U,  // ANDI

    ((isOpImm) &&
      funct3 === "b110".U)                                 -> ALU.OR.U,   // ORI

    ((isOpImm) &&
      funct3 === "b100".U)                                 -> ALU.XOR.U,  // XORI

    ((isOpImm) &&
      funct3 === "b001".U && funct6 === "b000000".U)       -> ALU.SLL.U,  // SLLI

    ((isOpImm) &&
      funct3 === "b101".U && funct6 === "b000000".U)       -> ALU.SRL.U,  // SRLI

    ((isOpImm) &&
      funct3 === "b101".U && funct6 === "b010000".U)       -> ALU.SRA.U,  // SRAI

    ((isOpImm) &&
      funct3 === "b010".U)                                 -> ALU.SLT.U,  // SLTI

    ((isOpImm) &&
      funct3 === "b011".U)                                 -> ALU.SLTU.U, // SLTIU

    // ---- 32-bit OP_32 ----
    ((isOp32) &&
      funct3 === "b000".U && funct7 === "b0000000".U)      -> ALU.ADDW.U,

    ((isOp32) &&
      funct3 === "b000".U && funct7 === "b0100000".U)      -> ALU.SUBW.U,

    ((isOp32) &&
      funct3 === "b001".U && funct7 === "b0000000".U)      -> ALU.SLLW.U,

    ((isOp32) &&
      funct3 === "b101".U && funct7 === "b0000000".U)      -> ALU.SRLW.U,

    ((isOp32) &&
      funct3 === "b101".U && funct7 === "b0100000".U)      -> ALU.SRAW.U,

    // ---- 32-bit OP-IMM-32 ----
    ((isOpImm32) &&
      funct3 === "b000".U)                                 -> ALU.ADDW.U, // ADDIW

    ((isOpImm32) &&
      funct3 === "b001".U && funct7 === "b0000000".U)      -> ALU.SLLW.U, // SLLIW

    ((isOpImm32) &&
      funct3 === "b101".U && funct7 === "b0000000".U)      -> ALU.SRLW.U, // SRLIW

    ((isOpImm32) &&
      funct3 === "b101".U && funct7 === "b0100000".U)      -> ALU.SRAW.U  // SRAIW
  ))

  // MUL/DIV decode
  out.mulDivOp := 0.U

  when (isMulDivInstr) {
    when (isOp) {
      switch(funct3) {
        is("b000".U) { out.mulDivOp := MulDivOp.MUL.U }
        is("b001".U) { out.mulDivOp := MulDivOp.MULH.U }
        is("b010".U) { out.mulDivOp := MulDivOp.MULHSU.U }
        is("b011".U) { out.mulDivOp := MulDivOp.MULHU.U }
        is("b100".U) { out.mulDivOp := MulDivOp.DIV.U }
        is("b101".U) { out.mulDivOp := MulDivOp.DIVU.U }
        is("b110".U) { out.mulDivOp := MulDivOp.REM.U }
        is("b111".U) { out.mulDivOp := MulDivOp.REMU.U }
      }
    } .elsewhen (isOp32) {
      switch(funct3) {
        is("b000".U) { out.mulDivOp := MulDivOp.MULW.U }
        is("b100".U) { out.mulDivOp := MulDivOp.DIVW.U }
        is("b101".U) { out.mulDivOp := MulDivOp.DIVUW.U }
        is("b110".U) { out.mulDivOp := MulDivOp.REMW.U }
        is("b111".U) { out.mulDivOp := MulDivOp.REMUW.U }
      }
    }
  }

  // Branch op uses raw RISC-V funct3.
  out.brOp := funct3
}