package valence.core

import chisel3._
import chisel3.util._
import valence.execution.{ALU, BranchUnit, MulDiv}

class ExecuteIn extends Bundle {
  val pc       = UInt(64.W)

  val rs1_val  = UInt(64.W)
  val rs2_val  = UInt(64.W)

  val imm      = UInt(64.W)

  val rd       = UInt(5.W)

  val aluOp    = UInt(5.W)
  val mulDivOp = UInt(5.W)

  val brOp     = UInt(3.W)
  val memOp    = UInt(3.W)

  // Atomics
  val isLR     = Bool()
  val isSC     = Bool()
  val isAmo    = Bool()

  val amoOp    = UInt(5.W)

  val aq       = Bool()
  val rl       = Bool()

  // Control
  val useImm   = Bool()

  val isLoad   = Bool()
  val isStore  = Bool()

  val isBranch = Bool()

  val isJal    = Bool()
  val isJalr   = Bool()

  val isLui    = Bool()
  val isAuipc  = Bool()

  val isCsr    = Bool()
  val isMulDiv = Bool()

  val valid    = Bool()
}

class ExecuteOut extends Bundle {
  val result        = UInt(64.W)

  val rd            = UInt(5.W)

  val rs2_val       = UInt(64.W)

  val memOp         = UInt(3.W)

  val isLoad        = Bool()
  val isStore       = Bool()

  // Atomics
  val isLR          = Bool()
  val isSC          = Bool()
  val isAmo         = Bool()

  val amoOp         = UInt(5.W)

  val branch_taken  = Bool()
  val branch_target = UInt(64.W)

  val valid         = Bool()
}

class Execute extends Module {
  val io = IO(new Bundle {
    val in  = Input(new ExecuteIn)
    val out = Output(new ExecuteOut)
  })

  val alu    = Module(new ALU(64))
  val muldiv = Module(new MulDiv(64))
  val bu     = Module(new BranchUnit(64))

  // ---------------------------------------------------------------------------
  // Atomic classification
  // ---------------------------------------------------------------------------
  // For LR/SC/AMO, the memory address is rs1.
  // rs2 is data for SC/AMO, not an address operand.

  val isAtomic =
    io.in.isLR ||
    io.in.isSC ||
    io.in.isAmo

  // ---------------------------------------------------------------------------
  // ALU input selection
  // ---------------------------------------------------------------------------

  val alu_a = Mux(
    io.in.isLui,
    0.U,
    Mux(
      io.in.isAuipc,
      io.in.pc,
      io.in.rs1_val
    )
  )

  val alu_b = Mux(
    io.in.useImm || io.in.isLui || io.in.isAuipc,
    io.in.imm,
    io.in.rs2_val
  )

  // ---------------------------------------------------------------------------
  // ALU
  // ---------------------------------------------------------------------------

  alu.io.op  := io.in.aluOp
  alu.io.rs1 := alu_a
  alu.io.rs2 := alu_b

  // ---------------------------------------------------------------------------
  // MUL/DIV
  // ---------------------------------------------------------------------------

  muldiv.io.op  := io.in.mulDivOp
  muldiv.io.rs1 := io.in.rs1_val
  muldiv.io.rs2 := io.in.rs2_val

  // ---------------------------------------------------------------------------
  // Branch unit
  // ---------------------------------------------------------------------------

  bu.io.op  := io.in.brOp
  bu.io.rs1 := io.in.rs1_val
  bu.io.rs2 := io.in.rs2_val
  bu.io.pc  := io.in.pc
  bu.io.imm := io.in.imm

  // ---------------------------------------------------------------------------
  // Jump targets
  // ---------------------------------------------------------------------------

  val jal_target =
    io.in.pc + io.in.imm

  val jalr_target =
    (io.in.rs1_val + io.in.imm) & ~1.U(64.W)

  // ---------------------------------------------------------------------------
  // Result selection
  // ---------------------------------------------------------------------------
  // Normal loads/stores use the ALU effective address.
  // LR/SC/AMO use rs1 directly, because rs2 is the atomic data operand.

  io.out.result := Mux(
    io.in.isJal || io.in.isJalr,
    io.in.pc + 4.U,
    Mux(
      isAtomic,
      io.in.rs1_val,
      Mux(
        io.in.isMulDiv,
        muldiv.io.result,
        alu.io.result
      )
    )
  )

  // ---------------------------------------------------------------------------
  // Pipeline passthrough
  // ---------------------------------------------------------------------------

  io.out.rd      := io.in.rd
  io.out.rs2_val := io.in.rs2_val
  io.out.memOp   := io.in.memOp

  io.out.isLoad  := io.in.isLoad
  io.out.isStore := io.in.isStore

  // Atomics
  io.out.isLR    := io.in.isLR
  io.out.isSC    := io.in.isSC
  io.out.isAmo   := io.in.isAmo
  io.out.amoOp   := io.in.amoOp

  // ---------------------------------------------------------------------------
  // Branch control
  // ---------------------------------------------------------------------------

  io.out.branch_taken :=
    (io.in.isBranch && bu.io.taken) ||
    io.in.isJal ||
    io.in.isJalr

  io.out.branch_target := MuxCase(
    bu.io.target,
    Seq(
      io.in.isJal  -> jal_target,
      io.in.isJalr -> jalr_target
    )
  )

  io.out.valid := io.in.valid
}