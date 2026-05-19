package valence.soc
import chisel3._
import chisel3.util._

// =============================================================================
// BootROM — first instructions the CPU executes after reset
// =============================================================================
//
// The BootROM is a small read-only memory baked directly into the RTL.
// It is NOT loadable — its contents are hardcoded constants in hardware.
//
// Purpose:
//   Act as a trampoline. The CPU always resets to BOOTROM_BASE (0x00001000)
//   because writable memory (SRAM/DRAM) may be empty or uninitialized at
//   power-on. The BootROM does the minimum required setup and jumps to the
//   real program in writable memory.
//
// This is the same pattern used by every real CPU:
//   x86   → resets at 0xFFFFFFF0 (BIOS ROM)  → jumps to bootloader
//   ARM   → resets at 0x00000000 (mask ROM)   → jumps to flash
//   RISC-V→ resets at BootROM   (this file)   → jumps to OpenSBI/program
//
// What it does:
//   1. Sets a0 = 0          (hart ID, required by RISC-V calling convention)
//   2. Sets a1 = 0x87000000 (device tree blob pointer, used by Linux/OpenSBI)
//   3. Jumps to BOOT_TARGET (SRAM for sim, DRAM for Linux)
//
// Targets:
//   Sim target:   jumps to SRAM at 0x20000000 (hello.elf, bare metal tests)
//   Linux target: jumps to DRAM at 0x80000000 (OpenSBI → U-Boot → Linux)
//
// To switch targets, change BOOT_TARGET below and regenerate:
//   sbt "hardware/runMain valence.soc.SoCElaborate"
//
// Assembly equivalent (sim):
//   li  a0, 0            # hart ID = 0
//   li  a1, 0x87000000   # device tree pointer (unused in sim)
//   li  t0, 0x20000000   # jump target — SRAM base
//   jr  t0
//
// Assembly equivalent (linux):
//   li  a0, 0            # hart ID = 0
//   li  a1, 0x87000000   # device tree pointer
//   li  t0, 0x80000000   # jump target — OpenSBI in DRAM
//   jr  t0
// =============================================================================

class BootROM extends Module {
  val io = IO(new Bundle {
    val addr  = Input(UInt(64.W))
    val valid = Input(Bool())
    val data  = Output(UInt(32.W))
  })

  // Change to MemoryMap.DRAM_BASE for Linux boot
  val BOOT_TARGET = MemoryMap.SRAM_BASE

  // lui t0, BOOT_TARGET[31:12]
  val lui_t0 = (((BOOT_TARGET >> 12) & 0xFFFFF) << 12 | 0x2B7).toLong
  // jr t0 (jalr x0, t0, 0)
  val jr_t0  = 0x00028067L

  val rom = VecInit(Seq(
    // li a0, 0  (hart id = 0)
    0x00000513L.U(32.W),
    // li a1, 0x87000000  (device tree blob address)
    0x87000537L.U(32.W),
    0x00058593L.U(32.W),
    // li t0, BOOT_TARGET
    lui_t0.U(32.W),
    // nop — let lui writeback complete before jr reads t0
    0x00000013L.U(32.W),
    // nop — extra bubble for safety
    0x00000013L.U(32.W),
    // jr t0
    jr_t0.U(32.W),
    // infinite loop (safety net)
    0x0000006FL.U(32.W),
  ))

  val inRange = io.addr >= MemoryMap.BOOTROM_BASE.U &&
                io.addr <  (MemoryMap.BOOTROM_BASE + MemoryMap.BOOTROM_SIZE).U
  val offset  = (io.addr - MemoryMap.BOOTROM_BASE.U)(log2Ceil(rom.length) + 1, 2)
  io.data := Mux(
    io.valid && inRange && offset < rom.length.U,
    rom(offset),
    0.U
  )
}