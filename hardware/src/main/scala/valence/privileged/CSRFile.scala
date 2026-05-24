package valence.privileged

import chisel3._
import chisel3.util._

// CSR addresses — machine mode
object CSRFile {
  val MSTATUS  = 0x300
  val MISA     = 0x301
  val MIE      = 0x304
  val MTVEC    = 0x305
  val MSCRATCH = 0x340
  val MEPC     = 0x341
  val MCAUSE   = 0x342
  val MTVAL    = 0x343
  val MIP      = 0x344
  val MHARTID  = 0xF14

  // mstatus bit positions (RV64)
  val MSTATUS_MIE_BIT  = 3
  val MSTATUS_MPIE_BIT = 7
  // MPP is bits [12:11]; we always run in M-mode so MPP stays 11.
  val MSTATUS_MPP_LSB  = 11

  // mie / mip bit positions
  val MSIE_BIT = 3
  val MTIE_BIT = 7
  val MEIE_BIT = 11

  val MSIP_BIT = 3
  val MTIP_BIT = 7
  val MEIP_BIT = 11
}

class CSRFile(xlen: Int) extends Module {
  val io = IO(new Bundle {
    // ----- Software CSR read/write port (driven by CSR instructions) -----
    val addr   = Input(UInt(12.W))
    val wen    = Input(Bool())
    val wdata  = Input(UInt(xlen.W))
    val rdata  = Output(UInt(xlen.W))

    // ----- Trap entry interface (from TrapUnit) -----
    // When takeTrap asserts, atomically:
    //   mepc   := trapEpc
    //   mcause := trapCause
    //   mtval  := trapTval
    //   mstatus.MPIE := mstatus.MIE
    //   mstatus.MIE  := 0
    val takeTrap  = Input(Bool())
    val trapEpc   = Input(UInt(xlen.W))
    val trapCause = Input(UInt(xlen.W))
    val trapTval  = Input(UInt(xlen.W))

    // ----- MRET interface (from TrapUnit) -----
    // When takeMret asserts, atomically:
    //   mstatus.MIE  := mstatus.MPIE
    //   mstatus.MPIE := 1
    val takeMret = Input(Bool())

    // ----- Hardware interrupt line inputs (from CLINT/PLIC) -----
    // These set the corresponding bits in mip (which is read-only for
    // these bits — software can't clear a real pending line, the source
    // device must).
    val mtipIn = Input(Bool())  // timer interrupt pending (from CLINT)
    val msipIn = Input(Bool())  // software interrupt pending (from CLINT)
    val meipIn = Input(Bool())  // external interrupt pending (from PLIC)

    // ----- CSR value exports (read by TrapUnit and other modules) -----
    val mstatus = Output(UInt(xlen.W))
    val mie     = Output(UInt(xlen.W))
    val mip     = Output(UInt(xlen.W))
    val mtvec   = Output(UInt(xlen.W))
    val mepc    = Output(UInt(xlen.W))
  })

  // --------------------------------------------------------------------------
  // CSR storage
  // --------------------------------------------------------------------------

  val mstatusReg = RegInit(0.U(xlen.W))
  val misa       = RegInit(0.U(xlen.W))  // TODO: populate with supported extensions
  val mieReg     = RegInit(0.U(xlen.W))
  val mtvec      = RegInit(0.U(xlen.W))
  val mscratch   = RegInit(0.U(xlen.W))
  val mepc       = RegInit(0.U(xlen.W))
  val mcause     = RegInit(0.U(xlen.W))
  val mtval      = RegInit(0.U(xlen.W))

  // --------------------------------------------------------------------------
  // mip register
  //
  // Hardware-driven bits (MTIP, MSIP, MEIP) come from the interrupt source
  // devices and are read-only from the software side for our implementation.
  // Software-writable mip bits don't exist in this minimal core.
  // --------------------------------------------------------------------------

  val mip = Wire(UInt(xlen.W))
  mip := 0.U
  mip := Cat(
    0.U((xlen - 12).W),
    io.meipIn,                // bit 11
    0.U(3.W),                 // bits 10-8
    io.mtipIn,                // bit 7
    0.U(3.W),                 // bits 6-4
    io.msipIn,                // bit 3
    0.U(3.W)                  // bits 2-0
  )

  // --------------------------------------------------------------------------
  // mstatus state machine
  //
  // Priority for mstatus update this cycle:
  //   1. takeTrap   -> save MIE to MPIE, clear MIE
  //   2. takeMret   -> restore MIE from MPIE, set MPIE = 1
  //   3. software CSR write to mstatus (only if no trap/mret this cycle)
  // --------------------------------------------------------------------------

  val mstatusMie  = mstatusReg(CSRFile.MSTATUS_MIE_BIT)
  val mstatusMpie = mstatusReg(CSRFile.MSTATUS_MPIE_BIT)

  // Helper: build new mstatus with MIE, MPIE, and MPP updated.
  // MPP is always forced to 11 (M-mode) since this core only implements M-mode.
  def mstatusWithMieMpieMpp(current: UInt, newMie: Bool, newMpie: Bool): UInt = {
    val mieMask  = (BigInt(1) << CSRFile.MSTATUS_MIE_BIT).U(xlen.W)
    val mpieMask = (BigInt(1) << CSRFile.MSTATUS_MPIE_BIT).U(xlen.W)
    val mppMask  = (BigInt(3) << CSRFile.MSTATUS_MPP_LSB).U(xlen.W)
    val mppM     = (BigInt(3) << CSRFile.MSTATUS_MPP_LSB).U(xlen.W)

    val cleared = current & ~(mieMask | mpieMask | mppMask)

    cleared |
      Mux(newMie, mieMask, 0.U) |
      Mux(newMpie, mpieMask, 0.U) |
      mppM
  }

  val softwareWritesMstatus = io.wen && (io.addr === CSRFile.MSTATUS.U)

  when (io.takeTrap) {
    // Save MIE -> MPIE, clear MIE, force MPP = M
    mstatusReg := mstatusWithMieMpieMpp(mstatusReg, newMie = false.B, newMpie = mstatusMie)
  } .elsewhen (io.takeMret) {
    // Restore MIE from MPIE, set MPIE = 1, force MPP = M
    mstatusReg := mstatusWithMieMpieMpp(mstatusReg, newMie = mstatusMpie, newMpie = true.B)
  } .elsewhen (softwareWritesMstatus) {
    mstatusReg := io.wdata
  }

  // --------------------------------------------------------------------------
  // Trap entry writes to mepc / mcause / mtval
  //
  // These happen atomically with mstatus update on takeTrap.
  // --------------------------------------------------------------------------

  when (io.takeTrap) {
    mepc   := io.trapEpc
    mcause := io.trapCause
    mtval  := io.trapTval
  }

  // --------------------------------------------------------------------------
  // Software CSR writes (only effective when no trap/mret this cycle and
  // the trap-entry path isn't writing the same register)
  // --------------------------------------------------------------------------

  val softwareCanWrite = io.wen && !io.takeTrap && !io.takeMret

  when (softwareCanWrite) {
    switch(io.addr) {
      is(CSRFile.MTVEC.U)    { mtvec    := io.wdata }
      is(CSRFile.MIE.U)      { mieReg   := io.wdata }
      is(CSRFile.MSCRATCH.U) { mscratch := io.wdata }
      is(CSRFile.MEPC.U)     { mepc     := io.wdata }
      is(CSRFile.MCAUSE.U)   { mcause   := io.wdata }
      is(CSRFile.MTVAL.U)    { mtval    := io.wdata }
      // mstatus handled above
      // mip: software writes to mip in this core are ignored
      //      (hardware-only pending bits)
      // misa: read-only in this core
      // mhartid: read-only
    }
  }

  // --------------------------------------------------------------------------
  // Read port
  // --------------------------------------------------------------------------

  io.rdata := MuxLookup(io.addr, 0.U)(Seq(
    CSRFile.MSTATUS.U  -> mstatusReg,
    CSRFile.MISA.U     -> misa,
    CSRFile.MIE.U      -> mieReg,
    CSRFile.MTVEC.U    -> mtvec,
    CSRFile.MSCRATCH.U -> mscratch,
    CSRFile.MEPC.U     -> mepc,
    CSRFile.MCAUSE.U   -> mcause,
    CSRFile.MTVAL.U    -> mtval,
    CSRFile.MIP.U      -> mip,
    CSRFile.MHARTID.U  -> 0.U
  ))

  // --------------------------------------------------------------------------
  // Exports
  // --------------------------------------------------------------------------

  io.mstatus := mstatusReg
  io.mie     := mieReg
  io.mip     := mip
  io.mtvec   := mtvec
  io.mepc    := mepc
}