package valence.soc

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

// =============================================================================
// SRAMSpec — verifies dual-port SRAM (data port + fetch port)
//
// Port 0 (data)  — DCache: read/write with byte enables
// Port 1 (fetch) — ICache: read-only instruction fetch
//
// Notes:
//   - Uses BigInt for 64-bit literals to avoid Scala Long overflow
//   - SyncReadMem is not zero-initialized — unwritten reads return garbage
//     so we only assert on addresses we have written
// =============================================================================
class SRAMSpec extends AnyFlatSpec with Matchers {

  behavior of "SRAM"

  val BASE = MemoryMap.SRAM_BASE.toLong

  def test(fn: SRAM => Unit): Unit =
    simulate(new SRAM) { dut =>
      dut.reset.poke(true)
      dut.clock.step(2)
      dut.reset.poke(false)
      dut.io.addr.poke(BASE.U)
      dut.io.wen.poke(false)
      dut.io.wdata.poke(0.U)
      dut.io.wstrb.poke(0.U)
      dut.io.valid.poke(false)
      dut.io.fetch_addr.poke(BASE.U)
      dut.io.fetch_valid.poke(false)
      fn(dut)
    }

  // ── Port 0: data port ─────────────────────────────────────────────────────

  it should "write and read back on data port" in {
    test { dut =>
      val value = BigInt("CAFEBABECAFEBABE", 16)
      dut.io.addr.poke(BASE.U)
      dut.io.wen.poke(true)
      dut.io.wdata.poke(value.U)
      dut.io.wstrb.poke(0xFF.U)
      dut.io.valid.poke(true)
      dut.clock.step(1)

      dut.io.wen.poke(false)
      dut.clock.step(1)
      dut.io.rdata.expect(value.U)
    }
  }

  it should "write to multiple addresses without aliasing" in {
    test { dut =>
      val v0 = BigInt("AAAAAAAAAAAAAAAA", 16)
      val v1 = BigInt("BBBBBBBBBBBBBBBB", 16)

      dut.io.wen.poke(true)
      dut.io.wstrb.poke(0xFF.U)
      dut.io.valid.poke(true)

      dut.io.addr.poke(BASE.U)
      dut.io.wdata.poke(v0.U)
      dut.clock.step(1)

      dut.io.addr.poke((BASE + 8).U)
      dut.io.wdata.poke(v1.U)
      dut.clock.step(1)

      dut.io.wen.poke(false)
      dut.io.addr.poke(BASE.U)
      dut.clock.step(1)
      dut.io.rdata.expect(v0.U)

      dut.io.addr.poke((BASE + 8).U)
      dut.clock.step(1)
      dut.io.rdata.expect(v1.U)
    }
  }

  it should "read back exactly what was written" in {
    test { dut =>
      val value = BigInt("0123456789ABCDEF", 16)
      dut.io.addr.poke((BASE + 16).U)
      dut.io.wen.poke(true)
      dut.io.wdata.poke(value.U)
      dut.io.wstrb.poke(0xFF.U)
      dut.io.valid.poke(true)
      dut.clock.step(1)

      dut.io.wen.poke(false)
      dut.clock.step(1)
      dut.io.rdata.expect(value.U)
    }
  }

  // ── Port 1: fetch port ────────────────────────────────────────────────────

  it should "read data written by data port via fetch port" in {
    test { dut =>
      val value = BigInt("200002B700000513", 16)
      dut.io.addr.poke(BASE.U)
      dut.io.wen.poke(true)
      dut.io.wdata.poke(value.U)
      dut.io.wstrb.poke(0xFF.U)
      dut.io.valid.poke(true)
      dut.clock.step(1)

      dut.io.valid.poke(false)
      dut.io.fetch_addr.poke(BASE.U)
      dut.io.fetch_valid.poke(true)
      dut.clock.step(1)

      dut.io.fetch_data.expect(value.U)
    }
  }

  it should "return zero on fetch port when fetch_valid is false" in {
    test { dut =>
      dut.io.fetch_addr.poke(BASE.U)
      dut.io.fetch_valid.poke(false)
      dut.clock.step(2)
      dut.io.fetch_data.expect(0.U)
    }
  }

  // ── Simultaneous access ───────────────────────────────────────────────────

  it should "allow simultaneous reads on both ports at different addresses" in {
    test { dut =>
      val v0 = BigInt("1111111111111111", 16)
      val v1 = BigInt("2222222222222222", 16)

      dut.io.wen.poke(true)
      dut.io.wstrb.poke(0xFF.U)
      dut.io.valid.poke(true)

      dut.io.addr.poke(BASE.U)
      dut.io.wdata.poke(v0.U)
      dut.clock.step(1)

      dut.io.addr.poke((BASE + 8).U)
      dut.io.wdata.poke(v1.U)
      dut.clock.step(1)

      dut.io.wen.poke(false)
      dut.io.addr.poke(BASE.U)
      dut.io.valid.poke(true)
      dut.io.fetch_addr.poke((BASE + 8).U)
      dut.io.fetch_valid.poke(true)
      dut.clock.step(1)

      dut.io.rdata.expect(v0.U)
      dut.io.fetch_data.expect(v1.U)
    }
  }
}