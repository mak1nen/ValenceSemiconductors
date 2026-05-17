package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class RegFileSpec extends AnyFlatSpec with Matchers {

  behavior of "RegFile"

  it should "read zero from r0 always" in {
    simulate(new RegFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // try to write to r0
      dut.io.wen.poke(true)
      dut.io.waddr.poke(0.U)
      dut.io.wdata.poke(999.U)
      dut.clock.step()

      // r0 must always read as 0
      dut.io.raddr1.poke(0.U)
      dut.io.raddr2.poke(0.U)
      dut.io.rdata1.expect(0.U)
      dut.io.rdata2.expect(0.U)
    }
  }

  it should "write and read back a value" in {
    simulate(new RegFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // write 42 to r1
      dut.io.wen.poke(true)
      dut.io.waddr.poke(1.U)
      dut.io.wdata.poke(42.U)
      dut.clock.step()
      dut.io.wen.poke(false)

      // read back from r1
      dut.io.raddr1.poke(1.U)
      dut.io.rdata1.expect(42.U)
    }
  }

  it should "support two simultaneous reads" in {
    simulate(new RegFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // write to r1 and r2
      dut.io.wen.poke(true)
      dut.io.waddr.poke(1.U)
      dut.io.wdata.poke(10.U)
      dut.clock.step()

      dut.io.waddr.poke(2.U)
      dut.io.wdata.poke(20.U)
      dut.clock.step()
      dut.io.wen.poke(false)

      // read both simultaneously
      dut.io.raddr1.poke(1.U)
      dut.io.raddr2.poke(2.U)
      dut.io.rdata1.expect(10.U)
      dut.io.rdata2.expect(20.U)
    }
  }

  it should "write to all 31 registers and read back correctly" in {
    simulate(new RegFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // write i to register i for all r1-r31
      for (i <- 1 to 31) {
        dut.io.wen.poke(true)
        dut.io.waddr.poke(i.U)
        dut.io.wdata.poke((i * 100).U)
        dut.clock.step()
      }
      dut.io.wen.poke(false)

      // verify all
      for (i <- 1 to 31) {
        dut.io.raddr1.poke(i.U)
        dut.io.rdata1.expect((i * 100).U)
      }
    }
  }

  it should "not write when wen is low" in {
    simulate(new RegFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // write 42 to r5
      dut.io.wen.poke(true)
      dut.io.waddr.poke(5.U)
      dut.io.wdata.poke(42.U)
      dut.clock.step()

      // try to overwrite with wen=false
      dut.io.wen.poke(false)
      dut.io.waddr.poke(5.U)
      dut.io.wdata.poke(999.U)
      dut.clock.step()

      // should still be 42
      dut.io.raddr1.poke(5.U)
      dut.io.rdata1.expect(42.U)
    }
  }
}