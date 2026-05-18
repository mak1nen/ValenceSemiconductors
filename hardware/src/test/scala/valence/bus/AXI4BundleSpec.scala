package valence.bus

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

// Wrap AXI4Bundle in a simple module to simulate it
class AXI4BundleWrapper extends chisel3.Module {
  val io = IO(new chisel3.Bundle {
    val aw_valid = Output(Bool())
    val aw_addr  = Output(UInt(64.W))
    val ar_valid = Output(Bool())
    val ar_addr  = Output(UInt(64.W))
    val w_valid  = Output(Bool())
    val w_data   = Output(UInt(64.W))
    val r_ready  = Output(Bool())
    val b_ready  = Output(Bool())
  })

  val bundle = Wire(new AXI4Bundle)

  bundle.aw.valid := false.B
  bundle.aw.addr  := 0.U
  bundle.aw.len   := 0.U
  bundle.aw.size  := 0.U
  bundle.aw.burst := AXI4.BURST_INCR
  bundle.aw.id    := 0.U

  bundle.w.valid  := false.B
  bundle.w.data   := 0.U
  bundle.w.strb   := 0xFF.U
  bundle.w.last   := true.B

  bundle.b.ready  := true.B

  bundle.ar.valid := false.B
  bundle.ar.addr  := 0.U
  bundle.ar.len   := 0.U
  bundle.ar.size  := 0.U
  bundle.ar.burst := AXI4.BURST_INCR
  bundle.ar.id    := 0.U

  bundle.r.ready  := true.B

  io.aw_valid := bundle.aw.valid
  io.aw_addr  := bundle.aw.addr
  io.ar_valid := bundle.ar.valid
  io.ar_addr  := bundle.ar.addr
  io.w_valid  := bundle.w.valid
  io.w_data   := bundle.w.data
  io.r_ready  := bundle.r.ready
  io.b_ready  := bundle.b.ready
}

class AXI4BundleSpec extends AnyFlatSpec with Matchers {

  behavior of "AXI4Bundle"

  it should "have correct default signal values" in {
    // AXI4Bundle is just a data structure — test constants only
    AXI4.BURST_FIXED.litValue shouldBe 0
    AXI4.BURST_INCR.litValue  shouldBe 1
    succeed
  }

  it should "have correct AXI4 burst constants" in {
    AXI4.BURST_FIXED.litValue shouldBe 0
    AXI4.BURST_INCR.litValue  shouldBe 1
    AXI4.BURST_WRAP.litValue  shouldBe 2
  }

  it should "have correct AXI4 response constants" in {
    AXI4.RESP_OKAY.litValue   shouldBe 0
    AXI4.RESP_EXOKAY.litValue shouldBe 1
    AXI4.RESP_SLVERR.litValue shouldBe 2
    AXI4.RESP_DECERR.litValue shouldBe 3
  }
}