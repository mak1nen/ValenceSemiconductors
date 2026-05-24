package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.execution.{ALU, MulDivOp}

class DecodeSpec extends AnyFlatSpec with Matchers {

  behavior of "Decode"

  def test(instr: Long)(fn: Decode => Unit): Unit =
    simulate(new Decode) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.instr.poke(instr.U)
      fn(dut)
    }

  // ==========================================================================
  // Existing baseline tests
  // ==========================================================================

  it should "decode ADD r2, r1, r2" in {
    // ADD rd=2 rs1=1 rs2=2 funct3=0 funct7=0
    test(0x00208133L) { dut =>
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(2.U)
      dut.io.out.aluOp.expect(ALU.ADD.U)
      dut.io.out.useImm.expect(false)
    }
  }

  it should "decode ADDI r1, r0, 42" in {
    test(0x02A00093L) { dut =>
      dut.io.out.rs1.expect(0.U)
      dut.io.out.rd.expect(1.U)
      dut.io.out.imm.expect(42.U)
      dut.io.out.useImm.expect(true)
      dut.io.out.aluOp.expect(ALU.ADD.U)
    }
  }

  it should "decode LW (load)" in {
    test(0x00012083L) { dut =>
      dut.io.out.isLoad.expect(true)
      dut.io.out.isStore.expect(false)
      dut.io.out.useImm.expect(true)
    }
  }

  it should "decode SW (store)" in {
    test(0x00112023L) { dut =>
      dut.io.out.isStore.expect(true)
      dut.io.out.isLoad.expect(false)
    }
  }

  it should "decode BEQ (branch)" in {
    test(0x00208463L) { dut =>
      dut.io.out.isBranch.expect(true)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
    }
  }

  it should "decode JAL" in {
    test(0x000000EFL) { dut =>
      dut.io.out.isJal.expect(true)
    }
  }

  it should "decode LUI" in {
    test(0x12345537L) { dut =>
      dut.io.out.isLui.expect(true)
      dut.io.out.rd.expect(10.U)
    }
  }

  // ==========================================================================
  // RV64I shift-immediate with shamt 32-63 (uses 6-bit funct6, not funct7)
  // ==========================================================================

  it should "decode SLLI r1, r2, 32 (RV64 6-bit shamt)" in {
    // SLLI: funct6=000000, shamt=100000 (32), rs1=2, funct3=001, rd=1, opcode=0010011
    test(0x02011093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SLL.U)
      dut.io.out.useImm.expect(true)
      dut.io.out.rd.expect(1.U)
      dut.io.out.rs1.expect(2.U)
      // immI = instr[31:20] sign-extended; shamt = imm low 6 bits = 32
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 32, s"expected shamt=32, got ${imm & 0x3F}")
    }
  }

  it should "decode SLLI r1, r2, 63 (max RV64 shamt)" in {
    test(0x03F11093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SLL.U)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 63, s"expected shamt=63, got ${imm & 0x3F}")
    }
  }

  it should "decode SRLI r1, r2, 32" in {
    test(0x02015093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SRL.U)
      dut.io.out.useImm.expect(true)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 32, s"expected shamt=32, got ${imm & 0x3F}")
    }
  }

  it should "decode SRLI r1, r2, 63" in {
    test(0x03F15093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SRL.U)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 63, s"expected shamt=63, got ${imm & 0x3F}")
    }
  }

  it should "decode SRAI r1, r2, 32" in {
    test(0x42015093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SRA.U)
      dut.io.out.useImm.expect(true)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 32, s"expected shamt=32, got ${imm & 0x3F}")
    }
  }

  it should "decode SRAI r1, r2, 63" in {
    test(0x43F15093L) { dut =>
      dut.io.out.aluOp.expect(ALU.SRA.U)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x3F) == 63, s"expected shamt=63, got ${imm & 0x3F}")
    }
  }

  // ==========================================================================
  // RV64I OP-IMM-32 W-immediate ops
  // ==========================================================================

  it should "decode ADDIW r1, r2, 5" in {
    // ADDIW: imm=000000000101, rs1=00010, funct3=000, rd=00001, opcode=0011011
    test(0x0051009BL) { dut =>
      dut.io.out.aluOp.expect(ALU.ADDW.U)
      dut.io.out.useImm.expect(true)
      dut.io.out.rs1.expect(2.U)
      dut.io.out.rd.expect(1.U)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0xFFF) == 5, s"expected imm low 12 = 5, got ${imm & 0xFFF}")
      dut.io.out.isMulDiv.expect(false)
    }
  }

  it should "decode ADDIW with negative immediate" in {
    // ADDIW r1, r2, -1: imm=111111111111
    test(0xFFF1011BL) { dut =>
      dut.io.out.aluOp.expect(ALU.ADDW.U)
      dut.io.out.useImm.expect(true)
      // imm should be sign-extended -1 = all ones in 64 bits
      dut.io.out.imm.expect("hFFFFFFFFFFFFFFFF".U)
    }
  }

  it should "decode SLLIW r1, r2, 5" in {
    // SLLIW: funct7=0000000, shamt=00101, rs1=00010, funct3=001, rd=00001, opcode=0011011
    test(0x0051111BL) { dut =>
      dut.io.out.aluOp.expect(ALU.SLLW.U)
      dut.io.out.useImm.expect(true)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x1F) == 5, s"expected shamt=5, got ${imm & 0x1F}")
    }
  }

  it should "decode SLLIW r1, r2, 31 (max W shamt)" in {
    // shamt=11111, funct7=0000000
    test(0x01F1111BL) { dut =>
      dut.io.out.aluOp.expect(ALU.SLLW.U)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x1F) == 31, s"expected shamt=31, got ${imm & 0x1F}")
    }
  }

  it should "decode SRLIW r1, r2, 5" in {
    // SRLIW: funct7=0000000, shamt=00101, funct3=101, opcode=0011011
    test(0x0051511BL) { dut =>
      dut.io.out.aluOp.expect(ALU.SRLW.U)
      dut.io.out.useImm.expect(true)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x1F) == 5, s"expected shamt=5, got ${imm & 0x1F}")
    }
  }

  it should "decode SRAIW r1, r2, 5" in {
    // SRAIW: funct7=0100000, shamt=00101, funct3=101, opcode=0011011
    test(0x4051511BL) { dut =>
      dut.io.out.aluOp.expect(ALU.SRAW.U)
      dut.io.out.useImm.expect(true)
      val imm = dut.io.out.imm.peek().litValue
      assert((imm & 0x1F) == 5, s"expected shamt=5, got ${imm & 0x1F}")
    }
  }

  // ==========================================================================
  // RV64I OP_32 W register-register ops
  // ==========================================================================

  it should "decode ADDW r3, r1, r2" in {
    // ADDW: funct7=0000000, rs2=00010, rs1=00001, funct3=000, rd=00011, opcode=0111011
    test(0x002081BBL) { dut =>
      dut.io.out.aluOp.expect(ALU.ADDW.U)
      dut.io.out.useImm.expect(false)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(3.U)
      dut.io.out.isMulDiv.expect(false)
    }
  }

  it should "decode SUBW r3, r1, r2" in {
    // SUBW: funct7=0100000, rs2=00010, rs1=00001, funct3=000, rd=00011, opcode=0111011
    test(0x402081BBL) { dut =>
      dut.io.out.aluOp.expect(ALU.SUBW.U)
      dut.io.out.useImm.expect(false)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(3.U)
    }
  }

  it should "decode SLLW r3, r1, r2" in {
    // SLLW: funct7=0000000, funct3=001, opcode=0111011
    test(0x002091BBL) { dut =>
      dut.io.out.aluOp.expect(ALU.SLLW.U)
      dut.io.out.useImm.expect(false)
    }
  }

  it should "decode SRLW r3, r1, r2" in {
    test(0x0020D1BBL) { dut =>
      dut.io.out.aluOp.expect(ALU.SRLW.U)
    }
  }

  it should "decode SRAW r3, r1, r2" in {
    // SRAW: funct7=0100000, funct3=101
    test(0x4020D1BBL) { dut =>
      dut.io.out.aluOp.expect(ALU.SRAW.U)
    }
  }

  // ==========================================================================
  // Regression: ADD and MUL share funct3=000 on opcode OP.
  // Make sure adding W-ops didn't break the OP/OP_32 distinction.
  // ==========================================================================

  it should "not flag ADDW as MulDiv" in {
    // ADDW (funct7=0000000) must not set isMulDiv even though opcode is OP_32
    test(0x002081BBL) { dut =>
      dut.io.out.isMulDiv.expect(false)
      dut.io.out.aluOp.expect(ALU.ADDW.U)
    }
  }

  it should "not flag ADD as MulDiv" in {
    test(0x00208133L) { dut =>
      dut.io.out.isMulDiv.expect(false)
    }
  }

  // ==========================================================================
  // M-extension decode (existing ops, never previously tested in Decode)
  // ==========================================================================

  it should "decode MUL r3, r1, r2" in {
    // MUL: funct7=0000001, rs2=00010, rs1=00001, funct3=000, rd=00011, opcode=0110011
    test(0x022081B3L) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.MUL.U)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(3.U)
    }
  }

  it should "decode DIV r3, r1, r2" in {
    // DIV: funct7=0000001, funct3=100, opcode=0110011
    test(0x0220C1B3L) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.DIV.U)
    }
  }

  // ==========================================================================
  // M-extension W-variant decode (newly added)
  // ==========================================================================

  it should "decode MULW r3, r1, r2" in {
    // MULW: funct7=0000001, rs2=00010, rs1=00001, funct3=000, rd=00011, opcode=0111011
    test(0x022081BBL) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.MULW.U)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(3.U)
    }
  }

  it should "decode DIVW r3, r1, r2" in {
    // DIVW: funct7=0000001, funct3=100, opcode=0111011
    test(0x0220C1BBL) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.DIVW.U)
    }
  }

  it should "decode DIVUW r3, r1, r2" in {
    // DIVUW: funct7=0000001, funct3=101, opcode=0111011
    test(0x0220D1BBL) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.DIVUW.U)
    }
  }

  it should "decode REMW r3, r1, r2" in {
    // REMW: funct7=0000001, funct3=110, opcode=0111011
    test(0x0220E1BBL) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.REMW.U)
    }
  }

  it should "decode REMUW r3, r1, r2" in {
    // REMUW: funct7=0000001, funct3=111, opcode=0111011
    test(0x0220F1BBL) { dut =>
      dut.io.out.isMulDiv.expect(true)
      dut.io.out.mulDivOp.expect(MulDivOp.REMUW.U)
    }
  }
}