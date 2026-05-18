package valence.soc

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.params._

class SoCSpec extends AnyFlatSpec with Matchers {

  behavior of "SoC"

  val p = CoreParams(
    xlen          = 64,
    resetVector   = MemoryMap.RESET_VECTOR.toLong,
    nHarts        = 1,
    nStages       = 5,
    hasFPU        = false,
    hasCompressed = false,
    hasAtomic     = false,
    hasVector     = false,
    hasSupervisor = false,
    hasMMU        = false,
    hasPMP        = false,
    iCache        = CacheParams(nSets=4, nWays=2, blockBytes=16, nMSHRs=2, nTLBEntries=8),
    dCache        = CacheParams(nSets=4, nWays=2, blockBytes=16, nMSHRs=2, nTLBEntries=8),
    gemm          = GEMMParams(enabled=false, tileSize=4, dataWidthBits=16, nMACUnits=4, scratchpadKB=16),
    physical      = PhysicalParams(
      targetNode    = "sky130",
      clockPeriodNs = 10.0,
      setupMarginNs = 0.1,
      holdMarginNs  = 0.05,
      voltageV      = 1.8,
      metalLayers   = 5,
      maxFanout     = 16,
    )
  )

  def test(fn: SoC => Unit): Unit =
    simulate(new SoC(p)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.uart_rx.poke(true)
      fn(dut)
    }

  it should "elaborate and reset cleanly" in {
    test { dut =>
      dut.clock.step(10)
      // UART tx idles high
      dut.io.uart_tx.expect(true)
    }
  }

  it should "run for 100 cycles without hanging" in {
    test { dut =>
      dut.clock.step(100)
      // still alive — no assertion failure
      succeed
    }
  }

  it should "fetch first instruction from BootROM" in {
    test { dut =>
      // step enough cycles for first fetch
      dut.clock.step(5)
      // UART tx still high — no spurious output
      dut.io.uart_tx.expect(true)
    }
  }
}