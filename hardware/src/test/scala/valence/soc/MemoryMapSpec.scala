package valence.soc

import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

// Pure Scala test — no Chisel simulation needed
// Verifies memory map constants are correct and non-overlapping

class MemoryMapSpec extends AnyFlatSpec with Matchers {

  behavior of "MemoryMap"

  it should "have reset vector inside BootROM" in {
    assert(
      MemoryMap.RESET_VECTOR >= MemoryMap.BOOTROM_BASE &&
      MemoryMap.RESET_VECTOR <  MemoryMap.BOOTROM_BASE + MemoryMap.BOOTROM_SIZE,
      "reset vector must be inside BootROM"
    )
  }

  it should "have all regions 4KB aligned" in {
    val alignment = BigInt("1000", 16)
    assert(MemoryMap.BOOTROM_BASE % alignment == 0)
    assert(MemoryMap.CLINT_BASE   % alignment == 0)
    assert(MemoryMap.PLIC_BASE    % alignment == 0)
    assert(MemoryMap.UART_BASE    % alignment == 0)
    assert(MemoryMap.SRAM_BASE    % alignment == 0)
    assert(MemoryMap.DRAM_BASE    % alignment == 0)
  }

  it should "have non-overlapping regions" in {
    val regions = Seq(
      ("BOOTROM", MemoryMap.BOOTROM_BASE, MemoryMap.BOOTROM_SIZE),
      ("CLINT",   MemoryMap.CLINT_BASE,   MemoryMap.CLINT_SIZE),
      ("PLIC",    MemoryMap.PLIC_BASE,    MemoryMap.PLIC_SIZE),
      ("UART",    MemoryMap.UART_BASE,    MemoryMap.UART_SIZE),
      ("SRAM",    MemoryMap.SRAM_BASE,    MemoryMap.SRAM_SIZE),
      ("DRAM",    MemoryMap.DRAM_BASE,    MemoryMap.DRAM_SIZE),
    )

    for {
      (nameA, baseA, sizeA) <- regions
      (nameB, baseB, sizeB) <- regions
      if nameA != nameB
    } {
      val endA = baseA + sizeA
      val endB = baseB + sizeB
      val overlap = baseA < endB && baseB < endA
      assert(!overlap, s"$nameA and $nameB overlap!")
    }
  }

  it should "have DRAM at standard RISC-V base address" in {
    MemoryMap.DRAM_BASE shouldBe BigInt("80000000", 16)
  }

  it should "have UART at standard address" in {
    MemoryMap.UART_BASE shouldBe BigInt("10000000", 16)
  }

  it should "have CLINT at standard address" in {
    MemoryMap.CLINT_BASE shouldBe BigInt("02000000", 16)
  }

  it should "have all sizes greater than zero" in {
    MemoryMap.BOOTROM_SIZE should be > BigInt(0)
    MemoryMap.CLINT_SIZE   should be > BigInt(0)
    MemoryMap.PLIC_SIZE    should be > BigInt(0)
    MemoryMap.UART_SIZE    should be > BigInt(0)
    MemoryMap.SRAM_SIZE    should be > BigInt(0)
    MemoryMap.DRAM_SIZE    should be > BigInt(0)
  }
}