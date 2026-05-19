package valence.caches

import chisel3._
import chisel3.util._

// ICache — direct-mapped instruction cache
//
// On hit:  returns instruction in same cycle, no stall
// On miss: stalls pipeline, requests from memory, fills on response
//
// Address breakdown (byte address):
//   [tag | index | offset]
//   tag    = addr[xlen-1 : indexBits+offsetBits]
//   index  = addr[indexBits+offsetBits-1 : offsetBits]
//   offset = addr[offsetBits-1 : 0]

class ICacheReq extends Bundle {
  val valid = Input(Bool())
  val addr  = Input(UInt(64.W))
}
class ICacheResp extends Bundle {
  val valid = Output(Bool())
  val stall = Output(Bool())
  val data  = Output(UInt(32.W))
}
class ICacheMemResp extends Bundle {
  val valid = Input(Bool())
  val data  = Input(UInt(32.W))
}

class ICache(nSets: Int, nWays: Int, blockBytes: Int) extends Module {
  val offsetBits = log2Ceil(blockBytes)
  val indexBits  = log2Ceil(nSets)
  val tagBits    = 64 - indexBits - offsetBits

  val io = IO(new Bundle {
    val req  = new ICacheReq
    val resp = new ICacheResp
    val mem  = new ICacheMemResp
  })

  val valid = RegInit(VecInit(Seq.fill(nSets)(false.B)))
  val tags  = RegInit(VecInit(Seq.fill(nSets)(0.U(tagBits.W))))
  val data  = RegInit(VecInit(Seq.fill(nSets)(0.U(32.W))))

  val index  = io.req.addr(indexBits + offsetBits - 1, offsetBits)
  val tag    = io.req.addr(63, indexBits + offsetBits)

  val hit = io.req.valid && valid(index) && tags(index) === tag

  when(io.mem.valid) {
    valid(index) := true.B
    tags(index)  := tag
    data(index)  := io.mem.data
  }

  io.resp.valid := hit || (io.mem.valid && io.req.valid)
  io.resp.stall := io.req.valid && !hit && !io.mem.valid
  io.resp.data  := Mux(io.mem.valid, io.mem.data, data(index))
}
