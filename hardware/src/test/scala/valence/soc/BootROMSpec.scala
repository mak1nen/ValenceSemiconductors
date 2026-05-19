package valence.soc

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

// =============================================================================
// BootROMSpec — verifies the BootROM trampoline
//
// Checks that:
//   1. The ROM responds correctly to valid addresses
//   2. The ROM returns zero for out-of-range addresses
//   3. The ROM returns zero when io_valid is false
//   4. The jump instruction targets SRAM_BASE (0x20000000)
//   5. The hart ID is set to 0 (a0 = 0)
// =============================================================================
class BootROMSpec extends AnyFlatSpec with Matchers {

  behavior of "BootROM"

  def read(dut: BootROM, addr: Long): Long = {
    dut.io.addr.poke(addr.U)
    dut.io.valid.poke(true)
    dut.clock.step(1)
    dut.io.data.peek().litValue.toLong
  }

  it should "return first instruction at reset vector" in {
    simulate(new BootROM) { dut =>
      dut.reset.poke(true); dut.clock.step(); dut.reset.poke(false)
      dut.io.addr.poke(MemoryMap.RESET_VECTOR.U)
      dut.io.valid.poke(true)
      dut.clock.step()
      assert(dut.io.data.peek().litValue != 0, "first instruction should not be zero")
    }
  }

  it should "return zero for out of range address" in {
    simulate(new BootROM) { dut =>
      // Use an address well outside BOOTROM_BASE + size
      val instr = read(dut, (MemoryMap.BOOTROM_BASE + MemoryMap.BOOTROM_SIZE + 0x100).toLong)
      instr shouldBe 0L
    }
  }

  it should "return zero when io_valid is false" in {
    simulate(new BootROM) { dut =>
      dut.io.addr.poke(MemoryMap.BOOTROM_BASE.U)
      dut.io.valid.poke(false)
      dut.clock.step(1)
      dut.io.data.expect(0.U)
    }
  }

  it should "return sequential instructions" in {
    simulate(new BootROM) { dut =>
      dut.reset.poke(true); dut.clock.step(); dut.reset.poke(false)
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

  it should "contain a lui instruction targeting SRAM_BASE" in {
    simulate(new BootROM) { dut =>
      // Read all ROM words and look for lui t0 with SRAM upper immediate
      val sramUpper = (MemoryMap.SRAM_BASE >> 12) & 0xFFFFF  // 0x20000
      val luiOpcode = 0x37L  // U-type opcode for lui
      val luiRd     = 0x5L   // rd = t0 = x5
      // lui t0, imm encoding: imm[31:12] | rd[11:7] | opcode[6:0]
      val expectedLui = (sramUpper << 12) | (luiRd << 7) | luiOpcode

      var found = false
      for (i <- 0 until 8) {
        val addr = MemoryMap.BOOTROM_BASE.toLong + (i * 4)
        val instr = read(dut, addr)
        if (instr == expectedLui) found = true
      }
      found shouldBe true
    }
  }

  it should "contain li a0, 0 (hart ID = 0)" in {
    simulate(new BootROM) { dut =>
      // addi a0, x0, 0 = 0x00000513
      val liA0Zero = 0x00000513L
      var found = false
      for (i <- 0 until 8) {
        val addr = MemoryMap.BOOTROM_BASE.toLong + (i * 4)
        val instr = read(dut, addr)
        if (instr == liA0Zero) found = true
      }
      found shouldBe true
    }
  }

  it should "contain jr t0 (jalr x0, t0, 0)" in {
    simulate(new BootROM) { dut =>
      // jalr x0, t0, 0 = 0x00028067
      val jrT0 = 0x00028067L
      var found = false
      for (i <- 0 until 8) {
        val addr = MemoryMap.BOOTROM_BASE.toLong + (i * 4)
        val instr = read(dut, addr)
        if (instr == jrT0) found = true
      }
      found shouldBe true
    }
  }

  it should "serve sequential instructions without gaps" in {
    simulate(new BootROM) { dut =>
      // Every word from base to base+5 should be non-zero except the loop
      var nonZeroCount = 0
      for (i <- 0 until 6) {
        val addr = MemoryMap.BOOTROM_BASE.toLong + (i * 4)
        val instr = read(dut, addr)
        if (instr != 0L) nonZeroCount += 1
      }
      nonZeroCount should be >= 4
    }
  }
}