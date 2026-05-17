package valence.caches

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class ICacheSpec extends AnyFlatSpec with Matchers {

  behavior of "ICache"

  def test(fn: ICache => Unit): Unit =
    simulate(new ICache(nSets = 4, nWays = 2, blockBytes = 16)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.req.valid.poke(false)
      dut.io.req.addr.poke(0.U)
      dut.io.mem.valid.poke(false)
      dut.io.mem.data.poke(0.U)
      fn(dut)
    }

  it should "miss on cold start and signal stall" in {
    test { dut =>
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x1000.U)
      dut.clock.step()
      dut.io.resp.stall.expect(true)
      dut.io.resp.valid.expect(false)
    }
  }

  it should "return valid data after memory fill" in {
    test { dut =>
      // request address
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x1000.U)
      dut.clock.step()

      // miss — memory responds with data
      dut.io.mem.valid.poke(true)
      dut.io.mem.data.poke(0xDEADBEEFL.U)
      dut.clock.step()

      dut.io.mem.valid.poke(false)
      dut.clock.step()

      // now should hit
      dut.io.resp.valid.expect(true)
      dut.io.resp.stall.expect(false)
      dut.io.resp.data.expect(0xDEADBEEFL.U)
    }
  }

  it should "hit on second access to same address" in {
    test { dut =>
      // first access — miss + fill
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x2000.U)
      dut.clock.step()

      dut.io.mem.valid.poke(true)
      dut.io.mem.data.poke(0xCAFEBABEL.U)
      dut.clock.step()
      dut.io.mem.valid.poke(false)
      dut.clock.step()

      // second access — should hit immediately
      dut.io.req.valid.poke(true)
      dut.io.req.addr.poke(0x2000.U)
      dut.clock.step()
      dut.io.resp.valid.expect(true)
      dut.io.resp.stall.expect(false)
      dut.io.resp.data.expect(0xCAFEBABEL.U)
    }
  }

  it should "stall when request is not valid" in {
    test { dut =>
      dut.io.req.valid.poke(false)
      dut.clock.step()
      dut.io.resp.valid.expect(false)
    }
  }
}