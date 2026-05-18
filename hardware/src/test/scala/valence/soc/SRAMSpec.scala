package valence.soc

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class SRAMSpec extends AnyFlatSpec with Matchers {

  behavior of "SRAM"

  def test(fn: SRAM => Unit): Unit =
    simulate(new SRAM(65536)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.valid.poke(false)
      dut.io.wen.poke(false)
      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.io.wdata.poke(0.U)
      dut.io.wstrb.poke(0xFF.U)
      fn(dut)
    }

  it should "write and read back a value" in {
    test { dut =>
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.io.wdata.poke(BigInt("DEADBEEFCAFEBABE", 16).U)
      dut.clock.step()

      dut.io.wen.poke(false)
      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.clock.step()

      dut.io.rdata.expect(BigInt("DEADBEEFCAFEBABE", 16).U)
    }
  }

  it should "write to different addresses independently" in {
    test { dut =>
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)

      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.io.wdata.poke(0xAAAAAAAAL.U)
      dut.clock.step()

      dut.io.addr.poke((MemoryMap.SRAM_BASE + 8).U)
      dut.io.wdata.poke(0xBBBBBBBBL.U)
      dut.clock.step()

      dut.io.wen.poke(false)
      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.clock.step()
      dut.io.rdata.expect(0xAAAAAAAAL.U)

      dut.io.addr.poke((MemoryMap.SRAM_BASE + 8).U)
      dut.clock.step()
      dut.io.rdata.expect(0xBBBBBBBBL.U)
    }
  }

  it should "not write when valid is low" in {
    test { dut =>
      // write a known value first
      dut.io.valid.poke(true)
      dut.io.wen.poke(true)
      dut.io.addr.poke(MemoryMap.SRAM_BASE.U)
      dut.io.wdata.poke(0x1234L.U)
      dut.clock.step()

      // try to overwrite with valid=false
      dut.io.valid.poke(false)
      dut.io.wdata.poke(0x9999L.U)
      dut.clock.step()

      // read back — should still be 0x1234
      dut.io.valid.poke(true)
      dut.io.wen.poke(false)
      dut.clock.step()
      dut.io.rdata.expect(0x1234L.U)
    }
  }
}