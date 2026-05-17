package valence.peripherals

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

class UARTSpec extends AnyFlatSpec with Matchers {

  behavior of "UART"

  def test(fn: UART => Unit): Unit =
    simulate(new UART(clockFreqHz = 50000000, baudRate = 115200)) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.tx_data.poke(0.U)
      dut.io.tx_valid.poke(false)
      fn(dut)
    }

  it should "be ready to transmit after reset" in {
    test { dut =>
      dut.io.tx_ready.expect(true)
    }
  }

  it should "accept a byte when valid and ready" in {
    test { dut =>
      dut.io.tx_data.poke('A'.U)
      dut.io.tx_valid.poke(true)
      dut.clock.step()
      // busy transmitting — not ready
      dut.io.tx_ready.expect(false)
    }
  }

  it should "transmit start bit low then data bits" in {
    test { dut =>
      // load byte
      dut.io.tx_data.poke(0x55.U)  // 01010101
      dut.io.tx_valid.poke(true)
      dut.clock.step()
      dut.io.tx_valid.poke(false)
      dut.clock.step()  // one more cycle for start bit to appear

      // start bit should be low
      dut.io.tx.expect(false)
    }
  }

  it should "return to idle (tx high) after full frame" in {
    test { dut =>
      val cyclesPerBit = 50000000 / 115200  // ~434 cycles

      dut.io.tx_data.poke(0x41.U)  // 'A'
      dut.io.tx_valid.poke(true)
      dut.clock.step()
      dut.io.tx_valid.poke(false)

      // step through full frame: 1 start + 8 data + 1 stop = 10 bits
      dut.clock.step(cyclesPerBit * 10 + 10)

      // should be idle and ready again
      dut.io.tx.expect(true)
      dut.io.tx_ready.expect(true)
    }
  }
}