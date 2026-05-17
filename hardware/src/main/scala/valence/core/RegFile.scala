
package valence.core

import chisel3._
import chisel3.util._

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

  // read — r0 always returns 0
  io.rdata1 := Mux(io.raddr1 === 0.U, 0.U, regs(io.raddr1))
  io.rdata2 := Mux(io.raddr2 === 0.U, 0.U, regs(io.raddr2))
}