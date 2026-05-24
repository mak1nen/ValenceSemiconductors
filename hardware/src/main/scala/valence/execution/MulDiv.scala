package valence.execution

import chisel3._
import chisel3.util._

object MulDivOp {
  val MUL    = 10
  val MULH   = 11
  val MULHSU = 12
  val MULHU  = 13
  val DIV    = 14
  val DIVU   = 15
  val REM    = 16
  val REMU   = 17
  val MULW   = 18
  val DIVW   = 19
  val DIVUW  = 20
  val REMW   = 21
  val REMUW  = 22
}

class MulDiv(xlen: Int) extends Module {
  require(xlen == 64, "MulDiv currently supports RV64 only")

  val io = IO(new Bundle {
    val op     = Input(UInt(5.W))
    val rs1    = Input(UInt(xlen.W))
    val rs2    = Input(UInt(xlen.W))
    val result = Output(UInt(xlen.W))
  })

  val rs1s = io.rs1.asSInt
  val rs2s = io.rs2.asSInt

  // --------------------------------------------------------------------------
  // 64-bit multiply products
  // --------------------------------------------------------------------------

  val mulSS = Wire(UInt((2 * xlen).W))
  val mulSU = Wire(UInt((2 * xlen).W))
  val mulUU = Wire(UInt((2 * xlen).W))

  val rs2AsPositiveSInt = Cat(0.U(1.W), io.rs2).asSInt

  mulSS := (rs1s * rs2s).asUInt
  mulSU := (rs1s * rs2AsPositiveSInt).asUInt
  mulUU := io.rs1 * io.rs2

  // --------------------------------------------------------------------------
  // 32-bit W operands
  // --------------------------------------------------------------------------

  val rs1wS = io.rs1(31, 0).asSInt
  val rs2wS = io.rs2(31, 0).asSInt

  val rs1wU = io.rs1(31, 0)
  val rs2wU = io.rs2(31, 0)

  // --------------------------------------------------------------------------
  // DIV/REM special cases
  // --------------------------------------------------------------------------

  val divByZero  = io.rs2 === 0.U
  val divwByZero = io.rs2(31, 0) === 0.U

  val divOverflow =
    io.rs1 === "h8000000000000000".U(64.W) &&
    io.rs2 === "hffffffffffffffff".U(64.W)

  val divwOverflow =
    io.rs1(31, 0) === "h80000000".U(32.W) &&
    io.rs2(31, 0) === "hffffffff".U(32.W)

  // --------------------------------------------------------------------------
  // 64-bit DIV/REM
  // --------------------------------------------------------------------------

  val divResult = Mux(
    divByZero,
    Fill(xlen, 1.U),
    Mux(
      divOverflow,
      io.rs1,
      (rs1s / rs2s).asUInt
    )
  )

  val divuResult = Mux(
    divByZero,
    Fill(xlen, 1.U),
    io.rs1 / io.rs2
  )

  val remResult = Mux(
    divByZero,
    io.rs1,
    Mux(
      divOverflow,
      0.U(xlen.W),
      (rs1s % rs2s).asUInt
    )
  )

  val remuResult = Mux(
    divByZero,
    io.rs1,
    io.rs1 % io.rs2
  )

  // --------------------------------------------------------------------------
  // RV64W MUL/DIV/REM
  // Results are sign-extended from bit 31.
  // --------------------------------------------------------------------------

  val mulw32 = Wire(UInt(32.W))
  mulw32 := (rs1wS * rs2wS).asUInt(31, 0)

  val mulwResult = mulw32.asSInt.pad(xlen).asUInt

  val divw32 = Mux(
    divwByZero,
    "hffffffff".U(32.W),
    Mux(
      divwOverflow,
      "h80000000".U(32.W),
      (rs1wS / rs2wS).asUInt(31, 0)
    )
  )

  val divwResult = divw32.asSInt.pad(xlen).asUInt

  val divuw32 = Mux(
    divwByZero,
    "hffffffff".U(32.W),
    rs1wU / rs2wU
  )

  val divuwResult = divuw32.asSInt.pad(xlen).asUInt

  val remw32 = Mux(
    divwByZero,
    rs1wU,
    Mux(
      divwOverflow,
      0.U(32.W),
      (rs1wS % rs2wS).asUInt(31, 0)
    )
  )

  val remwResult = remw32.asSInt.pad(xlen).asUInt

  val remuw32 = Mux(
    divwByZero,
    rs1wU,
    rs1wU % rs2wU
  )

  val remuwResult = remuw32.asSInt.pad(xlen).asUInt

  // --------------------------------------------------------------------------
  // Result mux
  // --------------------------------------------------------------------------

  io.result := MuxLookup(io.op, 0.U(xlen.W))(Seq(
    MulDivOp.MUL.U    -> mulSS(63, 0),
    MulDivOp.MULH.U   -> mulSS(127, 64),
    MulDivOp.MULHSU.U -> mulSU(127, 64),
    MulDivOp.MULHU.U  -> mulUU(127, 64),

    MulDivOp.DIV.U    -> divResult,
    MulDivOp.DIVU.U   -> divuResult,
    MulDivOp.REM.U    -> remResult,
    MulDivOp.REMU.U   -> remuResult,

    MulDivOp.MULW.U   -> mulwResult,
    MulDivOp.DIVW.U   -> divwResult,
    MulDivOp.DIVUW.U  -> divuwResult,
    MulDivOp.REMW.U   -> remwResult,
    MulDivOp.REMUW.U  -> remuwResult
  ))
}