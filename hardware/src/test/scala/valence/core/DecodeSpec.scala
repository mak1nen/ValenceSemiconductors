package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.execution.ALU

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

  it should "decode ADD r2, r1, r2" in {
    // ADD rd=2 rs1=1 rs2=2 funct3=0 funct7=0
    // 0000000 00010 00001 000 00010 0110011
    test(0x00208133L) { dut =>
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
      dut.io.out.rd.expect(2.U)
      dut.io.out.aluOp.expect(ALU.ADD.U)
      dut.io.out.useImm.expect(false)
    }
  }

  it should "decode ADDI r1, r0, 42" in {
    // ADDI rd=1 rs1=0 imm=42 funct3=0
    // 000000101010 00000 000 00001 0010011
    test(0x02A00093L) { dut =>
      dut.io.out.rs1.expect(0.U)
      dut.io.out.rd.expect(1.U)
      dut.io.out.imm.expect(42.U)
      dut.io.out.useImm.expect(true)
      dut.io.out.aluOp.expect(ALU.ADD.U)
    }
  }

  it should "decode LW (load)" in {
    // LW rd=1 rs1=2 imm=0
    // 000000000000 00010 010 00001 0000011
    test(0x00012083L) { dut =>
      dut.io.out.isLoad.expect(true)
      dut.io.out.isStore.expect(false)
      dut.io.out.useImm.expect(true)
    }
  }

  it should "decode SW (store)" in {
    // SW rs1=2 rs2=1 imm=0
    // 0000000 00001 00010 010 00000 0100011
    test(0x00112023L) { dut =>
      dut.io.out.isStore.expect(true)
      dut.io.out.isLoad.expect(false)
    }
  }

  it should "decode BEQ (branch)" in {
    // BEQ rs1=1 rs2=2 imm=8
    // 0000000 00010 00001 000 01000 1100011
    test(0x00208463L) { dut =>
      dut.io.out.isBranch.expect(true)
      dut.io.out.rs1.expect(1.U)
      dut.io.out.rs2.expect(2.U)
    }
  }

  it should "decode JAL" in {
    // JAL rd=1 imm=0
    test(0x000000EFL) { dut =>
      dut.io.out.isJal.expect(true)
    }
  }

  it should "decode LUI" in {
    // LUI rd=1 imm=0x12345000
    test(0x12345537L) { dut =>
      dut.io.out.isLui.expect(true)
      dut.io.out.rd.expect(10.U)
    }
  }
}