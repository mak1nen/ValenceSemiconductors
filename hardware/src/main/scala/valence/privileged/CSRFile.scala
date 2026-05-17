package valence.privileged

import chisel3._
import chisel3.util._

// CSR addresses — machine mode
object CSRFile {
  val MSTATUS  = 0x300
  val MISA     = 0x301
  val MTVEC    = 0x305
  val MSCRATCH = 0x340
  val MEPC     = 0x341
  val MCAUSE   = 0x342
  val MTVAL    = 0x343
  val MHARTID  = 0xF14
}

class CSRFile(xlen: Int) extends Module {
  val io = IO(new Bundle {
    // read/write port
    val addr   = Input(UInt(12.W))
    val wen    = Input(Bool())
    val wdata  = Input(UInt(xlen.W))
    val rdata  = Output(UInt(xlen.W))

    // exception / trap interface
    val exception = Input(Bool())
    val epc       = Input(UInt(xlen.W))
    val cause     = Input(UInt(xlen.W))

    // trap vector output — where to jump on exception
    val tvec   = Output(UInt(xlen.W))
  })

  // machine mode CSRs
  val mstatus  = RegInit(0.U(xlen.W))
  val misa     = RegInit(0.U(xlen.W))
  val mtvec    = RegInit(0.U(xlen.W))
  val mscratch = RegInit(0.U(xlen.W))
  val mepc     = RegInit(0.U(xlen.W))
  val mcause   = RegInit(0.U(xlen.W))
  val mtval    = RegInit(0.U(xlen.W))

  // exception handling — save pc and cause, redirect to tvec
  when(io.exception) {
    mepc   := io.epc
    mcause := io.cause
  }

  // write
  when(io.wen && !io.exception) {
    switch(io.addr) {
      is(CSRFile.MSTATUS.U)  { mstatus  := io.wdata }
      is(CSRFile.MTVEC.U)    { mtvec    := io.wdata }
      is(CSRFile.MSCRATCH.U) { mscratch := io.wdata }
      is(CSRFile.MEPC.U)     { mepc     := io.wdata }
      is(CSRFile.MCAUSE.U)   { mcause   := io.wdata }
      is(CSRFile.MTVAL.U)    { mtval    := io.wdata }
    }
  }

  // read
  io.rdata := MuxLookup(io.addr, 0.U)(Seq(
    CSRFile.MSTATUS.U  -> mstatus,
    CSRFile.MISA.U     -> misa,
    CSRFile.MTVEC.U    -> mtvec,
    CSRFile.MSCRATCH.U -> mscratch,
    CSRFile.MEPC.U     -> mepc,
    CSRFile.MCAUSE.U   -> mcause,
    CSRFile.MTVAL.U    -> mtval,
    CSRFile.MHARTID.U  -> 0.U,
  ))

  io.tvec := mtvec
}