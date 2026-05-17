package valence.pipeline

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class PipelineRegSpec extends AnyFlatSpec with Matchers {

  behavior of "PipelineReg"

  it should "pass data through after one cycle" in {
    simulate(new PipelineReg(UInt(64.W))) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.in.poke(42.U)
      dut.io.stall.poke(false)
      dut.io.flush.poke(false)
      dut.clock.step()

      dut.io.out.expect(42.U)
    }
  }

  it should "hold value when stalled" in {
    simulate(new PipelineReg(UInt(64.W))) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // load 42
      dut.io.in.poke(42.U)
      dut.io.stall.poke(false)
      dut.io.flush.poke(false)
      dut.clock.step()

      // stall — new data should not overwrite
      dut.io.in.poke(99.U)
      dut.io.stall.poke(true)
      dut.clock.step()

      // should still hold 42
      dut.io.out.expect(42.U)
    }
  }

  it should "flush to zero on flush signal" in {
    simulate(new PipelineReg(UInt(64.W))) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // load 42
      dut.io.in.poke(42.U)
      dut.io.stall.poke(false)
      dut.io.flush.poke(false)
      dut.clock.step()

      // flush — clears the register
      dut.io.flush.poke(true)
      dut.clock.step()

      dut.io.out.expect(0.U)
    }
  }

  it should "reset to zero" in {
    simulate(new PipelineReg(UInt(64.W))) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.out.expect(0.U)
    }
  }
}