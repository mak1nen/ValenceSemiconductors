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
  val OP_IMM_32  = "b0011011".U(7.W)
  val OP_32      = "b0111011".U(7.W)
  val AMO        = "b0101111".U(7.W)  // RV64A
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

  // CSR
  val csrAddr  = UInt(12.W)
  val csrOp    = UInt(3.W)
  val csrUimm  = UInt(5.W)

  // Memory / control
  val isLoad   = Bool()
  val isStore  = Bool()
  val isBranch = Bool()
  val isJal    = Bool()
  val isJalr   = Bool()
  val isLui    = Bool()
  val isAuipc  = Bool()

  // CSR
  val isCsr    = Bool()

  // M extension
  val isMulDiv = Bool()

  // A extension
  val isLR     = Bool()
  val isSC     = Bool()
  val isAmo    = Bool()

  val amoOp    = UInt(5.W)

  // aq / rl bits
  val aq       = Bool()
  val rl       = Bool()

  val useImm   = Bool()
  val valid    = Bool()
}

class Decode extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val out   = Output(new DecodeOut)
  })

  // ───────────────────────────────────────────────────────────────────────────
  // Instruction fields
  // ───────────────────────────────────────────────────────────────────────────

  val instr  = io.instr

  val opcode = instr(6, 0)
  val rd     = instr(11, 7)
  val funct3 = instr(14, 12)
  val rs1    = instr(19, 15)
  val rs2    = instr(24, 20)

  val funct7 = instr(31, 25)
  val funct6 = instr(31, 26)
  val funct5 = instr(31, 27)

  // Atomic ordering bits
  val aq = instr(26)
  val rl = instr(25)

  // ───────────────────────────────────────────────────────────────────────────
  // Opcode classification
  // ───────────────────────────────────────────────────────────────────────────

  val isOp      = opcode === Opcode.OP
  val isOpImm   = opcode === Opcode.OP_IMM
  val isOp32    = opcode === Opcode.OP_32
  val isOpImm32 = opcode === Opcode.OP_IMM_32

  val isAmoOpc  = opcode === Opcode.AMO

  val isCsrInstr =
    opcode === Opcode.SYSTEM &&
    funct3 =/= "b000".U

  val isMulDivInstr =
    (isOp || isOp32) &&
    funct7 === "b0000001".U

  // ───────────────────────────────────────────────────────────────────────────
  // Atomic instruction decode
  // ───────────────────────────────────────────────────────────────────────────

  val isLR =
    isAmoOpc &&
    funct5 === "b00010".U &&
    rs2 === 0.U

  val isSC =
    isAmoOpc &&
    funct5 === "b00011".U

  val isAmo =
    isAmoOpc &&
    !isLR &&
    !isSC

  // ───────────────────────────────────────────────────────────────────────────
  // Immediate decode
  // ───────────────────────────────────────────────────────────────────────────

  val immI =
    Cat(Fill(52, instr(31)), instr(31, 20))

  val immS =
    Cat(Fill(52, instr(31)),
        instr(31, 25),
        instr(11, 7))

  val immB =
    Cat(Fill(51, instr(31)),
        instr(31),
        instr(7),
        instr(30, 25),
        instr(11, 8),
        0.U(1.W))

  val immU =
    Cat(Fill(32, instr(31)),
        instr(31, 12),
        0.U(12.W))

  val immJ =
    Cat(Fill(43, instr(31)),
        instr(31),
        instr(19, 12),
        instr(20),
        instr(30, 21),
        0.U(1.W))

  // ───────────────────────────────────────────────────────────────────────────
  // Does instruction write rd?
  // ───────────────────────────────────────────────────────────────────────────

  val writesRd =
    opcode === Opcode.LUI     ||
    opcode === Opcode.AUIPC   ||
    opcode === Opcode.JAL     ||
    opcode === Opcode.JALR    ||
    opcode === Opcode.LOAD    ||
    isOpImm                   ||
    isOp                      ||
    isOpImm32                 ||
    isOp32                    ||
    isCsrInstr                ||
    isAmoOpc

  val out = io.out

  // ───────────────────────────────────────────────────────────────────────────
  // Register fields
  // ───────────────────────────────────────────────────────────────────────────

  out.rs1 := rs1
  out.rs2 := rs2
  out.rd  := Mux(writesRd, rd, 0.U)

  // ───────────────────────────────────────────────────────────────────────────
  // Memory operation width
  // ───────────────────────────────────────────────────────────────────────────

  out.memOp := funct3

  // ───────────────────────────────────────────────────────────────────────────
  // CSR metadata
  // ───────────────────────────────────────────────────────────────────────────

  out.csrAddr := instr(31, 20)
  out.csrOp   := funct3
  out.csrUimm := rs1

  // ───────────────────────────────────────────────────────────────────────────
  // Main control decode
  // ───────────────────────────────────────────────────────────────────────────

  out.isLoad   := opcode === Opcode.LOAD
  out.isStore  := opcode === Opcode.STORE

  out.isBranch := opcode === Opcode.BRANCH

  out.isJal    := opcode === Opcode.JAL
  out.isJalr   := opcode === Opcode.JALR

  out.isLui    := opcode === Opcode.LUI
  out.isAuipc  := opcode === Opcode.AUIPC

  out.isCsr    := isCsrInstr

  out.isMulDiv := isMulDivInstr

  // Atomic extension
  out.isLR     := isLR
  out.isSC     := isSC
  out.isAmo    := isAmo

  out.amoOp    := funct5

  out.aq       := aq
  out.rl       := rl

  out.valid    := true.B

  // ───────────────────────────────────────────────────────────────────────────
  // Immediate selection
  // ───────────────────────────────────────────────────────────────────────────

  out.imm := MuxCase(immI, Seq(
    (opcode === Opcode.STORE)  -> immS,
    (opcode === Opcode.BRANCH) -> immB,
    (opcode === Opcode.LUI)    -> immU,
    (opcode === Opcode.AUIPC)  -> immU,
    (opcode === Opcode.JAL)    -> immJ
  ))

  // ───────────────────────────────────────────────────────────────────────────
  // Use immediate?
  // ───────────────────────────────────────────────────────────────────────────

  out.useImm :=
    isOpImm                  ||
    isOpImm32                ||
    opcode === Opcode.LOAD   ||
    opcode === Opcode.STORE  ||
    opcode === Opcode.JALR

  // ───────────────────────────────────────────────────────────────────────────
  // ALU decode
  // ───────────────────────────────────────────────────────────────────────────

  out.aluOp := MuxCase(ALU.ADD.U, Seq(

    // U-type
    (opcode === Opcode.LUI)   -> ALU.ADD.U,
    (opcode === Opcode.AUIPC) -> ALU.ADD.U,

    // 64-bit OP
    ((isOp) && funct3 === "b000".U && funct7 === "b0000000".U) -> ALU.ADD.U,
    ((isOp) && funct3 === "b000".U && funct7 === "b0100000".U) -> ALU.SUB.U,
    ((isOp) && funct3 === "b111".U && funct7 === "b0000000".U) -> ALU.AND.U,
    ((isOp) && funct3 === "b110".U && funct7 === "b0000000".U) -> ALU.OR.U,
    ((isOp) && funct3 === "b100".U && funct7 === "b0000000".U) -> ALU.XOR.U,
    ((isOp) && funct3 === "b001".U && funct7 === "b0000000".U) -> ALU.SLL.U,
    ((isOp) && funct3 === "b101".U && funct7 === "b0000000".U) -> ALU.SRL.U,
    ((isOp) && funct3 === "b101".U && funct7 === "b0100000".U) -> ALU.SRA.U,
    ((isOp) && funct3 === "b010".U && funct7 === "b0000000".U) -> ALU.SLT.U,
    ((isOp) && funct3 === "b011".U && funct7 === "b0000000".U) -> ALU.SLTU.U,

    // 64-bit OP-IMM
    ((isOpImm) && funct3 === "b000".U) -> ALU.ADD.U,
    ((isOpImm) && funct3 === "b111".U) -> ALU.AND.U,
    ((isOpImm) && funct3 === "b110".U) -> ALU.OR.U,
    ((isOpImm) && funct3 === "b100".U) -> ALU.XOR.U,
    ((isOpImm) && funct3 === "b001".U && funct6 === "b000000".U) -> ALU.SLL.U,
    ((isOpImm) && funct3 === "b101".U && funct6 === "b000000".U) -> ALU.SRL.U,
    ((isOpImm) && funct3 === "b101".U && funct6 === "b010000".U) -> ALU.SRA.U,
    ((isOpImm) && funct3 === "b010".U) -> ALU.SLT.U,
    ((isOpImm) && funct3 === "b011".U) -> ALU.SLTU.U,

    // 32-bit OP
    ((isOp32) && funct3 === "b000".U && funct7 === "b0000000".U) -> ALU.ADDW.U,
    ((isOp32) && funct3 === "b000".U && funct7 === "b0100000".U) -> ALU.SUBW.U,
    ((isOp32) && funct3 === "b001".U && funct7 === "b0000000".U) -> ALU.SLLW.U,
    ((isOp32) && funct3 === "b101".U && funct7 === "b0000000".U) -> ALU.SRLW.U,
    ((isOp32) && funct3 === "b101".U && funct7 === "b0100000".U) -> ALU.SRAW.U,

    // 32-bit OP-IMM
    ((isOpImm32) && funct3 === "b000".U) -> ALU.ADDW.U,
    ((isOpImm32) && funct3 === "b001".U && funct7 === "b0000000".U) -> ALU.SLLW.U,
    ((isOpImm32) && funct3 === "b101".U && funct7 === "b0000000".U) -> ALU.SRLW.U,
    ((isOpImm32) && funct3 === "b101".U && funct7 === "b0100000".U) -> ALU.SRAW.U
  ))

  // ───────────────────────────────────────────────────────────────────────────
  // MUL/DIV decode
  // ───────────────────────────────────────────────────────────────────────────

  out.mulDivOp := 0.U

  when(isMulDivInstr) {

    when(isOp) {

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

    }.elsewhen(isOp32) {

      switch(funct3) {
        is("b000".U) { out.mulDivOp := MulDivOp.MULW.U }
        is("b100".U) { out.mulDivOp := MulDivOp.DIVW.U }
        is("b101".U) { out.mulDivOp := MulDivOp.DIVUW.U }
        is("b110".U) { out.mulDivOp := MulDivOp.REMW.U }
        is("b111".U) { out.mulDivOp := MulDivOp.REMUW.U }
      }
    }
  }

  // ───────────────────────────────────────────────────────────────────────────
  // Branch operation
  // ───────────────────────────────────────────────────────────────────────────

  out.brOp := funct3
}