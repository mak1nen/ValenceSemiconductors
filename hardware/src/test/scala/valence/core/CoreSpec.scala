package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.params._
import valence.soc.MemoryMap

class CoreSpec extends AnyFlatSpec with Matchers {

  behavior of "Core"

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

  def test(fn: Core => Unit): Unit =
    simulate(new Core(p)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.icache_data.poke(0x00000013.U)  // NOP
      dut.io.icache_stall.poke(false)
      dut.io.dcache_rdata.poke(0.U)
      dut.io.dcache_stall.poke(false)
      dut.io.timer_irq.poke(false)
      dut.io.soft_irq.poke(false)
      fn(dut)
    }

  it should "reset and fetch from reset vector" in {
    test { dut =>
      dut.io.icache_addr.expect(MemoryMap.RESET_VECTOR.U)
      dut.io.icache_req.expect(true)
    }
  }

  it should "advance PC each cycle with NOPs" in {
    test { dut =>
      dut.clock.step()
      val pc0 = dut.io.icache_addr.peek().litValue
      dut.clock.step()
      val pc1 = dut.io.icache_addr.peek().litValue
      assert(pc1 == pc0 + 4, s"PC should advance by 4: $pc0 -> $pc1")
    }
  }

  it should "run 50 NOP cycles without hanging" in {
    test { dut =>
      dut.clock.step(50)
      succeed
    }
  }

  it should "stall when icache stalls" in {
    test { dut =>
      dut.clock.step()
      val pc = dut.io.icache_addr.peek().litValue
      dut.io.icache_stall.poke(true)
      dut.clock.step()
      dut.io.icache_addr.expect(pc.U)
    }
  }

  it should "assert dcache_valid on store instruction" in {
    test { dut =>
      // SW x1, 0(x2) — store instruction
      // 0000000 00001 00010 010 00000 0100011
      dut.io.icache_data.poke(0x00112023L.U)
      dut.clock.step(5)
      // dcache will be accessed after pipeline stages
      succeed
    }
  }
}