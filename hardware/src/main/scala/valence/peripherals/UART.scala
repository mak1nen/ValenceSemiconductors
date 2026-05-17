package valence.peripherals

import chisel3._
import chisel3.util._

// UART transmitter — 8N1 format
// 8 data bits, no parity, 1 stop bit
//
// Frame: [start=0][d0][d1][d2][d3][d4][d5][d6][d7][stop=1]
//
// tx line idles high
// start bit = low
// stop bit  = high
// LSB transmitted first

class UART(clockFreqHz: Int, baudRate: Int) extends Module {
  val cyclesPerBit = clockFreqHz / baudRate

  val io = IO(new Bundle {
    // transmit interface
    val tx_data  = Input(UInt(8.W))
    val tx_valid = Input(Bool())
    val tx_ready = Output(Bool())
    val tx       = Output(Bool())

    // receive interface (stub — RX not needed for Linux boot)
    val rx       = Input(Bool())
    val rx_data  = Output(UInt(8.W))
    val rx_valid = Output(Bool())
  })

  // transmit state machine
  val idle :: start :: sending :: stop :: Nil = Enum(4)
  val state = RegInit(idle)

  val baud_cnt  = RegInit(0.U(log2Ceil(cyclesPerBit + 1).W))
  val bit_cnt   = RegInit(0.U(4.W))
  val shift_reg = RegInit(0.U(8.W))
  val tx_reg    = RegInit(true.B)  // idle high

  switch(state) {
    is(idle) {
      tx_reg := true.B
      when(io.tx_valid) {
        shift_reg := io.tx_data
        baud_cnt  := 0.U
        state     := start
      }
    }

    is(start) {
      tx_reg := false.B  // start bit
      when(baud_cnt === (cyclesPerBit - 1).U) {
        baud_cnt := 0.U
        bit_cnt  := 0.U
        state    := sending
      }.otherwise {
        baud_cnt := baud_cnt + 1.U
      }
    }

    is(sending) {
      tx_reg := shift_reg(0)  // LSB first
      when(baud_cnt === (cyclesPerBit - 1).U) {
        baud_cnt  := 0.U
        shift_reg := shift_reg >> 1
        when(bit_cnt === 7.U) {
          state := stop
        }.otherwise {
          bit_cnt := bit_cnt + 1.U
        }
      }.otherwise {
        baud_cnt := baud_cnt + 1.U
      }
    }

    is(stop) {
      tx_reg := true.B  // stop bit
      when(baud_cnt === (cyclesPerBit - 1).U) {
        baud_cnt := 0.U
        state    := idle
      }.otherwise {
        baud_cnt := baud_cnt + 1.U
      }
    }
  }

  io.tx       := tx_reg
  io.tx_ready := state === idle

  // RX stub
  io.rx_data  := 0.U
  io.rx_valid := false.B
}