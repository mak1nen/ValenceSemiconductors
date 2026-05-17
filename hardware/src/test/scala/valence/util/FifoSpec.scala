package valence.util

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class FifoSpec extends AnyFlatSpec with Matchers {

  behavior of "FIFO"

  it should "enqueue and dequeue a single element" in {
    simulate(new Fifo(UInt(8.W), depth = 4)) { dut =>
      // apply reset
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      // enqueue 42
      dut.io.enq.valid.poke(true)
      dut.io.enq.bits.poke(42)
      dut.io.deq.ready.poke(false)
      dut.clock.step()
      dut.io.enq.valid.poke(false)

      // check deq
      dut.io.deq.valid.expect(true)
      dut.io.deq.bits.expect(42)
    }
  }

  it should "be full when depth exceeded" in {
    simulate(new Fifo(UInt(8.W), depth = 2)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.deq.ready.poke(false)
      dut.io.enq.valid.poke(true)

      dut.io.enq.bits.poke(1)
      dut.clock.step()
      dut.io.enq.bits.poke(2)
      dut.clock.step()

      dut.io.enq.ready.expect(false)
    }
  }

  it should "be empty after reset" in {
    simulate(new Fifo(UInt(8.W), depth = 4)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.deq.valid.expect(false)
      dut.io.enq.ready.expect(true)
    }
  }

  it should "maintain FIFO order" in {
    simulate(new Fifo(UInt(8.W), depth = 4)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)

      dut.io.deq.ready.poke(false)
      dut.io.enq.valid.poke(true)

      for (i <- 1 to 3) {
        dut.io.enq.bits.poke(i)
        dut.clock.step()
      }
      dut.io.enq.valid.poke(false)
      dut.io.deq.ready.poke(true)

      for (i <- 1 to 3) {
        dut.io.deq.valid.expect(true)
        dut.io.deq.bits.expect(i)
        dut.clock.step()
      }
    }
  }
}