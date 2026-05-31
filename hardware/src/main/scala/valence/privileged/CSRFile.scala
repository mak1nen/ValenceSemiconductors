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

  // Counter CSRs
  val MCYCLE   = 0xB00
  val MINSTRET = 0xB02
  val CYCLE    = 0xC00
  val INSTRET  = 0xC02

  // mstatus bit positions (RV64)
  val MSTATUS_MIE_BIT  = 3
  val MSTATUS_MPIE_BIT = 7
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
  require(xlen == 64, "CSRFile currently assumes RV64")

  val io = IO(new Bundle {
    // ------------------------------------------------------------------------
    // Software CSR read/write port.
    //
    // Core.scala computes the CSR instruction behavior:
    //   CSRRW  -> wdata = rs1
    //   CSRRS  -> wdata = old | rs1
    //   CSRRC  -> wdata = old & ~rs1
    //   CSRRWI -> wdata = uimm
    //   CSRRSI -> wdata = old | uimm
    //   CSRRCI -> wdata = old & ~uimm
    //
    // CSRFile only performs:
    //   read:  rdata = CSR[addr]
    //   write: if wen, CSR[addr] := wdata
    // ------------------------------------------------------------------------
    val addr   = Input(UInt(12.W))
    val wen    = Input(Bool())
    val wdata  = Input(UInt(xlen.W))
    val rdata  = Output(UInt(xlen.W))

    // Retire pulse for minstret / instret.
    val retire = Input(Bool())

    // ------------------------------------------------------------------------
    // Trap entry interface from TrapUnit.
    // ------------------------------------------------------------------------
    val takeTrap  = Input(Bool())
    val trapEpc   = Input(UInt(xlen.W))
    val trapCause = Input(UInt(xlen.W))
    val trapTval  = Input(UInt(xlen.W))

    // MRET interface from TrapUnit.
    val takeMret = Input(Bool())

    // Hardware interrupt line inputs.
    val mtipIn = Input(Bool())  // machine timer interrupt pending
    val msipIn = Input(Bool())  // machine software interrupt pending
    val meipIn = Input(Bool())  // machine external interrupt pending

    // CSR value exports for TrapUnit / other modules.
    val mstatus = Output(UInt(xlen.W))
    val mie     = Output(UInt(xlen.W))
    val mip     = Output(UInt(xlen.W))
    val mtvec   = Output(UInt(xlen.W))
    val mepc    = Output(UInt(xlen.W))
  })

  // --------------------------------------------------------------------------
  // MISA value
  //
  // RV64 MXL = 2 in bits [63:62]
  //
  // Extension bits:
  //   A = bit 0
  //   I = bit 8
  //   M = bit 12
  //   S = bit 18
  //   U = bit 20
  //
  // This advertises RV64IMASU.
  // NOTE: This is enough to let OpenSBI take the S-mode-capable coldboot path.
  // Full Linux boot will still require real S-mode behavior later.
  // --------------------------------------------------------------------------

  private val misaValue = (
    (BigInt(2) << 62) | // RV64
    (BigInt(1) << 0)  | // A
    (BigInt(1) << 8)  | // I
    (BigInt(1) << 12) | // M
    (BigInt(1) << 18) | // S
    (BigInt(1) << 20)   // U
  ).U(xlen.W)

  // --------------------------------------------------------------------------
  // CSR storage
  // --------------------------------------------------------------------------

  val mstatusReg = RegInit(0.U(xlen.W))

  val mieReg   = RegInit(0.U(xlen.W))
  val mtvec    = RegInit(0.U(xlen.W))
  val mscratch = RegInit(0.U(xlen.W))
  val mepc     = RegInit(0.U(xlen.W))
  val mcause   = RegInit(0.U(xlen.W))
  val mtval    = RegInit(0.U(xlen.W))

  // --------------------------------------------------------------------------
  // Counter CSRs
  // --------------------------------------------------------------------------

  val mcycle   = RegInit(0.U(xlen.W))
  val minstret = RegInit(0.U(xlen.W))

  mcycle := mcycle + 1.U

  when (io.retire) {
    minstret := minstret + 1.U
  }

  // --------------------------------------------------------------------------
  // mip register
  //
  // In this minimal core, real interrupt-pending bits are hardware driven.
  // Software writes to mip are ignored.
  // --------------------------------------------------------------------------

  val mip = Wire(UInt(xlen.W))
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
  // mstatus helpers
  // --------------------------------------------------------------------------

  val mstatusMie  = mstatusReg(CSRFile.MSTATUS_MIE_BIT)
  val mstatusMpie = mstatusReg(CSRFile.MSTATUS_MPIE_BIT)

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

  // Preserve user-provided mstatus bits but force MPP=M for now.
  //
  // TODO:
  // Once real S-mode is implemented, do not force MPP=M.
  // OpenSBI will eventually need to set MPP=S before mret into the payload.
  def normalizeMstatus(x: UInt): UInt = {
    val mppMask = (BigInt(3) << CSRFile.MSTATUS_MPP_LSB).U(xlen.W)
    val mppM    = (BigInt(3) << CSRFile.MSTATUS_MPP_LSB).U(xlen.W)

    (x & ~mppMask) | mppM
  }

  // --------------------------------------------------------------------------
  // mstatus update priority
  //
  // Priority:
  //   1. Trap entry
  //   2. MRET
  //   3. Software CSR write
  // --------------------------------------------------------------------------

  val softwareCanWrite = io.wen && !io.takeTrap && !io.takeMret

  when (io.takeTrap) {
    // Save MIE -> MPIE, clear MIE, force MPP = M for now.
    mstatusReg := mstatusWithMieMpieMpp(
      mstatusReg,
      newMie  = false.B,
      newMpie = mstatusMie
    )
  } .elsewhen (io.takeMret) {
    // Restore MIE from MPIE, set MPIE = 1, force MPP = M for now.
    mstatusReg := mstatusWithMieMpieMpp(
      mstatusReg,
      newMie  = mstatusMpie,
      newMpie = true.B
    )
  } .elsewhen (softwareCanWrite && io.addr === CSRFile.MSTATUS.U) {
    mstatusReg := normalizeMstatus(io.wdata)
  }

  // --------------------------------------------------------------------------
  // Trap entry writes to mepc / mcause / mtval
  // --------------------------------------------------------------------------

  when (io.takeTrap) {
    mepc   := io.trapEpc
    mcause := io.trapCause
    mtval  := io.trapTval
  }

  // --------------------------------------------------------------------------
  // Software CSR writes
  //
  // Core.scala computes the final CSR write value.
  // CSRFile just stores io.wdata into the selected CSR.
  // --------------------------------------------------------------------------

  when (softwareCanWrite) {
    switch(io.addr) {
      is(CSRFile.MTVEC.U)    { mtvec    := io.wdata }
      is(CSRFile.MIE.U)      { mieReg   := io.wdata }
      is(CSRFile.MSCRATCH.U) { mscratch := io.wdata }
      is(CSRFile.MEPC.U)     { mepc     := io.wdata }
      is(CSRFile.MCAUSE.U)   { mcause   := io.wdata }
      is(CSRFile.MTVAL.U)    { mtval    := io.wdata }

      // Machine counter CSRs are writable in this minimal M-mode implementation.
      is(CSRFile.MCYCLE.U)   { mcycle   := io.wdata }
      is(CSRFile.MINSTRET.U) { minstret := io.wdata }

      // mstatus handled above.
      // misa is read-only.
      // mip is hardware driven for implemented interrupt pending bits.
      // mhartid is read-only.
      // cycle/instret are read-only aliases here.
    }
  }

  // --------------------------------------------------------------------------
  // Read port
  // --------------------------------------------------------------------------

  io.rdata := MuxLookup(io.addr, 0.U(xlen.W))(Seq(
    CSRFile.MSTATUS.U  -> mstatusReg,
    CSRFile.MISA.U     -> misaValue,
    CSRFile.MIE.U      -> mieReg,
    CSRFile.MTVEC.U    -> mtvec,
    CSRFile.MSCRATCH.U -> mscratch,
    CSRFile.MEPC.U     -> mepc,
    CSRFile.MCAUSE.U   -> mcause,
    CSRFile.MTVAL.U    -> mtval,
    CSRFile.MIP.U      -> mip,
    CSRFile.MHARTID.U  -> 0.U(xlen.W),

    CSRFile.MCYCLE.U   -> mcycle,
    CSRFile.CYCLE.U    -> mcycle,
    CSRFile.MINSTRET.U -> minstret,
    CSRFile.INSTRET.U  -> minstret
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