package valence.soc

import chisel3._
import chisel3.util._

class BootROM extends Module {
  val io = IO(new Bundle {
    val addr  = Input(UInt(64.W))
    val valid = Input(Bool())
    val data  = Output(UInt(32.W))
  })

  val rom = VecInit(Seq(
    0x00000513L.U(32.W),
    0x08700593L.U(32.W),
    0x01859593L.U(32.W),
    0x00100293L.U(32.W),
    0x01F29293L.U(32.W),
    0x00000013L.U(32.W),
    0x00028067L.U(32.W),
    0x0000006FL.U(32.W),
  ))

  val inRange = (io.addr - MemoryMap.BOOTROM_BASE.U) < MemoryMap.BOOTROM_SIZE.U
  val offset  = (io.addr - MemoryMap.BOOTROM_BASE.U)(log2Ceil(rom.length) + 1, 2)

  io.data := Mux(
    io.valid && inRange && offset < rom.length.U,
    rom(offset),
    0.U
  )
}
