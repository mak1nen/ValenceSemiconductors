package valence.pipeline

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

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
      dut.io.mem_rd.poke(0.U)
      dut.io.mem_wen.poke(false)
      dut.io.wb_rd.poke(0.U)
      dut.io.wb_wen.poke(false)
      fn(dut)
    }

  it should "select no forwarding when no hazard" in {
    test { dut =>
      dut.io.ex_rs1.poke(1.U)
      dut.io.ex_rs2.poke(2.U)
      dut.io.mem_rd.poke(5.U)
      dut.io.mem_wen.poke(true)
      dut.io.wb_rd.poke(6.U)
      dut.io.wb_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.NO_FWD.U)
      dut.io.fwd_b.expect(ForwardingUnit.NO_FWD.U)
    }
  }

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

  it should "not forward when rd is r0" in {
    test { dut =>
      dut.io.ex_rs1.poke(0.U)
      dut.io.mem_rd.poke(0.U)
      dut.io.mem_wen.poke(true)
      dut.clock.step()
      dut.io.fwd_a.expect(ForwardingUnit.NO_FWD.U)
    }
  }
}