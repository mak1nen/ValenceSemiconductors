package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class WritebackSpec extends AnyFlatSpec with Matchers {

  behavior of "Writeback"

  def test(fn: Writeback => Unit): Unit =
    simulate(new Writeback) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.in.result.poke(0.U)
      dut.io.in.rd.poke(0.U)
      dut.io.in.valid.poke(false)
      fn(dut)
    }

  it should "write result to rd when valid" in {
    test { dut =>
      dut.io.in.result.poke(42.U)
      dut.io.in.rd.poke(5.U)
      dut.io.in.valid.poke(true)
      dut.clock.step()
      dut.io.wen.expect(true)
      dut.io.waddr.expect(5.U)
      dut.io.wdata.expect(42.U)
    }
  }

  it should "not write when not valid" in {
    test { dut =>
      dut.io.in.result.poke(42.U)
      dut.io.in.rd.poke(5.U)
      dut.io.in.valid.poke(false)
      dut.clock.step()
      dut.io.wen.expect(false)
    }
  }

  it should "not write to r0" in {
    test { dut =>
      dut.io.in.result.poke(42.U)
      dut.io.in.rd.poke(0.U)
      dut.io.in.valid.poke(true)
      dut.clock.step()
      dut.io.wen.expect(false)
    }
  }
}