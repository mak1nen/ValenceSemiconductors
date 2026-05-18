package valence.soc

import chisel3._
import chisel3.util._

// On-chip SRAM — 64KB default
// Used for stack + small data during boot

class SRAM(sizeBytes: Int = 65536) extends Module {
  val depth = sizeBytes / 8  // 64-bit words

  val io = IO(new Bundle {
    val addr  = Input(UInt(64.W))
    val wen   = Input(Bool())
    val wdata = Input(UInt(64.W))
    val wstrb = Input(UInt(8.W))
    val valid = Input(Bool())
    val rdata = Output(UInt(64.W))
  })

  val mem = SyncReadMem(depth, UInt(64.W))

  val offset = (io.addr - MemoryMap.SRAM_BASE.U) >> 3

  io.rdata := 0.U

  when(io.valid) {
    when(io.wen) {
      mem.write(offset, io.wdata)
    }.otherwise {
      io.rdata := mem.read(offset)
    }
  }
}