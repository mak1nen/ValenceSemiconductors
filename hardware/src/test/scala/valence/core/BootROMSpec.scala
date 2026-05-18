package valence.soc

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class BootROMSpec extends AnyFlatSpec with Matchers {

  behavior of "BootROM"

  def test(fn: BootROM => Unit): Unit =
    simulate(new BootROM) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      fn(dut)
    }

  it should "return first instruction at reset vector" in {
    test { dut =>
      dut.io.addr.poke(MemoryMap.RESET_VECTOR.U)
      dut.io.valid.poke(true)
      dut.clock.step()
      // first instruction should be non-zero
      val data = dut.io.data.peek().litValue
      assert(data != 0, "first instruction should not be zero")
    }
  }

  it should "return zero for out of range address" in {
    test { dut =>
      dut.io.addr.poke(0x9999999L.U)
      dut.io.valid.poke(true)
      dut.clock.step()
      dut.io.data.expect(0.U)
    }
  }

  it should "return zero when not valid" in {
    test { dut =>
      dut.io.addr.poke(MemoryMap.RESET_VECTOR.U)
      dut.io.valid.poke(false)
      dut.clock.step()
      dut.io.data.expect(0.U)
    }
  }

  it should "return sequential instructions" in {
    test { dut =>
      dut.io.valid.poke(true)
      dut.io.addr.poke(MemoryMap.RESET_VECTOR.U)
      dut.clock.step()
      val instr0 = dut.io.data.peek().litValue

      dut.io.addr.poke((MemoryMap.RESET_VECTOR + 4).U)
      dut.clock.step()
      val instr1 = dut.io.data.peek().litValue

      assert(instr0 != instr1, "sequential instructions should differ")
    }
  }
}