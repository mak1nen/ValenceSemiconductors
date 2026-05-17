package valence.execution

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class BranchUnitSpec extends AnyFlatSpec with Matchers {

  behavior of "BranchUnit"

  def test(fn: BranchUnit => Unit): Unit =
    simulate(new BranchUnit(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.rs1.poke(0.U)
      dut.io.rs2.poke(0.U)
      dut.io.pc.poke(0.U)
      dut.io.imm.poke(0.U)
      dut.io.op.poke(BranchUnit.BEQ.U)
      fn(dut)
    }

  it should "BEQ taken when equal" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BEQ.U)
      dut.io.rs1.poke(5.U)
      dut.io.rs2.poke(5.U)
      dut.io.pc.poke(100.U)
      dut.io.imm.poke(20.U)
      dut.clock.step()
      dut.io.taken.expect(true)
      dut.io.target.expect(120.U)
    }
  }

  it should "BEQ not taken when not equal" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BEQ.U)
      dut.io.rs1.poke(5.U)
      dut.io.rs2.poke(6.U)
      dut.clock.step()
      dut.io.taken.expect(false)
    }
  }

  it should "BNE taken when not equal" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BNE.U)
      dut.io.rs1.poke(5.U)
      dut.io.rs2.poke(6.U)
      dut.io.pc.poke(100.U)
      dut.io.imm.poke(8.U)
      dut.clock.step()
      dut.io.taken.expect(true)
      dut.io.target.expect(108.U)
    }
  }

  it should "BNE not taken when equal" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BNE.U)
      dut.io.rs1.poke(5.U)
      dut.io.rs2.poke(5.U)
      dut.clock.step()
      dut.io.taken.expect(false)
    }
  }

  it should "BLT taken when rs1 < rs2 signed" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BLT.U)
      dut.io.rs1.poke(3.U)
      dut.io.rs2.poke(10.U)
      dut.clock.step()
      dut.io.taken.expect(true)
    }
  }

  it should "BGE taken when rs1 >= rs2 signed" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BGE.U)
      dut.io.rs1.poke(10.U)
      dut.io.rs2.poke(3.U)
      dut.clock.step()
      dut.io.taken.expect(true)
    }
  }

  it should "BLTU taken when rs1 < rs2 unsigned" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BLTU.U)
      dut.io.rs1.poke(3.U)
      dut.io.rs2.poke(10.U)
      dut.clock.step()
      dut.io.taken.expect(true)
    }
  }

  it should "BGEU taken when rs1 >= rs2 unsigned" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BGEU.U)
      dut.io.rs1.poke(10.U)
      dut.io.rs2.poke(3.U)
      dut.clock.step()
      dut.io.taken.expect(true)
    }
  }

  it should "compute target as pc + imm" in {
    test { dut =>
      dut.io.op.poke(BranchUnit.BEQ.U)
      dut.io.rs1.poke(1.U)
      dut.io.rs2.poke(1.U)
      dut.io.pc.poke(200.U)
      dut.io.imm.poke(40.U)
      dut.clock.step()
      dut.io.taken.expect(true)
      dut.io.target.expect(240.U)
    }
  }
}