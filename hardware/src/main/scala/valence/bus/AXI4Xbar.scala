package valence.bus

import chisel3._
import chisel3.util._

// AXI4 crossbar — routes one master to N slaves based on address
// Master = CPU core
// Slaves = DRAM, UART, CLINT, PLIC, SRAM, BootROM

class AXI4Xbar(nSlaves: Int, baseAddrs: Seq[BigInt], sizes: Seq[BigInt])
    extends Module {
  require(nSlaves == baseAddrs.length && nSlaves == sizes.length)

  val io = IO(new Bundle {
    // single master port (CPU)
    val master = Flipped(new AXI4Bundle)

    // slave ports
    val slaves = Vec(nSlaves, new AXI4Bundle)
  })

  // address decode — which slave does this address belong to?
  def decode(addr: UInt): UInt = {
    val sel = Wire(UInt(log2Ceil(nSlaves + 1).W))
    sel := nSlaves.U  // default: no slave (error)
    for (i <- 0 until nSlaves) {
      when(addr >= baseAddrs(i).U &&
           addr <  (baseAddrs(i) + sizes(i)).U) {
        sel := i.U
      }
    }
    sel
  }

  // read address routing
  val ar_sel = decode(io.master.ar.addr)

  // write address routing
  val aw_sel = decode(io.master.aw.addr)

  // default — tie off all slave ports
  for (i <- 0 until nSlaves) {
    io.slaves(i).aw.valid := false.B
    io.slaves(i).aw.addr  := 0.U
    io.slaves(i).aw.len   := 0.U
    io.slaves(i).aw.size  := 0.U
    io.slaves(i).aw.burst := 0.U
    io.slaves(i).aw.id    := 0.U

    io.slaves(i).w.valid  := false.B
    io.slaves(i).w.data   := 0.U
    io.slaves(i).w.strb   := 0.U
    io.slaves(i).w.last   := false.B

    io.slaves(i).b.ready  := false.B

    io.slaves(i).ar.valid := false.B
    io.slaves(i).ar.addr  := 0.U
    io.slaves(i).ar.len   := 0.U
    io.slaves(i).ar.size  := 0.U
    io.slaves(i).ar.burst := 0.U
    io.slaves(i).ar.id    := 0.U

    io.slaves(i).r.ready  := false.B
  }

  // route read address to selected slave
  io.master.ar.ready := false.B
  for (i <- 0 until nSlaves) {
    when(ar_sel === i.U) {
      io.slaves(i).ar.valid := io.master.ar.valid
      io.slaves(i).ar.addr  := io.master.ar.addr
      io.slaves(i).ar.len   := io.master.ar.len
      io.slaves(i).ar.size  := io.master.ar.size
      io.slaves(i).ar.burst := io.master.ar.burst
      io.slaves(i).ar.id    := io.master.ar.id
      io.master.ar.ready    := io.slaves(i).ar.ready
    }
  }

  // route write address to selected slave
  io.master.aw.ready := false.B
  for (i <- 0 until nSlaves) {
    when(aw_sel === i.U) {
      io.slaves(i).aw.valid := io.master.aw.valid
      io.slaves(i).aw.addr  := io.master.aw.addr
      io.slaves(i).aw.len   := io.master.aw.len
      io.slaves(i).aw.size  := io.master.aw.size
      io.slaves(i).aw.burst := io.master.aw.burst
      io.slaves(i).aw.id    := io.master.aw.id
      io.master.aw.ready    := io.slaves(i).aw.ready
    }
  }

  // route write data to selected slave
  io.master.w.ready := false.B
  for (i <- 0 until nSlaves) {
    when(aw_sel === i.U) {
      io.slaves(i).w.valid := io.master.w.valid
      io.slaves(i).w.data  := io.master.w.data
      io.slaves(i).w.strb  := io.master.w.strb
      io.slaves(i).w.last  := io.master.w.last
      io.master.w.ready    := io.slaves(i).w.ready
    }
  }

  // read data back to master from selected slave
  io.master.r.valid := false.B
  io.master.r.data  := 0.U
  io.master.r.resp  := 0.U
  io.master.r.last  := false.B
  io.master.r.id    := 0.U
  for (i <- 0 until nSlaves) {
    when(io.slaves(i).r.valid) {
      io.master.r.valid := io.slaves(i).r.valid
      io.master.r.data  := io.slaves(i).r.data
      io.master.r.resp  := io.slaves(i).r.resp
      io.master.r.last  := io.slaves(i).r.last
      io.master.r.id    := io.slaves(i).r.id
      io.slaves(i).r.ready := io.master.r.ready
    }
  }

  // write response back to master
  io.master.b.valid := false.B
  io.master.b.resp  := 0.U
  io.master.b.id    := 0.U
  for (i <- 0 until nSlaves) {
    when(io.slaves(i).b.valid) {
      io.master.b.valid    := io.slaves(i).b.valid
      io.master.b.resp     := io.slaves(i).b.resp
      io.master.b.id       := io.slaves(i).b.id
      io.slaves(i).b.ready := io.master.b.ready
    }
  }
}