package valence.peripherals

import chisel3._
import chisel3.util._
import valence.soc.MemoryMap

// CLINT — Core Local Interruptor
//
// Two functions:
//   1. Timer interrupt — mtime >= mtimecmp → interrupt
//      Linux uses this for scheduling (every 10ms)
//
//   2. Software interrupt — msip register
//      Used for inter-processor interrupts (IPI)
//      Core 0 writes msip of Core 1 to wake it up
//
// Memory mapped registers:
//   0x02000000 → msip      (software interrupt pending)
//   0x02004000 → mtimecmp  (timer compare value)
//   0x0200BFF8 → mtime     (current time, increments every cycle)

class CLINT(nHarts: Int = 1) extends Module {
  val io = IO(new Bundle {
    // memory mapped register interface
    val addr   = Input(UInt(64.W))
    val wen    = Input(Bool())
    val wdata  = Input(UInt(64.W))
    val rdata  = Output(UInt(64.W))
    val valid  = Input(Bool())

    // interrupt outputs — one per hart
    val timer_irq = Output(Vec(nHarts, Bool()))
    val soft_irq  = Output(Vec(nHarts, Bool()))
  })

  // mtime — increments every clock cycle
  val mtime    = RegInit(0.U(64.W))
  mtime := mtime + 1.U

  // per-hart registers
  val mtimecmp = RegInit(VecInit(Seq.fill(nHarts)(BigInt("FFFFFFFFFFFFFFFF", 16).U(64.W))))
  val msip     = RegInit(VecInit(Seq.fill(nHarts)(false.B)))

  // write handler
  when(io.valid && io.wen) {
    val offset = io.addr - MemoryMap.CLINT_BASE.U

    // msip registers at 0x0000 + 4*hart
    for (i <- 0 until nHarts) {
      when(offset === (MemoryMap.CLINT_MSIP + i * 4).U) {
        msip(i) := io.wdata(0)
      }
      // mtimecmp at 0x4000 + 8*hart
      when(offset === (MemoryMap.CLINT_MTIMECMP + i * 8).U) {
        mtimecmp(i) := io.wdata
      }
    }
  }

  // read handler
  io.rdata := 0.U
  when(io.valid && !io.wen) {
    val offset = io.addr - MemoryMap.CLINT_BASE.U

    // mtime read
    when(offset === MemoryMap.CLINT_MTIME.U) {
      io.rdata := mtime
    }

    for (i <- 0 until nHarts) {
      when(offset === (MemoryMap.CLINT_MSIP + i * 4).U) {
        io.rdata := msip(i).asUInt
      }
      when(offset === (MemoryMap.CLINT_MTIMECMP + i * 8).U) {
        io.rdata := mtimecmp(i)
      }
    }
  }

  // interrupt generation
  for (i <- 0 until nHarts) {
    io.timer_irq(i) := mtime >= mtimecmp(i)
    io.soft_irq(i)  := msip(i)
  }
}