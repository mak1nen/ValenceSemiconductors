package valence.soc

// =============================================================================
// Valence RISC-V — Memory Map
// All addresses must match:
//   sim/sw/linker.ld
//   sim/verilator/tb_soc.cpp
//   device tree (valence.dts)
// =============================================================================

object MemoryMap {
  // BootROM — first instructions after reset
  val BOOTROM_BASE = BigInt("00001000", 16)
  val BOOTROM_SIZE = BigInt("00001000", 16)  // 4KB

  // CLINT — Core Local Interruptor (timer + software interrupts)
  val CLINT_BASE   = BigInt("02000000", 16)
  val CLINT_SIZE   = BigInt("00010000", 16)  // 64KB

  // PLIC — Platform Level Interrupt Controller
  val PLIC_BASE    = BigInt("0C000000", 16)
  val PLIC_SIZE    = BigInt("04000000", 16)  // 64MB

  // UART
  val UART_BASE    = BigInt("10000000", 16)
  val UART_SIZE    = BigInt("00001000", 16)  // 4KB

  // SRAM — on chip
  val SRAM_BASE    = BigInt("20000000", 16)
  val SRAM_SIZE    = BigInt("00010000", 16)  // 64KB

  // DRAM — main memory (loaded by Verilator sim)
  val DRAM_BASE    = BigInt("80000000", 16)
  val DRAM_SIZE    = BigInt("10000000", 16)  // 256MB

  // Reset vector — CPU starts here
  val RESET_VECTOR = BigInt("00001000", 16)  // BootROM

  // CLINT register offsets
  val CLINT_MSIP   = BigInt("0000", 16)  // software interrupt
  val CLINT_MTIME  = BigInt("BFF8", 16)  // timer value
  val CLINT_MTIMECMP = BigInt("4000", 16) // timer compare
}