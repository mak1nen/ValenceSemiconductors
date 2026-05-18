package valence.bus

import chisel3._
import chisel3.util._

// AXI4 channel bundles
// 5 channels: AW, W, B, AR, R

class AXI4WriteAddr extends Bundle {
  val valid  = Output(Bool())
  val ready  = Input(Bool())
  val addr   = Output(UInt(64.W))
  val len    = Output(UInt(8.W))
  val size   = Output(UInt(3.W))
  val burst  = Output(UInt(2.W))
  val id     = Output(UInt(4.W))
}

class AXI4WriteData extends Bundle {
  val valid  = Output(Bool())
  val ready  = Input(Bool())
  val data   = Output(UInt(64.W))
  val strb   = Output(UInt(8.W))
  val last   = Output(Bool())
}

class AXI4WriteResp extends Bundle {
  val valid  = Input(Bool())
  val ready  = Output(Bool())
  val resp   = Input(UInt(2.W))
  val id     = Input(UInt(4.W))
}

class AXI4ReadAddr extends Bundle {
  val valid  = Output(Bool())
  val ready  = Input(Bool())
  val addr   = Output(UInt(64.W))
  val len    = Output(UInt(8.W))
  val size   = Output(UInt(3.W))
  val burst  = Output(UInt(2.W))
  val id     = Output(UInt(4.W))
}

class AXI4ReadData extends Bundle {
  val valid  = Input(Bool())
  val ready  = Output(Bool())
  val data   = Input(UInt(64.W))
  val resp   = Input(UInt(2.W))
  val last   = Input(Bool())
  val id     = Input(UInt(4.W))
}

class AXI4Bundle extends Bundle {
  val aw = new AXI4WriteAddr
  val w  = new AXI4WriteData
  val b  = new AXI4WriteResp
  val ar = new AXI4ReadAddr
  val r  = new AXI4ReadData
}

object AXI4 {
  val BURST_FIXED = 0.U(2.W)
  val BURST_INCR  = 1.U(2.W)
  val BURST_WRAP  = 2.U(2.W)
  val RESP_OKAY   = 0.U(2.W)
  val RESP_EXOKAY = 1.U(2.W)
  val RESP_SLVERR = 2.U(2.W)
  val RESP_DECERR = 3.U(2.W)
}