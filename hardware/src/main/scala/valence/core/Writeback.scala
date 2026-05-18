package valence.core

import chisel3._
import chisel3.util._

class Writeback extends Module {
  val io = IO(new Bundle {
    val in     = Input(new MemoryOut)

    // to RegFile
    val wen    = Output(Bool())
    val waddr  = Output(UInt(5.W))
    val wdata  = Output(UInt(64.W))
  })

  io.wen   := io.in.valid && io.in.rd =/= 0.U
  io.waddr := io.in.rd
  io.wdata := io.in.result
}