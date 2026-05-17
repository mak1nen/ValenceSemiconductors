package valence.caches

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class DCacheSpec extends AnyFlatSpec with Matchers {

  behavior of "DCache"

  def test(fn: DCache => Unit): Unit =
    simulate(new DCache(nSets = 4, nWays = 2, blockBytes = 16)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.req.valid.poke(false)
      dut.io.req.addr.poke(0.U)
      dut.io.req.wen.poke(false)
      dut.io.req.wdata.poke(0.U)
      dut.io.mem.valid.poke(false)
      dut.io.mem.data.poke(0.U)
      fn(dut)
    }

  it should "miss on cold read and signal stall" in {
    test { dut =>
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x1000.U)
      dut.io.req.wen.poke(false)
      dut.clock.step()
      dut.io.resp.stall.expect(true)
      dut.io.resp.valid.expect(false)
    }
  }

  it should "return data after memory fill on read" in {
    test { dut =>
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x1000.U)
      dut.io.req.wen.poke(false)
      dut.clock.step()

      dut.io.mem.valid.poke(true)
      dut.io.mem.data.poke(0xABCD1234L.U)
      dut.clock.step()

      dut.io.mem.valid.poke(false)
      dut.clock.step()

      dut.io.resp.valid.expect(true)
      dut.io.resp.stall.expect(false)
      dut.io.resp.rdata.expect(0xABCD1234L.U)
    }
  }

  it should "hit on second read to same address" in {
    test { dut =>
      // first access — miss + fill
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x2000.U)
      dut.io.req.wen.poke(false)
      dut.clock.step()

      dut.io.mem.valid.poke(true)
      dut.io.mem.data.poke(0x12345678L.U)
      dut.clock.step()
      dut.io.mem.valid.poke(false)
      dut.clock.step()

      // second access — hit
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x2000.U)
      dut.clock.step()
      dut.io.resp.valid.expect(true)
      dut.io.resp.stall.expect(false)
      dut.io.resp.rdata.expect(0x12345678L.U)
    }
  }

  it should "write data and read it back" in {
    test { dut =>
      // fill cache line first
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x3000.U)
      dut.io.req.wen.poke(false)
      dut.clock.step()

      dut.io.mem.valid.poke(true)
      dut.io.mem.data.poke(0x0L.U)
      dut.clock.step()
      dut.io.mem.valid.poke(false)
      dut.clock.step()

      // write new value
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x3000.U)
      dut.io.req.wen.poke(true)
      dut.io.req.wdata.poke(0xBEEF0000L.U)
      dut.clock.step()
      dut.io.req.wen.poke(false)

      // read back
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x3000.U)
      dut.clock.step()
      dut.io.resp.valid.expect(true)
      dut.io.resp.rdata.expect(0xBEEF0000L.U)
    }
  }

  it should "not respond when request not valid" in {
    test { dut =>
      dut.io.req.valid.poke(false)
      dut.clock.step()
      dut.io.resp.valid.expect(false)
    }
  }
}