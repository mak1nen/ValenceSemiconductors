package valence.execution

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class AluSpec extends AnyFlatSpec with Matchers {

  behavior of "ALU"

  def testAlu(op: Int, a: Long, b: Long, expected: Long): Unit = {
    simulate(new ALU(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.op.poke(op.U)
      dut.io.rs1.poke(a.U)
      dut.io.rs2.poke(b.U)
      dut.clock.step()
      dut.io.result.expect(expected.U)
    }
  }

  it should "ADD" in {
    testAlu(ALU.ADD, 10, 20, 30)
    testAlu(ALU.ADD, 0, 0, 0)
  }

  it should "SUB" in {
    testAlu(ALU.SUB, 30, 10, 20)
    testAlu(ALU.SUB, 5, 5, 0)
  }

  it should "AND" in {
    testAlu(ALU.AND, 0xFF, 0x0F, 0x0F)
    testAlu(ALU.AND, 0xFF, 0x00, 0x00)
  }

  it should "OR" in {
    testAlu(ALU.OR, 0xF0, 0x0F, 0xFF)
    testAlu(ALU.OR, 0x00, 0x00, 0x00)
  }

  it should "XOR" in {
    testAlu(ALU.XOR, 0xFF, 0x0F, 0xF0)
    testAlu(ALU.XOR, 0xFF, 0xFF, 0x00)
  }

  it should "SLL (shift left logical)" in {
    testAlu(ALU.SLL, 1, 4, 16)
    testAlu(ALU.SLL, 1, 0, 1)
  }

  it should "SRL (shift right logical)" in {
    testAlu(ALU.SRL, 16, 4, 1)
    testAlu(ALU.SRL, 1, 1, 0)
  }

  it should "SLT (set less than signed)" in {
    testAlu(ALU.SLT, 5, 10, 1)
    testAlu(ALU.SLT, 10, 5, 0)
    testAlu(ALU.SLT, 5, 5, 0)
  }

  it should "SLTU (set less than unsigned)" in {
    testAlu(ALU.SLTU, 5, 10, 1)
    testAlu(ALU.SLTU, 10, 5, 0)
  }

  it should "set zero flag when result is 0" in {
    simulate(new ALU(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.op.poke(ALU.SUB.U)
      dut.io.rs1.poke(5.U)
      dut.io.rs2.poke(5.U)
      dut.clock.step()
      dut.io.zero.expect(true)
    }
  }

  it should "clear zero flag when result is nonzero" in {
    simulate(new ALU(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.op.poke(ALU.ADD.U)
      dut.io.rs1.poke(1.U)
      dut.io.rs2.poke(1.U)
      dut.clock.step()
      dut.io.zero.expect(false)
    }
  }
}