package valence.caches

import chisel3._
import chisel3.util._

class DCacheReq extends Bundle {
  val valid = Input(Bool())
  val addr  = Input(UInt(64.W))
  val wen   = Input(Bool())
  val wdata = Input(UInt(64.W))
}

class DCacheResp extends Bundle {
  val valid = Output(Bool())
  val stall = Output(Bool())
  val rdata = Output(UInt(64.W))
}

class DCacheMemResp extends Bundle {
  val valid = Input(Bool())
  val data  = Input(UInt(64.W))
}

class DCache(nSets: Int, nWays: Int, blockBytes: Int) extends Module {
  val offsetBits = log2Ceil(blockBytes)
  val indexBits  = log2Ceil(nSets)
  val tagBits    = 64 - indexBits - offsetBits

  val io = IO(new Bundle {
    val req  = new DCacheReq
    val resp = new DCacheResp
    val mem  = new DCacheMemResp
  })

  // cache arrays
  val valid = RegInit(VecInit(Seq.fill(nSets)(false.B)))
  val dirty = RegInit(VecInit(Seq.fill(nSets)(false.B)))
  val tags  = RegInit(VecInit(Seq.fill(nSets)(0.U(tagBits.W))))
  val data  = RegInit(VecInit(Seq.fill(nSets)(0.U(64.W))))

  // address decode
  val index = io.req.addr(indexBits + offsetBits - 1, offsetBits)
  val tag   = io.req.addr(63, indexBits + offsetBits)

  // hit detection
  val hit = io.req.valid && valid(index) && tags(index) === tag

  // fill from memory on miss response
  when(io.mem.valid) {
    valid(index) := true.B
    dirty(index) := false.B
    tags(index)  := tag
    data(index)  := io.mem.data
  }

  // write hit — update data in place, mark dirty
  when(hit && io.req.wen) {
    data(index)  := io.req.wdata
    dirty(index) := true.B
  }

  // outputs
  io.resp.valid := hit || (io.mem.valid && io.req.valid)
  io.resp.stall := io.req.valid && !hit && !io.mem.valid
  io.resp.rdata := Mux(io.mem.valid, io.mem.data,
                   Mux(hit && !io.req.wen, data(index), 0.U))
}