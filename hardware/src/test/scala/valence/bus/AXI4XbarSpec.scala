package valence.bus

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.soc.MemoryMap

class AXI4XbarSpec extends AnyFlatSpec with Matchers {

  behavior of "AXI4Xbar"

  val bases = Seq(
    MemoryMap.BOOTROM_BASE,
    MemoryMap.UART_BASE,
    MemoryMap.DRAM_BASE,
  )
  val sizes = Seq(
    MemoryMap.BOOTROM_SIZE,
    MemoryMap.UART_SIZE,
    MemoryMap.DRAM_SIZE,
  )

  def test(fn: AXI4Xbar => Unit): Unit =
    simulate(new AXI4Xbar(3, bases, sizes)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.master.ar.valid.poke(false)
      dut.io.master.aw.valid.poke(false)
      dut.io.master.w.valid.poke(false)
      dut.io.master.b.ready.poke(false)
      dut.io.master.r.ready.poke(false)
      for (i <- 0 until 3) {
        dut.io.slaves(i).ar.ready.poke(false)
        dut.io.slaves(i).aw.ready.poke(false)
        dut.io.slaves(i).w.ready.poke(false)
        dut.io.slaves(i).r.valid.poke(false)
        dut.io.slaves(i).r.data.poke(0.U)
        dut.io.slaves(i).r.resp.poke(0.U)
        dut.io.slaves(i).r.last.poke(false)
        dut.io.slaves(i).r.id.poke(0.U)
        dut.io.slaves(i).b.valid.poke(false)
        dut.io.slaves(i).b.resp.poke(0.U)
        dut.io.slaves(i).b.id.poke(0.U)
      }
      fn(dut)
    }

  it should "route read to BOOTROM slave" in {
    test { dut =>
      dut.io.master.ar.valid.poke(true)
      dut.io.master.ar.addr.poke(MemoryMap.BOOTROM_BASE.U)
      dut.clock.step()
      dut.io.slaves(0).ar.valid.expect(true)
      dut.io.slaves(1).ar.valid.expect(false)
      dut.io.slaves(2).ar.valid.expect(false)
    }
  }

  it should "route read to UART slave" in {
    test { dut =>
      dut.io.master.ar.valid.poke(true)
      dut.io.master.ar.addr.poke(MemoryMap.UART_BASE.U)
      dut.clock.step()
      dut.io.slaves(1).ar.valid.expect(true)
      dut.io.slaves(0).ar.valid.expect(false)
      dut.io.slaves(2).ar.valid.expect(false)
    }
  }

  it should "route read to DRAM slave" in {
    test { dut =>
      dut.io.master.ar.valid.poke(true)
      dut.io.master.ar.addr.poke(MemoryMap.DRAM_BASE.U)
      dut.clock.step()
      dut.io.slaves(2).ar.valid.expect(true)
      dut.io.slaves(0).ar.valid.expect(false)
      dut.io.slaves(1).ar.valid.expect(false)
    }
  }

  it should "route write to DRAM slave" in {
    test { dut =>
      dut.io.master.aw.valid.poke(true)
      dut.io.master.aw.addr.poke(MemoryMap.DRAM_BASE.U)
      dut.clock.step()
      dut.io.slaves(2).aw.valid.expect(true)
      dut.io.slaves(0).aw.valid.expect(false)
    }
  }

  it should "return read data from slave to master" in {
    test { dut =>
      dut.io.slaves(2).r.valid.poke(true)
      dut.io.slaves(2).r.data.poke(0xCAFEL.U)
      dut.clock.step()
      dut.io.master.r.valid.expect(true)
      dut.io.master.r.data.expect(0xCAFEL.U)
    }
  }
}