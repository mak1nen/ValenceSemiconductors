package valence.pipeline

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class HazardUnitSpec extends AnyFlatSpec with Matchers {

  behavior of "HazardUnit"

  // helper
  def test(fn: HazardUnit => Unit): Unit =
    simulate(new HazardUnit) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      // default — no hazards
      dut.io.id_rs1.poke(0.U)
      dut.io.id_rs2.poke(0.U)
      dut.io.ex_rd.poke(0.U)
      dut.io.ex_is_load.poke(false)
      dut.io.mem_rd.poke(0.U)
      dut.io.mem_wen.poke(false)
      dut.io.branch_taken.poke(false)
      fn(dut)
    }

  it should "produce no hazard when registers are independent" in {
    test { dut =>
      dut.io.id_rs1.poke(1.U)
      dut.io.id_rs2.poke(2.U)
      dut.io.ex_rd.poke(3.U)
      dut.io.ex_is_load.poke(false)
      dut.clock.step()
      dut.io.stall.expect(false)
      dut.io.flush.expect(false)
    }
  }

  it should "stall on load-use hazard (rs1)" in {
    test { dut =>
      // EX stage is a load writing to r1
      // ID stage needs r1 — must stall one cycle
      dut.io.id_rs1.poke(1.U)
      dut.io.id_rs2.poke(5.U)
      dut.io.ex_rd.poke(1.U)
      dut.io.ex_is_load.poke(true)
      dut.clock.step()
      dut.io.stall.expect(true)
      dut.io.flush.expect(false)
    }
  }

  it should "stall on load-use hazard (rs2)" in {
    test { dut =>
      dut.io.id_rs1.poke(5.U)
      dut.io.id_rs2.poke(2.U)
      dut.io.ex_rd.poke(2.U)
      dut.io.ex_is_load.poke(true)
      dut.clock.step()
      dut.io.stall.expect(true)
      dut.io.flush.expect(false)
    }
  }

  it should "not stall on load when rd is r0" in {
    test { dut =>
      dut.io.id_rs1.poke(0.U)
      dut.io.id_rs2.poke(0.U)
      dut.io.ex_rd.poke(0.U)
      dut.io.ex_is_load.poke(true)
      dut.clock.step()
      dut.io.stall.expect(false)
    }
  }

  it should "not stall on non-load RAW hazard (forwarding handles it)" in {
    test { dut =>
      // EX writing r1, ID reading r1 — but not a load
      // forwarding unit handles this, no stall needed
      dut.io.id_rs1.poke(1.U)
      dut.io.ex_rd.poke(1.U)
      dut.io.ex_is_load.poke(false)
      dut.clock.step()
      dut.io.stall.expect(false)
    }
  }

  it should "flush on branch taken" in {
    test { dut =>
      dut.io.branch_taken.poke(true)
      dut.clock.step()
      dut.io.flush.expect(true)
      dut.io.stall.expect(false)
    }
  }

  it should "flush and stall together when both conditions met" in {
    test { dut =>
      // load-use hazard + branch taken
      dut.io.id_rs1.poke(1.U)
      dut.io.ex_rd.poke(1.U)
      dut.io.ex_is_load.poke(true)
      dut.io.branch_taken.poke(true)
      dut.clock.step()
      // flush takes priority
      dut.io.flush.expect(true)
    }
  }
}