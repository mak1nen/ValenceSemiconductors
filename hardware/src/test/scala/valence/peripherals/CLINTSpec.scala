package valence.peripherals

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.soc.MemoryMap

class CLINTSpec extends AnyFlatSpec with Matchers {

  behavior of "CLINT"

  def test(fn: CLINT => Unit): Unit =
    simulate(new CLINT(nHarts = 1)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.addr.poke(0.U)
      dut.io.wen.poke(false)
      dut.io.wdata.poke(0.U)
      dut.io.valid.poke(false)
      fn(dut)
    }

  it should "increment mtime every cycle" in {
    test { dut =>
      dut.io.valid.poke(true)
      dut.io.addr.poke((MemoryMap.CLINT_BASE + MemoryMap.CLINT_MTIME).U)

      dut.clock.step()
      val t0 = dut.io.rdata.peek().litValue

      dut.clock.step()
      val t1 = dut.io.rdata.peek().litValue

      assert(t1 > t0, s"mtime should increment: t0=$t0 t1=$t1")
    }
  }

  it should "fire timer interrupt when mtime >= mtimecmp" in {
    test { dut =>
      // set mtimecmp to a small value so timer fires quickly
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke((MemoryMap.CLINT_BASE + MemoryMap.CLINT_MTIMECMP).U)
      dut.io.wdata.poke(5.U)
      dut.clock.step()
      dut.io.wen.poke(false)

      // step until mtime >= 5
      dut.clock.step(10)
      dut.io.timer_irq(0).expect(true)
    }
  }

  it should "not fire timer interrupt before mtimecmp" in {
    test { dut =>
      // set mtimecmp far in future
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke((MemoryMap.CLINT_BASE + MemoryMap.CLINT_MTIMECMP).U)
      dut.io.wdata.poke(0xFFFFFFFFL.U)
      dut.clock.step()
      dut.io.wen.poke(false)

      dut.clock.step(5)
      dut.io.timer_irq(0).expect(false)
    }
  }

  it should "set software interrupt via msip" in {
    test { dut =>
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke((MemoryMap.CLINT_BASE + MemoryMap.CLINT_MSIP).U)
      dut.io.wdata.poke(1.U)
      dut.clock.step()
      dut.io.soft_irq(0).expect(true)
    }
  }

  it should "clear software interrupt when msip written 0" in {
    test { dut =>
      // set msip
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke((MemoryMap.CLINT_BASE + MemoryMap.CLINT_MSIP).U)
      dut.io.wdata.poke(1.U)
      dut.clock.step()

      // clear msip
      dut.io.wdata.poke(0.U)
      dut.clock.step()
      dut.io.soft_irq(0).expect(false)
    }
  }
}