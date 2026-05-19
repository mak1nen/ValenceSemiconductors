package valence.pipeline

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

// =============================================================================
// ForwardingUnitSpec — verifies all three forwarding paths
//
// EX  forwarding: result from execute stage (1-cycle gap)
// MEM forwarding: result from EX/MEM register (2-cycle gap)
// WB  forwarding: result from MEM/WB register (3-cycle gap)
// Priority: EX > MEM > WB
// =============================================================================
class ForwardingUnitSpec extends AnyFlatSpec with Matchers {

  behavior of "ForwardingUnit"

  def test(fn: ForwardingUnit => Unit): Unit =
    simulate(new ForwardingUnit) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      // defaults — no forwarding needed
      dut.io.ex_rs1.poke(0.U)
      dut.io.ex_rs2.poke(0.U)
      dut.io.ex_rd.poke(0.U)
      dut.io.ex_wen.poke(false)
      dut.io.mem_rd.poke(0.U)
      dut.io.mem_wen.poke(false)
      dut.io.wb_rd.poke(0.U)
      dut.io.wb_wen.poke(false)
      fn(dut)
    }

  // ── No forwarding ─────────────────────────────────────────────────────────

  it should "select no forwarding when no hazard" in {
    test { dut =>
      dut.io.ex_rs1.poke(1.U)
      dut.io.ex_rs2.poke(2.U)
      dut.io.ex_rd.poke(5.U)
      dut.io.ex_wen.poke(true)
      dut.io.mem_rd.poke(6.U)
      dut.io.mem_wen.poke(true)
      dut.io.wb_rd.poke(7.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.NO_FWD.U)
      dut.io.fwd_b.expect(ForwardingUnit.NO_FWD.U)
    }
  }

  it should "not forward when rd is r0" in {
    test { dut =>
      dut.io.ex_rs1.poke(0.U)
      dut.io.ex_rd.poke(0.U)
      dut.io.ex_wen.poke(true)
      dut.io.mem_rd.poke(0.U)
      dut.io.mem_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.NO_FWD.U)
    }
  }

  // ── EX forwarding (1-cycle gap) ───────────────────────────────────────────

  it should "forward from EX to next instruction for rs1" in {
    test { dut =>
      dut.io.ex_rs1.poke(3.U)
      dut.io.ex_rd.poke(3.U)
      dut.io.ex_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.FWD_EX.U)
    }
  }

  it should "forward from EX to next instruction for rs2" in {
    test { dut =>
      dut.io.ex_rs2.poke(4.U)
      dut.io.ex_rd.poke(4.U)
      dut.io.ex_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_b.expect(ForwardingUnit.FWD_EX.U)
    }
  }

  // ── MEM forwarding (2-cycle gap) ──────────────────────────────────────────

  it should "forward from MEM to EX for rs1" in {
    test { dut =>
      dut.io.ex_rs1.poke(3.U)
      dut.io.mem_rd.poke(3.U)
      dut.io.mem_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.FWD_MEM.U)
    }
  }

  it should "forward from MEM to EX for rs2" in {
    test { dut =>
      dut.io.ex_rs2.poke(4.U)
      dut.io.mem_rd.poke(4.U)
      dut.io.mem_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_b.expect(ForwardingUnit.FWD_MEM.U)
    }
  }

  // ── WB forwarding (3-cycle gap) ───────────────────────────────────────────

  it should "forward from WB to EX for rs1" in {
    test { dut =>
      dut.io.ex_rs1.poke(5.U)
      dut.io.wb_rd.poke(5.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.FWD_WB.U)
    }
  }

  it should "forward from WB to EX for rs2" in {
    test { dut =>
      dut.io.ex_rs2.poke(6.U)
      dut.io.wb_rd.poke(6.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_b.expect(ForwardingUnit.FWD_WB.U)
    }
  }

  // ── Priority ──────────────────────────────────────────────────────────────

  it should "prioritise EX over MEM and WB when all match" in {
    test { dut =>
      dut.io.ex_rs1.poke(7.U)
      dut.io.ex_rd.poke(7.U)
      dut.io.ex_wen.poke(true)
      dut.io.mem_rd.poke(7.U)
      dut.io.mem_wen.poke(true)
      dut.io.wb_rd.poke(7.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.FWD_EX.U)
    }
  }

  it should "prioritise MEM over WB when both match" in {
    test { dut =>
      dut.io.ex_rs1.poke(7.U)
      dut.io.mem_rd.poke(7.U)
      dut.io.mem_wen.poke(true)
      dut.io.wb_rd.poke(7.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.FWD_MEM.U)
    }
  }
}