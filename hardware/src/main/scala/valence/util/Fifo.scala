package valence.util

import chisel3._
import chisel3.util._

class Fifo[T <: Data](gen: T, depth: Int) extends Module {
  require(depth > 0, "FIFO depth must be > 0")
  require((depth & (depth - 1)) == 0, "FIFO depth must be power of 2")

  val io = IO(new Bundle {
    val enq = Flipped(Decoupled(gen))
    val deq = Decoupled(gen)
  })

  val mem   = RegInit(VecInit(Seq.fill(depth)(0.U.asTypeOf(gen))))
  val head  = RegInit(0.U(log2Ceil(depth).W))
  val tail  = RegInit(0.U(log2Ceil(depth).W))
  val count = RegInit(0.U((log2Ceil(depth) + 1).W))

  val full  = count === depth.U
  val empty = count === 0.U

  io.enq.ready := !full
  io.deq.valid := !empty
  io.deq.bits  := mem(head)

  when(io.enq.fire) {
    mem(tail) := io.enq.bits
    tail := tail + 1.U
  }

  when(io.deq.fire) {
    head := head + 1.U
  }

  when(io.enq.fire && !io.deq.fire) {
    count := count + 1.U
  }.elsewhen(!io.enq.fire && io.deq.fire) {
    count := count - 1.U
  }
}