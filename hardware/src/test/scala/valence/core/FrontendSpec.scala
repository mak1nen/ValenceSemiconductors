package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.soc.MemoryMap

class FrontendSpec extends AnyFlatSpec with Matchers {

  behavior of "Frontend"

  def test(fn: Frontend => Unit): Unit =
    simulate(new Frontend) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.stall.poke(false)
      dut.io.flush.poke(false)
      dut.io.redirect.poke(false)
      dut.io.target.poke(0.U)
      dut.io.instr.poke(0x00000013.U)  // NOP
      dut.io.icache_stall.poke(false)
      fn(dut)
    }

  it should "start at reset vector" in {
    test { dut =>
      dut.io.out_pc.expect(MemoryMap.RESET_VECTOR.U)
    }
  }

  it should "increment PC by 4 each cycle" in {
    test { dut =>
      dut.clock.step()
      dut.io.out_pc.expect((MemoryMap.RESET_VECTOR + 4).U)
      dut.clock.step()
      dut.io.out_pc.expect((MemoryMap.RESET_VECTOR + 8).U)
    }
  }

  it should "hold PC when stalled" in {
    test { dut =>
      dut.clock.step()
      val pc = dut.io.out_pc.peek().litValue
      dut.io.stall.poke(true)
      dut.clock.step()
      dut.io.out_pc.expect(pc.U)
    }
  }

  it should "redirect PC on branch" in {
    test { dut =>
      dut.io.redirect.poke(true)
      dut.io.target.poke(0x80001000L.U)
      dut.clock.step()
      dut.io.out_pc.expect(0x80001000L.U)
    }
  }

  it should "output NOP when flushed" in {
    test { dut =>
      dut.io.flush.poke(true)
      dut.io.instr.poke(0xDEADBEEFL.U)
      dut.clock.step()
      dut.io.out_instr.expect(0x00000013.U)  // NOP
    }
  }

  it should "hold PC when icache stalls" in {
    test { dut =>
      dut.clock.step()
      val pc = dut.io.out_pc.peek().litValue
      dut.io.icache_stall.poke(true)
      dut.clock.step()
      dut.io.out_pc.expect(pc.U)
    }
  }
}