package valence.core

import chisel3._
import chisel3.util._

object TrapCause {
  // Synchronous exception cause codes (mcause without the interrupt bit set)
  val InstrAddrMisaligned = 0
  val IllegalInstruction  = 2
  val Breakpoint          = 3
  val LoadAddrMisaligned  = 4
  val StoreAddrMisaligned = 6
  val EcallU              = 8   // ECALL from U-mode (future)
  val EcallS              = 9   // ECALL from S-mode (future)
  val EcallM              = 11

  // Interrupt cause codes (mcause low bits when interrupt bit is set).
  //
  // RISC-V Privileged spec priority order, highest first:
  //   MEI > MSI > MTI > SEI > SSI > STI > UEI > USI > UTI
  //
  // Currently this core only handles the three M-mode interrupts. The S/U
  // constants are defined here for forward reference but are not wired into
  // the TrapUnit until S-mode and U-mode are implemented.
  val MachineExternalInterrupt    = 11
  val MachineSoftwareInterrupt    = 3
  val MachineTimerInterrupt       = 7

  val SupervisorExternalInterrupt = 9
  val SupervisorSoftwareInterrupt = 1
  val SupervisorTimerInterrupt    = 5

  val UserExternalInterrupt       = 8
  val UserSoftwareInterrupt       = 0
  val UserTimerInterrupt          = 4

  // Sentinel for "no cause asserted" - reserved code so a buggy takeTrap
  // assertion is visible rather than masquerading as cause 0
  // (instr-misaligned).
  val NoCause = 0x1F
}

class TrapUnit(xlen: Int) extends Module {
  require(xlen == 64, "TrapUnit currently assumes RV64")

  val io = IO(new Bundle {
    // ----- Context for the instruction being evaluated this cycle -----
    val pc    = Input(UInt(xlen.W))
    val instr = Input(UInt(32.W))

    // ----- Synchronous exception inputs -----
    val illegalInstr        = Input(Bool())
    val ecall               = Input(Bool())
    val ebreak              = Input(Bool())
    val instrAddrMisaligned = Input(Bool())
    val loadAddrMisaligned  = Input(Bool())
    val storeAddrMisaligned = Input(Bool())
    val badAddr             = Input(UInt(xlen.W))

    // ----- Return from machine trap -----
    val mret = Input(Bool())

    // ----- CSR inputs -----
    val mtvec   = Input(UInt(xlen.W))
    val mepc    = Input(UInt(xlen.W))
    val mstatus = Input(UInt(xlen.W))
    val mie     = Input(UInt(xlen.W))

    // ----- Raw interrupt line inputs (level-sensitive, from PLIC/CLINT) -----
    val machineSoftwareInterrupt = Input(Bool())
    val machineTimerInterrupt    = Input(Bool())
    val machineExternalInterrupt = Input(Bool())

    // ----- Trap outputs (to CSRFile, to update mepc/mcause/mtval/mstatus) -----
    val takeTrap    = Output(Bool())
    val isInterrupt = Output(Bool())
    val trapEpc     = Output(UInt(xlen.W))
    val trapCause   = Output(UInt(xlen.W))
    val trapTval    = Output(UInt(xlen.W))

    // ----- MRET output (to CSRFile, to restore mstatus from MPP/MPIE) -----
    val takeMret = Output(Bool())

    // ----- Pipeline redirect / flush -----
    val redirect   = Output(Bool())
    val redirectPc = Output(UInt(xlen.W))
    val flush      = Output(Bool())
  })

  // --------------------------------------------------------------------------
  // CSR bit aliases
  //
  // mstatus.MIE = bit 3   (global machine interrupt enable)
  // mie.MSIE    = bit 3   (machine software interrupt enable)
  // mie.MTIE    = bit 7   (machine timer interrupt enable)
  // mie.MEIE    = bit 11  (machine external interrupt enable)
  // --------------------------------------------------------------------------

  val mstatusMie = io.mstatus(3)
  val msie       = io.mie(3)
  val mtie       = io.mie(7)
  val meie       = io.mie(11)

  // --------------------------------------------------------------------------
  // Interrupt evaluation
  //
  // Each interrupt is taken only if:
  //   global MIE in mstatus is set, AND
  //   the per-interrupt enable in mie is set, AND
  //   the input line is asserted.
  //
  // Priority (RISC-V Privileged spec, Section 3.1.9): MEI > MSI > MTI
  // --------------------------------------------------------------------------

  val pendMSI = msie && io.machineSoftwareInterrupt
  val pendMTI = mtie && io.machineTimerInterrupt
  val pendMEI = meie && io.machineExternalInterrupt

  val anyPending      = pendMEI || pendMTI || pendMSI
  val interruptArmed  = mstatusMie && anyPending

  val interruptCauseCode = WireDefault(TrapCause.NoCause.U(xlen.W))
  when (pendMEI) {
    interruptCauseCode := TrapCause.MachineExternalInterrupt.U(xlen.W)
  } .elsewhen (pendMSI) {
    interruptCauseCode := TrapCause.MachineSoftwareInterrupt.U(xlen.W)
  } .elsewhen (pendMTI) {
    interruptCauseCode := TrapCause.MachineTimerInterrupt.U(xlen.W)
  }

  // mcause encoding: bit (xlen-1) is the interrupt flag, low bits are the code
  val interruptBit   = (BigInt(1) << (xlen - 1)).U(xlen.W)
  val interruptCause = interruptBit | interruptCauseCode

  // --------------------------------------------------------------------------
  // Synchronous exception evaluation
  //
  // Priority (per RISC-V Privileged spec, highest first for the subset we
  // implement):
  //   illegal instruction        (instr couldn't decode)
  //   instruction addr misaligned
  //   ECALL
  //   EBREAK
  //   load addr misaligned
  //   store addr misaligned
  //
  // In an in-order pipeline only one of these typically asserts per
  // instruction, but if two co-occur (e.g. illegal-instr at a misaligned
  // PC), spec mandates illegal-instr wins.
  // --------------------------------------------------------------------------

  val exceptionPending =
    io.illegalInstr        ||
    io.instrAddrMisaligned ||
    io.ecall               ||
    io.ebreak              ||
    io.loadAddrMisaligned  ||
    io.storeAddrMisaligned

  val exceptionCause = WireDefault(TrapCause.NoCause.U(xlen.W))
  val exceptionTval  = WireDefault(0.U(xlen.W))

  when (io.illegalInstr) {
    exceptionCause := TrapCause.IllegalInstruction.U(xlen.W)
    // mtval for illegal instr is the offending instruction word, zero-extended
    exceptionTval  := Cat(0.U((xlen - 32).W), io.instr)
  } .elsewhen (io.instrAddrMisaligned) {
    exceptionCause := TrapCause.InstrAddrMisaligned.U(xlen.W)
    exceptionTval  := io.badAddr
  } .elsewhen (io.ecall) {
    exceptionCause := TrapCause.EcallM.U(xlen.W)
    exceptionTval  := 0.U
  } .elsewhen (io.ebreak) {
    exceptionCause := TrapCause.Breakpoint.U(xlen.W)
    // RISC-V Privileged spec 1.12: mtval for EBREAK is 0 (was PC in older specs)
    exceptionTval  := 0.U
  } .elsewhen (io.loadAddrMisaligned) {
    exceptionCause := TrapCause.LoadAddrMisaligned.U(xlen.W)
    exceptionTval  := io.badAddr
  } .elsewhen (io.storeAddrMisaligned) {
    exceptionCause := TrapCause.StoreAddrMisaligned.U(xlen.W)
    exceptionTval  := io.badAddr
  }

  // --------------------------------------------------------------------------
  // Final trap decision
  //
  // Priority:
  //   1. Synchronous exception on this instruction
  //   2. MRET (a normal instruction; only retires if it didn't itself fault)
  //   3. Interrupt (only when no exception is being taken and no mret retires
  //      this cycle, so mret cleanly completes before its first post-restore
  //      instruction)
  // --------------------------------------------------------------------------

  val takeException = exceptionPending
  val takeMret      = io.mret && !takeException
  val takeInterrupt = interruptArmed && !takeException && !io.mret
  val takeTrap      = takeException || takeInterrupt

  io.takeTrap    := takeTrap
  io.isInterrupt := takeInterrupt
  io.takeMret    := takeMret

  io.trapEpc := io.pc

  io.trapCause := Mux(
    takeInterrupt,
    interruptCause,
    exceptionCause
  )

  io.trapTval := Mux(
    takeInterrupt,
    0.U,
    exceptionTval
  )

  // --------------------------------------------------------------------------
  // Trap target from mtvec
  //
  //   mtvec[63:2] = base (always 4-byte aligned)
  //   mtvec[1:0]  = mode
  //                 00 = direct   : target = base
  //                 01 = vectored : target = base + 4 * cause_code  (interrupts only)
  //                 10, 11        = reserved; treat as direct
  //
  // Exceptions always go to base regardless of mode.
  // --------------------------------------------------------------------------

  val mtvecBase = Cat(io.mtvec(xlen - 1, 2), 0.U(2.W))
  val mtvecMode = io.mtvec(1, 0)

  // Shift cause code by 2 (to get *4), keep xlen bits.
  val vectoredOffset = (interruptCauseCode << 2)(xlen - 1, 0)
  val trapTargetVectored = mtvecBase + vectoredOffset
  val trapTargetDirect   = mtvecBase

  val useVectored = takeInterrupt && (mtvecMode === 1.U(2.W))

  val trapTarget = Mux(useVectored, trapTargetVectored, trapTargetDirect)

  // --------------------------------------------------------------------------
  // Pipeline redirect
  //
  // A trap goes to mtvec, an mret returns to mepc, otherwise no redirect.
  // Flush is asserted alongside any redirect so in-flight instructions
  // behind this stage get squashed.
  // --------------------------------------------------------------------------

  io.redirect := takeTrap || takeMret

  io.redirectPc := Mux(
    takeTrap,
    trapTarget,
    io.mepc
  )

  io.flush := io.redirect
}