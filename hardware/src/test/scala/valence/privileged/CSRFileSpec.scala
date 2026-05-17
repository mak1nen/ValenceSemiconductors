package valence.privileged

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class CSRFileSpec extends AnyFlatSpec with Matchers {

  behavior of "CSRFile"

  def test(fn: CSRFile => Unit): Unit =
    simulate(new CSRFile(64)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.wen.poke(false)
      dut.io.addr.poke(0.U)
      dut.io.wdata.poke(0.U)
      dut.io.exception.poke(false)
      dut.io.epc.poke(0.U)
      dut.io.cause.poke(0.U)
      fn(dut)
    }

  it should "write and read mstatus" in {
    test { dut =>
      dut.io.wen.poke(true)
      dut.io.addr.poke(CSRFile.MSTATUS.U)
      dut.io.wdata.poke(0x1800.U)
      dut.clock.step()
      dut.io.wen.poke(false)
      dut.io.addr.poke(CSRFile.MSTATUS.U)
      dut.io.rdata.expect(0x1800.U)
    }
  }

  it should "write and read mtvec" in {
    test { dut =>
      dut.io.wen.poke(true)
      dut.io.addr.poke(CSRFile.MTVEC.U)
      dut.io.wdata.poke(0x80000000L.U)
      dut.clock.step()
      dut.io.wen.poke(false)
      dut.io.addr.poke(CSRFile.MTVEC.U)
      dut.io.rdata.expect(0x80000000L.U)
    }
  }

  it should "write and read mepc" in {
    test { dut =>
      dut.io.wen.poke(true)
      dut.io.addr.poke(CSRFile.MEPC.U)
      dut.io.wdata.poke(0x80001000L.U)
      dut.clock.step()
      dut.io.wen.poke(false)
      dut.io.addr.poke(CSRFile.MEPC.U)
      dut.io.rdata.expect(0x80001000L.U)
    }
  }

  it should "save epc and cause on exception" in {
    test { dut =>
      // set mtvec first
      dut.io.wen.poke(true)
      dut.io.addr.poke(CSRFile.MTVEC.U)
      dut.io.wdata.poke(0x80000000L.U)
      dut.clock.step()
      dut.io.wen.poke(false)

      // trigger exception
      dut.io.exception.poke(true)
      dut.io.epc.poke(0x80001000L.U)
      dut.io.cause.poke(11.U)
      dut.clock.step()
      dut.io.exception.poke(false)

      // mepc should hold the faulting pc
      dut.io.addr.poke(CSRFile.MEPC.U)
      dut.io.rdata.expect(0x80001000L.U)

      // mcause should hold the cause
      dut.io.addr.poke(CSRFile.MCAUSE.U)
      dut.io.rdata.expect(11.U)

      // trap vector output
      dut.io.tvec.expect(0x80000000L.U)
    }
  }

  it should "read mhartid as zero" in {
    test { dut =>
      dut.io.addr.poke(CSRFile.MHARTID.U)
      dut.io.rdata.expect(0.U)
    }
  }

  it should "not write when wen is low" in {
    test { dut =>
      dut.io.wen.poke(true)
      dut.io.addr.poke(CSRFile.MSCRATCH.U)
      dut.io.wdata.poke(42.U)
      dut.clock.step()

      dut.io.wen.poke(false)
      dut.io.wdata.poke(999.U)
      dut.clock.step()

      dut.io.addr.poke(CSRFile.MSCRATCH.U)
      dut.io.rdata.expect(42.U)
    }
  }
}