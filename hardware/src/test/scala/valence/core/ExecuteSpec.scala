package valence.core

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import valence.execution.ALU
import valence.execution.BranchUnit

class ExecuteSpec extends AnyFlatSpec with Matchers {

  behavior of "Execute"

  def test(fn: Execute => Unit): Unit =
    simulate(new Execute) { dut =>
      dut.reset.poke(true)
      dut.clock.step()
      dut.reset.poke(false)
      dut.io.in.pc.poke(0x1000.U)
      dut.io.in.rs1_val.poke(0.U)
      dut.io.in.rs2_val.poke(0.U)
      dut.io.in.imm.poke(0.U)
      dut.io.in.rd.poke(0.U)
      dut.io.in.aluOp.poke(ALU.ADD.U)
      dut.io.in.brOp.poke(0.U)
      dut.io.in.useImm.poke(false)
      dut.io.in.isLoad.poke(false)
      dut.io.in.isStore.poke(false)
      dut.io.in.isBranch.poke(false)
      dut.io.in.isJal.poke(false)
      dut.io.in.isJalr.poke(false)
      dut.io.in.isLui.poke(false)
      dut.io.in.isAuipc.poke(false)
      dut.io.in.isCsr.poke(false)
      dut.io.in.valid.poke(true)
      fn(dut)
    }

  it should "compute ADD" in {
    test { dut =>
      dut.io.in.aluOp.poke(ALU.ADD.U)
      dut.io.in.rs1_val.poke(10.U)
      dut.io.in.rs2_val.poke(20.U)
      dut.clock.step()
      dut.io.out.result.expect(30.U)
    }
  }

  it should "use immediate when useImm set" in {
    test { dut =>
      dut.io.in.aluOp.poke(ALU.ADD.U)
      dut.io.in.rs1_val.poke(10.U)
      dut.io.in.imm.poke(5.U)
      dut.io.in.useImm.poke(true)
      dut.clock.step()
      dut.io.out.result.expect(15.U)
    }
  }

  it should "compute LUI (load upper immediate)" in {
    test { dut =>
      dut.io.in.isLui.poke(true)
      dut.io.in.imm.poke(0x12345000L.U)
      dut.clock.step()
      dut.io.out.result.expect(0x12345000L.U)
    }
  }

  it should "compute AUIPC (add upper immediate to PC)" in {
    test { dut =>
      dut.io.in.pc.poke(0x1000.U)
      dut.io.in.isAuipc.poke(true)
      dut.io.in.imm.poke(0x1000.U)
      dut.clock.step()
      dut.io.out.result.expect(0x2000.U)
    }
  }

  it should "detect branch taken" in {
    test { dut =>
      dut.io.in.isBranch.poke(true)
      dut.io.in.brOp.poke(BranchUnit.BEQ.U)
      dut.io.in.rs1_val.poke(5.U)
      dut.io.in.rs2_val.poke(5.U)
      dut.io.in.pc.poke(0x1000.U)
      dut.io.in.imm.poke(0x10.U)
      dut.clock.step()
      dut.io.out.branch_taken.expect(true)
      dut.io.out.branch_target.expect(0x1010.U)
    }
  }

  it should "compute JAL return address" in {
    test { dut =>
      dut.io.in.isJal.poke(true)
      dut.io.in.pc.poke(0x2000.U)
      dut.io.in.imm.poke(0x100.U)
      dut.clock.step()
      dut.io.out.result.expect(0x2004.U)  // pc+4
      dut.io.out.branch_taken.expect(true)
      dut.io.out.branch_target.expect(0x2100.U)  // pc+imm
    }
  }
}