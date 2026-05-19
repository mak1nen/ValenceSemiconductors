package valence.core

import chisel3._
import chisel3.util._

// =============================================================================
// RegFile — 32 x xlen register file with write-to-read forwarding
//
// Standard RISC-V register file:
//   32 registers (x0–x31), each xlen bits wide
//   x0 is hardwired to zero — writes to x0 are ignored
//   Two read ports (rs1, rs2), one write port (rd)
//
// Write-to-read forwarding:
//   If the write address matches a read address in the same cycle,
//   the read returns the new write data immediately rather than the
//   stale registered value. This covers the WB→ID hazard where an
//   instruction writes back on the same cycle its value is needed by
//   a new instruction entering the decode stage.
//
//   Without this: JAL writes ra in WB at cycle N, but sd ra reads
//   the stale ra=0 from the register array at cycle N.
//   With this:    sd ra gets the forwarded ra value in the same cycle.
// =============================================================================
class RegFile(xlen: Int) extends Module {
  val io = IO(new Bundle {
    // write port
    val wen   = Input(Bool())
    val waddr = Input(UInt(5.W))
    val wdata = Input(UInt(xlen.W))
    // two read ports (rs1 + rs2)
    val raddr1 = Input(UInt(5.W))
    val raddr2 = Input(UInt(5.W))
    val rdata1 = Output(UInt(xlen.W))
    val rdata2 = Output(UInt(xlen.W))
  })

  // 32 registers, each xlen bits wide
  // r0 is hardwired to zero — never written
  val regs = RegInit(VecInit(Seq.fill(32)(0.U(xlen.W))))

  // write — r0 is always zero, ignore writes to it
  when(io.wen && io.waddr =/= 0.U) {
    regs(io.waddr) := io.wdata
  }

  // read with write-to-read forwarding
  // if WB is writing to the same register we're reading, return new data
  val fwd1 = io.wen && io.waddr =/= 0.U && io.waddr === io.raddr1
  val fwd2 = io.wen && io.waddr =/= 0.U && io.waddr === io.raddr2

  io.rdata1 := Mux(io.raddr1 === 0.U, 0.U,
               Mux(fwd1, io.wdata, regs(io.raddr1)))

  io.rdata2 := Mux(io.raddr2 === 0.U, 0.U,
               Mux(fwd2, io.wdata, regs(io.raddr2)))
}