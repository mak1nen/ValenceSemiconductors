package valence.core

import chisel3._
import chisel3.util._
import valence.soc.MemoryMap

class Frontend extends Module {
  val io = IO(new Bundle {
    // to ICache
    val pc       = Output(UInt(64.W))
    val req      = Output(Bool())

    // from ICache
    val instr    = Input(UInt(32.W))
    val icache_stall = Input(Bool())

    // control
    val stall    = Input(Bool())
    val flush    = Input(Bool())
    val redirect = Input(Bool())
    val target   = Input(UInt(64.W))

    // to decode
    val out_pc   = Output(UInt(64.W))
    val out_instr= Output(UInt(32.W))
    val out_valid= Output(Bool())
  })

  val pc = RegInit(MemoryMap.RESET_VECTOR.U(64.W))

  // NOP instruction
  val NOP = "h00000013".U(32.W)

  when(io.flush || io.redirect) {
    pc := io.target
  }.elsewhen(!io.stall && !io.icache_stall) {
    pc := pc + 4.U
  }

  io.pc       := pc
  io.req      := true.B
  io.out_pc   := pc
  io.out_instr:= Mux(io.flush || io.icache_stall, NOP, io.instr)
  io.out_valid:= !io.flush && !io.icache_stall
}