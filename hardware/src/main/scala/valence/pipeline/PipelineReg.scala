package valence.pipeline

import chisel3._
import chisel3.util._

// A single pipeline stage register
// Sits between two pipeline stages: IF/ID, ID/EX, EX/MEM, MEM/WB
//
// stall → hold current value (upstream stalled, don't advance)
// flush → clear to zero    (branch misprediction, exception)

class PipelineReg[T <: Data](gen: T) extends Module {
  val io = IO(new Bundle {
    val in    = Input(gen)
    val out   = Output(gen)
    val stall = Input(Bool())
    val flush = Input(Bool())
  })

  val reg = RegInit(0.U.asTypeOf(gen))

  when(io.flush) {
    reg := 0.U.asTypeOf(gen)
  }.elsewhen(!io.stall) {
    reg := io.in
  }

  io.out := reg
}