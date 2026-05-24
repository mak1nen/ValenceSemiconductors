package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec

class TrapUnitSpec extends AnyFlatSpec {

  // TrapUnit is purely combinational, so we don't need any reset sequence
  // or clock stepping. Each test just pokes inputs and peeks outputs.

  // Helper: bit positions in mstatus / mie
  private val MIE_BIT  = 3
  private val MSIE_BIT = 3
  private val MTIE_BIT = 7
  private val MEIE_BIT = 11

  private val INTERRUPT_BIT = BigInt(1) << 63

  // Convenience: build mstatus / mie values
  private def mstatusWithMie(enable: Boolean): BigInt =
    if (enable) BigInt(1) << MIE_BIT else BigInt(0)

  private def mieMask(mei: Boolean = false, mti: Boolean = false, msi: Boolean = false): BigInt = {
    var v = BigInt(0)
    if (mei) v |= BigInt(1) << MEIE_BIT
    if (mti) v |= BigInt(1) << MTIE_BIT
    if (msi) v |= BigInt(1) << MSIE_BIT
    v
  }

  // Drive all TrapUnit inputs to safe defaults so tests only set what they care about.
  private def driveDefaults(dut: TrapUnit): Unit = {
    dut.io.pc.poke(0.U)
    dut.io.instr.poke(0.U)
    dut.io.illegalInstr.poke(false.B)
    dut.io.ecall.poke(false.B)
    dut.io.ebreak.poke(false.B)
    dut.io.instrAddrMisaligned.poke(false.B)
    dut.io.loadAddrMisaligned.poke(false.B)
    dut.io.storeAddrMisaligned.poke(false.B)
    dut.io.badAddr.poke(0.U)
    dut.io.mret.poke(false.B)
    dut.io.mtvec.poke(0.U)
    dut.io.mepc.poke(0.U)
    dut.io.mstatus.poke(0.U)
    dut.io.mie.poke(0.U)
    dut.io.machineSoftwareInterrupt.poke(false.B)
    dut.io.machineTimerInterrupt.poke(false.B)
    dut.io.machineExternalInterrupt.poke(false.B)
  }

  // ==========================================================================
  // Idle / quiescent behavior
  // ==========================================================================

  behavior of "TrapUnit (idle)"

  it should "not assert takeTrap, takeMret, or redirect when no exception, interrupt, or mret" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.takeTrap.expect(false.B)
      dut.io.takeMret.expect(false.B)
      dut.io.redirect.expect(false.B)
      dut.io.flush.expect(false.B)
      dut.io.isInterrupt.expect(false.B)
    }
  }

  it should "not take an interrupt when mstatus.MIE is clear even with mie and line set" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(0.U)                       // MIE = 0
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)
      dut.io.takeTrap.expect(false.B)
      dut.io.isInterrupt.expect(false.B)
    }
  }

  it should "not take an interrupt when mie bit is clear even with line and mstatus.MIE set" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(0.U)                           // mtie = 0
      dut.io.machineTimerInterrupt.poke(true.B)
      dut.io.takeTrap.expect(false.B)
    }
  }

  // ==========================================================================
  // Synchronous exceptions
  // ==========================================================================

  behavior of "TrapUnit (synchronous exceptions)"

  it should "take an illegal-instruction trap with instr in mtval" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.pc.poke("h1000".U)
      dut.io.instr.poke("hDEADBEEF".U)
      dut.io.illegalInstr.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.isInterrupt.expect(false.B)
      dut.io.trapCause.expect(TrapCause.IllegalInstruction.U)
      dut.io.trapEpc.expect("h1000".U)
      dut.io.trapTval.expect("hDEADBEEF".U)
    }
  }

  it should "take an instr-address-misaligned trap with bad addr in mtval" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.pc.poke("h1002".U)
      dut.io.badAddr.poke("h1002".U)
      dut.io.instrAddrMisaligned.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.InstrAddrMisaligned.U)
      dut.io.trapTval.expect("h1002".U)
    }
  }

  it should "take an ECALL trap with mtval = 0" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.pc.poke("h2000".U)
      dut.io.ecall.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.EcallM.U)
      dut.io.trapTval.expect(0.U)
      dut.io.trapEpc.expect("h2000".U)
    }
  }

  it should "take an EBREAK trap with mtval = 0 (spec 1.12)" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.pc.poke("h3000".U)
      dut.io.ebreak.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.Breakpoint.U)
      dut.io.trapTval.expect(0.U)
    }
  }

  it should "take a load-misaligned trap with bad addr in mtval" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.badAddr.poke("h1003".U)
      dut.io.loadAddrMisaligned.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.LoadAddrMisaligned.U)
      dut.io.trapTval.expect("h1003".U)
    }
  }

  it should "take a store-misaligned trap with bad addr in mtval" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.badAddr.poke("h1005".U)
      dut.io.storeAddrMisaligned.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.StoreAddrMisaligned.U)
      dut.io.trapTval.expect("h1005".U)
    }
  }

  // ==========================================================================
  // Exception priority
  // ==========================================================================

  behavior of "TrapUnit (exception priority)"

  it should "prefer illegal-instr over instr-misaligned when both assert" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.instr.poke("hAABBCCDD".U)
      dut.io.badAddr.poke("h1002".U)
      dut.io.illegalInstr.poke(true.B)
      dut.io.instrAddrMisaligned.poke(true.B)

      dut.io.trapCause.expect(TrapCause.IllegalInstruction.U)
      dut.io.trapTval.expect("hAABBCCDD".U)
    }
  }

  it should "prefer instr-misaligned over ECALL when both assert" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.badAddr.poke("h2002".U)
      dut.io.instrAddrMisaligned.poke(true.B)
      dut.io.ecall.poke(true.B)

      dut.io.trapCause.expect(TrapCause.InstrAddrMisaligned.U)
      dut.io.trapTval.expect("h2002".U)
    }
  }

  it should "prefer ECALL over EBREAK when both assert" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.ecall.poke(true.B)
      dut.io.ebreak.poke(true.B)

      dut.io.trapCause.expect(TrapCause.EcallM.U)
    }
  }

  // ==========================================================================
  // Interrupts
  // ==========================================================================

  behavior of "TrapUnit (interrupts)"

  it should "take a machine timer interrupt when armed" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.pc.poke("h4000".U)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)

      dut.io.takeTrap.expect(true.B)
      dut.io.isInterrupt.expect(true.B)
      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineTimerInterrupt)).U)
      dut.io.trapEpc.expect("h4000".U)
      dut.io.trapTval.expect(0.U)
    }
  }

  it should "take a machine software interrupt when armed" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(msi = true).U)
      dut.io.machineSoftwareInterrupt.poke(true.B)

      dut.io.isInterrupt.expect(true.B)
      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineSoftwareInterrupt)).U)
    }
  }

  it should "take a machine external interrupt when armed" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mei = true).U)
      dut.io.machineExternalInterrupt.poke(true.B)

      dut.io.isInterrupt.expect(true.B)
      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineExternalInterrupt)).U)
    }
  }

  // ==========================================================================
  // Interrupt priority (RISC-V spec: MEI > MSI > MTI)
  // ==========================================================================

  behavior of "TrapUnit (interrupt priority)"

  it should "prefer external over software" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mei = true, msi = true).U)
      dut.io.machineExternalInterrupt.poke(true.B)
      dut.io.machineSoftwareInterrupt.poke(true.B)

      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineExternalInterrupt)).U)
    }
  }

  it should "prefer software over timer" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(msi = true, mti = true).U)
      dut.io.machineSoftwareInterrupt.poke(true.B)
      dut.io.machineTimerInterrupt.poke(true.B)

      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineSoftwareInterrupt)).U)
    }
  }

  it should "prefer external over timer and software when all three pending" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mei = true, mti = true, msi = true).U)
      dut.io.machineExternalInterrupt.poke(true.B)
      dut.io.machineTimerInterrupt.poke(true.B)
      dut.io.machineSoftwareInterrupt.poke(true.B)

      dut.io.trapCause.expect((INTERRUPT_BIT | BigInt(TrapCause.MachineExternalInterrupt)).U)
    }
  }

  // ==========================================================================
  // Exception vs interrupt: exception always wins
  // ==========================================================================

  behavior of "TrapUnit (exception vs interrupt)"

  it should "prefer synchronous exception over a pending interrupt" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)
      dut.io.illegalInstr.poke(true.B)
      dut.io.instr.poke("hAABBCCDD".U)

      dut.io.takeTrap.expect(true.B)
      dut.io.isInterrupt.expect(false.B)
      dut.io.trapCause.expect(TrapCause.IllegalInstruction.U)
    }
  }

  // ==========================================================================
  // MRET handling
  // ==========================================================================

  behavior of "TrapUnit (mret)"

  it should "take an mret with redirect to mepc" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mret.poke(true.B)
      dut.io.mepc.poke("h5000".U)

      dut.io.takeMret.expect(true.B)
      dut.io.takeTrap.expect(false.B)
      dut.io.redirect.expect(true.B)
      dut.io.redirectPc.expect("h5000".U)
      dut.io.flush.expect(true.B)
    }
  }

  it should "not take mret if a synchronous exception fires the same cycle" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mret.poke(true.B)
      dut.io.mepc.poke("h5000".U)
      dut.io.illegalInstr.poke(true.B)

      // Exception wins: takeTrap asserts, takeMret does not.
      dut.io.takeMret.expect(false.B)
      dut.io.takeTrap.expect(true.B)
      dut.io.trapCause.expect(TrapCause.IllegalInstruction.U)
    }
  }

  it should "take mret over a pending interrupt in the same cycle" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mret.poke(true.B)
      dut.io.mepc.poke("h5000".U)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)

      dut.io.takeMret.expect(true.B)
      dut.io.takeTrap.expect(false.B)
      dut.io.isInterrupt.expect(false.B)
      dut.io.redirectPc.expect("h5000".U)
    }
  }

  // ==========================================================================
  // mtvec target routing
  // ==========================================================================

  behavior of "TrapUnit (mtvec target)"

  it should "redirect exceptions to mtvec base regardless of mode" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      // mtvec = 0x80000001 -> base = 0x80000000, mode = vectored
      dut.io.mtvec.poke("h80000001".U)
      dut.io.illegalInstr.poke(true.B)

      // Exception always uses base, never vectored offset
      dut.io.redirect.expect(true.B)
      dut.io.redirectPc.expect("h80000000".U)
    }
  }

  it should "redirect interrupts to mtvec base in direct mode" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mtvec.poke("h80000000".U)   // base=0x80000000, mode=00 direct
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)

      dut.io.redirectPc.expect("h80000000".U)
    }
  }

  it should "redirect interrupts to base + 4*cause in vectored mode" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      // base=0x80000000, mode=01 vectored
      dut.io.mtvec.poke("h80000001".U)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)

      // MTI cause code = 7, so offset = 28 = 0x1C
      dut.io.redirectPc.expect("h8000001C".U)
    }
  }

  it should "use correct vectored offset for external interrupt (cause 11)" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.mtvec.poke("h80000001".U)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mei = true).U)
      dut.io.machineExternalInterrupt.poke(true.B)

      // MEI cause code = 11, offset = 44 = 0x2C
      dut.io.redirectPc.expect("h8000002C".U)
    }
  }

  it should "treat reserved mtvec mode 2 as direct" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      // mode = 10 (reserved), should behave as direct
      dut.io.mtvec.poke("h80000002".U)
      dut.io.mstatus.poke(mstatusWithMie(true).U)
      dut.io.mie.poke(mieMask(mti = true).U)
      dut.io.machineTimerInterrupt.poke(true.B)

      dut.io.redirectPc.expect("h80000000".U)
    }
  }

  // ==========================================================================
  // Redirect / flush correlation
  // ==========================================================================

  behavior of "TrapUnit (redirect / flush)"

  it should "assert flush whenever it asserts redirect" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)
      dut.io.illegalInstr.poke(true.B)

      dut.io.redirect.expect(true.B)
      dut.io.flush.expect(true.B)
    }
  }

  it should "not assert redirect when idle" in {
    simulate(new TrapUnit(64)) { dut =>
      driveDefaults(dut)

      dut.io.redirect.expect(false.B)
      dut.io.flush.expect(false.B)
    }
  }
}