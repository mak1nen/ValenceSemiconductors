package valence.soc

import chisel3._
import chisel3.util._

// BootROM — first instructions the CPU executes after reset
// Contains a small program that jumps to DRAM (OpenSBI/Linux)
//
// Assembly equivalent:
//   li  a0, 0          # hart ID = 0
//   li  a1, 0x87000000 # device tree pointer
//   li  t0, 0x80000000 # jump to OpenSBI in DRAM
//   jr  t0

class BootROM extends Module {
  val io = IO(new Bundle {
    val addr  = Input(UInt(64.W))
    val valid = Input(Bool())
    val data  = Output(UInt(32.W))
  })

  // minimal boot program — jumps to OpenSBI at 0x80000000
  // encoded as 32-bit RISC-V instructions (little endian)
  val rom = VecInit(Seq(
    // li a0, 0  (hart id)
    0x00000513L.U(32.W),
    // li a1, 0x87000000  (device tree blob address)
    0x87000537L.U(32.W),
    0x00058593L.U(32.W),
    // li t0, 0x80000000  (OpenSBI base)
    0x800002B7L.U(32.W),
    // jr t0
    0x00028067L.U(32.W),
    // infinite loop (safety net)
    0x0000006FL.U(32.W),
  ))

  val offset = (io.addr - MemoryMap.BOOTROM_BASE.U)(log2Ceil(rom.length) + 1, 2)
  io.data := Mux(
    io.valid && offset < rom.length.U,
    rom(offset),
    0.U
  )
}