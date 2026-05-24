package valence.execution

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec

class MulDivSpec extends AnyFlatSpec {

  // Convenience: drive op/rs1/rs2 and check result.
  // No reset needed because MulDiv is combinational.
  private def check(
    name: String,
    op: Int,
    rs1: BigInt,
    rs2: BigInt,
    expected: BigInt
  ): Unit = {
    simulate(new MulDiv(64)) { dut =>
      dut.io.op.poke(op.U)
      dut.io.rs1.poke(rs1.U(64.W))
      dut.io.rs2.poke(rs2.U(64.W))
      dut.clock.step()
      val got = dut.io.result.peek().litValue
      assert(
        got == expected,
        s"\n[$name] op=$op  rs1=0x${rs1.toString(16)}  rs2=0x${rs2.toString(16)}\n" +
        s"  expected 0x${expected.toString(16)}\n" +
        s"  got      0x${got.toString(16)}"
      )
    }
  }

  // Helpers for 64-bit arithmetic on BigInt with proper wrapping
  private val mask64 = (BigInt(1) << 64) - 1
  private val mask32 = (BigInt(1) << 32) - 1

  // Sign-extend a 32-bit value to 64 bits as RISC-V W-ops do
  private def sext32to64(x: BigInt): BigInt = {
    val low32 = x & mask32
    if ((low32 & (BigInt(1) << 31)) != 0) low32 | (mask32 << 32)
    else low32
  }

  // Treat a 64-bit unsigned as signed
  private def asSigned64(x: BigInt): BigInt = {
    val u = x & mask64
    if ((u & (BigInt(1) << 63)) != 0) u - (BigInt(1) << 64)
    else u
  }

  // ==========================================================================
  // 64-bit MUL family
  // ==========================================================================

  behavior of "MulDiv MUL"

  it should "multiply small positive values" in {
    check("MUL 6 * 7", MulDivOp.MUL, 6, 7, 42)
  }

  it should "discard the upper 64 bits of the product" in {
    // 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE_00000001, low 64 = that whole thing
    check("MUL big*big low",
      MulDivOp.MUL,
      BigInt("FFFFFFFF", 16),
      BigInt("FFFFFFFF", 16),
      BigInt("FFFFFFFE00000001", 16))
  }

  it should "handle signed * signed where MUL gives unsigned low bits" in {
    // (-1) * (-1) = 1, low 64 bits = 1
    check("MUL -1 * -1",
      MulDivOp.MUL,
      mask64, mask64, 1)
  }

  behavior of "MulDiv MULH"

  it should "produce upper bits of signed*signed product" in {
    // (-1) * (-1) = 1, upper 64 = 0
    check("MULH -1 * -1", MulDivOp.MULH, mask64, mask64, 0)
  }

  it should "produce -1 in upper bits when one operand is -1 and other is positive" in {
    // (-1) * 2 = -2, full 128b = 0xFFFF...FFFFFFFE, upper 64 = 0xFFFF...FFFF
    check("MULH -1 * 2", MulDivOp.MULH, mask64, 2, mask64)
  }

  behavior of "MulDiv MULHU"

  it should "produce upper bits of unsigned*unsigned product" in {
    // 0xFFFFFFFFFFFFFFFF * 0xFFFFFFFFFFFFFFFF (unsigned)
    //   = 0xFFFFFFFFFFFFFFFE_0000000000000001
    check("MULHU max*max",
      MulDivOp.MULHU,
      mask64, mask64,
      mask64 - 1)
  }

  behavior of "MulDiv MULHSU"

  it should "treat rs1 as signed and rs2 as unsigned" in {
    // (-1 signed) * (0xFFFFFFFFFFFFFFFF unsigned)
    //   signed -1 * unsigned 2^64-1 = -(2^64 - 1)
    //   as 128-bit two's complement: 0xFFFF...FFFF_00000001
    //   upper 64 = 0xFFFFFFFFFFFFFFFF
    check("MULHSU -1 * max",
      MulDivOp.MULHSU,
      mask64, mask64, mask64)
  }

  // ==========================================================================
  // 64-bit DIV family
  // ==========================================================================

  behavior of "MulDiv DIV"

  it should "divide signed values" in {
    check("DIV 20 / 3", MulDivOp.DIV, 20, 3, 6)
  }

  it should "round toward zero for negative results" in {
    // -20 / 3 = -6 (truncated, not floored)
    val neg20 = mask64 - 19  // two's complement of -20
    val neg6 = mask64 - 5
    check("DIV -20 / 3", MulDivOp.DIV, neg20, 3, neg6)
  }

  it should "return all-ones on divide by zero" in {
    check("DIV x / 0", MulDivOp.DIV, 42, 0, mask64)
  }

  it should "return dividend on signed overflow" in {
    // INT64_MIN / -1 should return INT64_MIN
    val intMin = BigInt(1) << 63
    check("DIV INT64_MIN / -1", MulDivOp.DIV, intMin, mask64, intMin)
  }

  behavior of "MulDiv DIVU"

  it should "divide unsigned values" in {
    check("DIVU 20 / 3", MulDivOp.DIVU, 20, 3, 6)
  }

  it should "treat all bits as unsigned" in {
    // 0xFFFFFFFFFFFFFFFF / 2 = 0x7FFFFFFFFFFFFFFF
    check("DIVU max / 2", MulDivOp.DIVU, mask64, 2, mask64 >> 1)
  }

  it should "return all-ones on divide by zero" in {
    check("DIVU x / 0", MulDivOp.DIVU, 42, 0, mask64)
  }

  behavior of "MulDiv REM"

  it should "compute signed remainder" in {
    check("REM 20 % 3", MulDivOp.REM, 20, 3, 2)
  }

  it should "preserve sign of dividend" in {
    // -20 % 3 = -2 in C/RISC-V semantics
    val neg20 = mask64 - 19
    val neg2 = mask64 - 1
    check("REM -20 % 3", MulDivOp.REM, neg20, 3, neg2)
  }

  it should "return dividend on divide by zero" in {
    check("REM x % 0", MulDivOp.REM, 42, 0, 42)
  }

  it should "return zero on signed overflow" in {
    val intMin = BigInt(1) << 63
    check("REM INT64_MIN % -1", MulDivOp.REM, intMin, mask64, 0)
  }

  behavior of "MulDiv REMU"

  it should "compute unsigned remainder" in {
    check("REMU 20 % 3", MulDivOp.REMU, 20, 3, 2)
  }

  it should "return dividend on divide by zero" in {
    check("REMU x % 0", MulDivOp.REMU, 42, 0, 42)
  }

  // ==========================================================================
  // 32-bit W family - all must sign-extend bit 31 to bit 63
  // ==========================================================================

  behavior of "MulDiv MULW"

  it should "multiply low 32 bits and sign-extend" in {
    check("MULW 6 * 7", MulDivOp.MULW, 6, 7, 42)
  }

  it should "ignore upper 32 bits of operands" in {
    // (0x1_00000005) * (0x1_00000003) -- W ops use only low 32
    // 5 * 3 = 15, sign-extended = 15
    check("MULW ignore upper",
      MulDivOp.MULW,
      BigInt("100000005", 16),
      BigInt("100000003", 16),
      15)
  }

  it should "sign-extend negative 32-bit results" in {
    // 0x7FFFFFFF * 2 = 0xFFFFFFFE (32b), sign-extended = 0xFFFFFFFF_FFFFFFFE
    check("MULW overflow into sign",
      MulDivOp.MULW,
      BigInt("7FFFFFFF", 16), 2,
      sext32to64(BigInt("FFFFFFFE", 16)))
  }

  behavior of "MulDiv DIVW"

  it should "divide low 32 bits as signed and sign-extend" in {
    check("DIVW 20 / 3", MulDivOp.DIVW, 20, 3, 6)
  }

  it should "handle negative 32-bit dividends" in {
    // -20 / 3 = -6, as 32b = 0xFFFFFFFA, sign-extended
    check("DIVW -20 / 3",
      MulDivOp.DIVW,
      sext32to64(BigInt("FFFFFFEC", 16)), 3,
      sext32to64(BigInt("FFFFFFFA", 16)))
  }

  it should "return all-ones (sign-extended) on divide by zero" in {
    check("DIVW x / 0",
      MulDivOp.DIVW, 42, 0,
      sext32to64(BigInt("FFFFFFFF", 16)))
  }

  it should "return INT32_MIN on signed overflow" in {
    // 0x80000000 / 0xFFFFFFFF -> 0x80000000, sign-extended
    check("DIVW INT32_MIN / -1",
      MulDivOp.DIVW,
      sext32to64(BigInt("80000000", 16)),
      sext32to64(BigInt("FFFFFFFF", 16)),
      sext32to64(BigInt("80000000", 16)))
  }

  behavior of "MulDiv DIVUW"

  it should "divide low 32 bits as unsigned and sign-extend" in {
    check("DIVUW 20 / 3", MulDivOp.DIVUW, 20, 3, 6)
  }

  it should "treat 0xFFFFFFFF as 4294967295 unsigned" in {
    // 0xFFFFFFFF / 2 = 0x7FFFFFFF
    check("DIVUW max32 / 2",
      MulDivOp.DIVUW,
      BigInt("FFFFFFFF", 16), 2,
      BigInt("7FFFFFFF", 16))
  }

  it should "return all-ones on divide by zero" in {
    check("DIVUW x / 0",
      MulDivOp.DIVUW, 42, 0,
      sext32to64(BigInt("FFFFFFFF", 16)))
  }

  behavior of "MulDiv REMW"

  it should "compute signed 32-bit remainder and sign-extend" in {
    check("REMW 20 % 3", MulDivOp.REMW, 20, 3, 2)
  }

  it should "return sign-extended dividend on divide by zero" in {
    // dividend low 32 = 0xFFFFFFEC, sign-extended
    val dividend = sext32to64(BigInt("FFFFFFEC", 16))
    check("REMW -20 % 0", MulDivOp.REMW, dividend, 0, dividend)
  }

  it should "return zero on signed overflow" in {
    check("REMW INT32_MIN % -1",
      MulDivOp.REMW,
      sext32to64(BigInt("80000000", 16)),
      sext32to64(BigInt("FFFFFFFF", 16)),
      0)
  }

  behavior of "MulDiv REMUW"

  it should "compute unsigned 32-bit remainder and sign-extend" in {
    check("REMUW 20 % 3", MulDivOp.REMUW, 20, 3, 2)
  }

  it should "return sign-extended dividend on divide by zero" in {
    val dividend = sext32to64(BigInt("FFFFFFEC", 16))
    check("REMUW x % 0", MulDivOp.REMUW, dividend, 0, dividend)
  }
}