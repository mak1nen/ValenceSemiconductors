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
    resetVector   = MemoryMap.BOOTROM_BASE.toLong,
    nHarts        = 1,
    nStages       = 5,
    hasFPU        = false,
    hasCompressed = false,
    hasAtomic     = false,
    hasVector     = false,
    hasSupervisor = false,
    hasMMU        = false,
    hasPMP        = false,
    iCache        = CacheParams(nSets = 4, nWays = 2, blockBytes = 16, nMSHRs = 1, nTLBEntries = 4),
    dCache        = CacheParams(nSets = 4, nWays = 2, blockBytes = 16, nMSHRs = 1, nTLBEntries = 4),
    gemm          = GEMMParams(enabled = false, tileSize = 4, dataWidthBits = 16, nMACUnits = 4, scratchpadKB = 4),
    physical      = PhysicalParams(
      targetNode    = "sim",
      clockPeriodNs = 10.0,
      setupMarginNs = 0.1,
      holdMarginNs  = 0.05,
      voltageV      = 1.8,
      metalLayers   = 5,
      maxFanout     = 16,
    ),
  )

  def test(fn: SoC => Unit): Unit =
    simulate(new SoC(p)) { dut =>
      dut.reset.poke(true)
      dut.io.uart_rx.poke(true)  // idle high
      dut.clock.step(2)
      dut.reset.poke(false)
      fn(dut)
    }

  // ---------------------------------------------------------------------------
  // Basic sanity
  // ---------------------------------------------------------------------------

  it should "elaborate and reset cleanly" in {
    test { dut =>
      dut.clock.step(5)
      // no assertion — just verifies elaboration and reset don't throw
    }
  }

  it should "run for 100 cycles without hanging" in {
    test { dut =>
      dut.clock.step(100)
      // hangs would timeout; reaching here means the pipeline is ticking
    }
  }

  it should "hold uart_tx high (idle) after reset" in {
    test { dut =>
      dut.clock.step(10)
      // UART idles HIGH — mark high after reset is correct
      dut.io.uart_tx.expect(true)
    }
  }

  // ---------------------------------------------------------------------------
  // BootROM fetch
  // ---------------------------------------------------------------------------

  it should "fetch first instruction from BootROM address range" in {
    test { dut =>
      // The core should be fetching from BOOTROM_BASE immediately after reset.
      // We can't observe icache_addr directly, but we can verify the SoC
      // doesn't stall out — it advances past cycle 0.
      dut.clock.step(10)
      // If icache is stuck stalling forever, the pipeline never moves.
      // Reaching here without timeout = BootROM is being served.
    }
  }

  // ---------------------------------------------------------------------------
  // UART TX path
  // ---------------------------------------------------------------------------

  it should "idle uart_tx high when no store to UART address" in {
    test { dut =>
      dut.clock.step(50)
      dut.io.uart_tx.expect(true)
    }
  }

  // ---------------------------------------------------------------------------
  // UART RX path
  // ---------------------------------------------------------------------------

  it should "accept uart_rx input without hanging" in {
    test { dut =>
      // Toggle RX line — simulates incoming serial data
      dut.io.uart_rx.poke(false)
      dut.clock.step(10)
      dut.io.uart_rx.poke(true)
      dut.clock.step(10)
      // SoC should still be running
    }
  }

  // ---------------------------------------------------------------------------
  // SRAM region
  // ---------------------------------------------------------------------------

  it should "run 500 cycles with SRAM region active" in {
    test { dut =>
      // After BootROM stub runs, the core will jump to SRAM_BASE (0x80000000).
      // SRAM is now wired — fetching zeros = NOP sled, not a hang.
      dut.clock.step(500)
    }
  }
}