package valence.core

import chisel3._
import chisel3.util._

class MemoryIn extends Bundle {
  val result  = UInt(64.W)  // effective address / ALU result
  val rd      = UInt(5.W)
  val rs2_val = UInt(64.W)
  val memOp   = UInt(3.W)   // funct3: width + signedness

  val isLoad  = Bool()
  val isStore = Bool()

  // RV64A atomics
  val isLR    = Bool()
  val isSC    = Bool()
  val isAmo   = Bool()
  val amoOp   = UInt(5.W)   // funct5

  val valid   = Bool()
}

class MemoryOut extends Bundle {
  val result = UInt(64.W)
  val rd     = UInt(5.W)
  val valid  = Bool()
}

class Memory extends Module {
  val io = IO(new Bundle {
    val in  = Input(new MemoryIn)
    val out = Output(new MemoryOut)

    val dcache_addr  = Output(UInt(64.W))
    val dcache_wen   = Output(Bool())
    val dcache_wdata = Output(UInt(64.W))
    val dcache_wstrb = Output(UInt(8.W))
    val dcache_valid = Output(Bool())

    val dcache_rdata = Input(UInt(64.W))
    val dcache_stall = Input(Bool())
  })

  // ───────────────────────────────────────────────────────────────────────────
  // Address and shift
  // ───────────────────────────────────────────────────────────────────────────

  val byteOffset = io.in.result(2, 0)
  val bitShift   = byteOffset << 3

  // ───────────────────────────────────────────────────────────────────────────
  // Alignment checks for atomics
  // ───────────────────────────────────────────────────────────────────────────

  val isWordAtomic  = io.in.memOp === "b010".U
  val isDwordAtomic = io.in.memOp === "b011".U

  val isAtomic =
    io.in.isLR ||
    io.in.isSC ||
    io.in.isAmo

  val misalignedAtomic =
    isAtomic &&
    (
      (isWordAtomic  && io.in.result(1, 0) =/= 0.U) ||
      (isDwordAtomic && io.in.result(2, 0) =/= 0.U)
    )

  // ───────────────────────────────────────────────────────────────────────────
  // Store byte mask
  // ───────────────────────────────────────────────────────────────────────────

  val storeMask = MuxLookup(io.in.memOp, 0.U(8.W))(Seq(
    "b000".U -> (1.U(8.W)     << byteOffset),  // SB
    "b001".U -> (3.U(8.W)     << byteOffset),  // SH
    "b010".U -> ("h0f".U(8.W) << byteOffset),  // SW
    "b011".U -> "hff".U(8.W)                   // SD
  ))

  // Atomic masks:
  // AMO/LR/SC.W use 4 bytes.
  // AMO/LR/SC.D use 8 bytes.
  val atomicMask = Mux(
    io.in.memOp === "b011".U,
    "hff".U(8.W),
    ("h0f".U(8.W) << byteOffset)
  )

  val shiftedStoreData =
    io.in.rs2_val << bitShift

  // ───────────────────────────────────────────────────────────────────────────
  // Load result
  // ───────────────────────────────────────────────────────────────────────────

  val shiftedLoad =
    io.dcache_rdata >> bitShift

  val loadResult = MuxLookup(io.in.memOp, io.dcache_rdata)(Seq(
    "b000".U -> Cat(Fill(56, shiftedLoad(7)),  shiftedLoad(7,  0)),  // LB
    "b001".U -> Cat(Fill(48, shiftedLoad(15)), shiftedLoad(15, 0)),  // LH
    "b010".U -> Cat(Fill(32, shiftedLoad(31)), shiftedLoad(31, 0)),  // LW
    "b011".U -> shiftedLoad,                                          // LD
    "b100".U -> Cat(0.U(56.W), shiftedLoad(7,  0)),                  // LBU
    "b101".U -> Cat(0.U(48.W), shiftedLoad(15, 0)),                  // LHU
    "b110".U -> Cat(0.U(32.W), shiftedLoad(31, 0))                   // LWU
  ))

  // ───────────────────────────────────────────────────────────────────────────
  // Reservation register for single-core LR/SC
  // ───────────────────────────────────────────────────────────────────────────

  val reservationValid = RegInit(false.B)
  val reservationAddr  = RegInit(0.U(64.W))

  // ───────────────────────────────────────────────────────────────────────────
  // AMO read-modify-write
  // ───────────────────────────────────────────────────────────────────────────
  //
  // funct5 encoding:
  //   00001 AMOSWAP
  //   00000 AMOADD
  //   00100 AMOXOR
  //   01100 AMOAND
  //   01000 AMOOR
  //   10000 AMOMIN
  //   10100 AMOMAX
  //   11000 AMOMINU
  //   11100 AMOMAXU

  val memVal = loadResult
  val rs2    = io.in.rs2_val

  val memValS = memVal.asSInt
  val rs2S    = rs2.asSInt

  val isWordOp =
    io.in.memOp === "b010".U

  val memWord = loadResult(31, 0)
  val rs2Word = rs2(31, 0)

  val memWordS = memWord.asSInt
  val rs2WordS = rs2Word.asSInt

  // 64-bit AMO result
  val amoResult64 = MuxLookup(io.in.amoOp, memVal)(Seq(
    "b00001".U -> rs2,                                      // AMOSWAP
    "b00000".U -> (memVal + rs2),                           // AMOADD
    "b00100".U -> (memVal ^ rs2),                           // AMOXOR
    "b01100".U -> (memVal & rs2),                           // AMOAND
    "b01000".U -> (memVal | rs2),                           // AMOOR
    "b10000".U -> Mux(memValS < rs2S, memVal, rs2).asUInt,  // AMOMIN
    "b10100".U -> Mux(memValS > rs2S, memVal, rs2).asUInt,  // AMOMAX
    "b11000".U -> Mux(memVal < rs2, memVal, rs2),           // AMOMINU
    "b11100".U -> Mux(memVal > rs2, memVal, rs2)            // AMOMAXU
  ))

  // 32-bit AMO result
  val amoResult32 = MuxLookup(io.in.amoOp, memWord)(Seq(
    "b00001".U -> rs2Word,                                          // AMOSWAP.W
    "b00000".U -> (memWord + rs2Word),                              // AMOADD.W
    "b00100".U -> (memWord ^ rs2Word),                              // AMOXOR.W
    "b01100".U -> (memWord & rs2Word),                              // AMOAND.W
    "b01000".U -> (memWord | rs2Word),                              // AMOOR.W
    "b10000".U -> Mux(memWordS < rs2WordS, memWord, rs2Word).asUInt, // AMOMIN.W
    "b10100".U -> Mux(memWordS > rs2WordS, memWord, rs2Word).asUInt, // AMOMAX.W
    "b11000".U -> Mux(memWord < rs2Word, memWord, rs2Word),          // AMOMINU.W
    "b11100".U -> Mux(memWord > rs2Word, memWord, rs2Word)           // AMOMAXU.W
  ))

  val finalAmoResult = Mux(
    isWordOp,
    Cat(Fill(32, amoResult32(31)), amoResult32),
    amoResult64
  )

  // ───────────────────────────────────────────────────────────────────────────
  // SC success condition
  // ───────────────────────────────────────────────────────────────────────────

  val scSuccess =
    reservationValid &&
    reservationAddr === io.in.result &&
    !misalignedAtomic

  // ───────────────────────────────────────────────────────────────────────────
  // Reservation update
  // ───────────────────────────────────────────────────────────────────────────

  when(io.in.isLR && io.in.valid && !io.dcache_stall) {
    reservationValid := true.B
    reservationAddr  := io.in.result

  }.elsewhen(io.in.isSC && io.in.valid && !io.dcache_stall) {
    // SC always clears the reservation after the attempt.
    reservationValid := false.B

  }.elsewhen(io.in.isStore &&
              !io.in.isSC &&
              io.in.valid &&
              !io.dcache_stall) {
    // Normal stores invalidate the reservation if they hit the reserved address.
    when(io.in.result === reservationAddr) {
      reservationValid := false.B
    }

  }.elsewhen(io.in.isAmo &&
              io.in.valid &&
              !io.dcache_stall) {
    // AMOs also invalidate the reservation if they hit the reserved address.
    when(io.in.result === reservationAddr) {
      reservationValid := false.B
    }
  }

  // ───────────────────────────────────────────────────────────────────────────
  // Memory bus signals
  // ───────────────────────────────────────────────────────────────────────────

  val doStore =
    io.in.isStore ||
    (io.in.isSC && scSuccess) ||
    io.in.isAmo

  val writeData = MuxCase(shiftedStoreData, Seq(
    io.in.isAmo -> (finalAmoResult << bitShift),
    io.in.isSC  -> shiftedStoreData
  ))

  // LR must NOT generate write strobes.
  val writeMask = MuxCase(storeMask, Seq(
    (io.in.isAmo || io.in.isSC) -> atomicMask
  ))

  val atomicValid =
    isAtomic &&
    !misalignedAtomic

  io.dcache_addr  := io.in.result
  io.dcache_wen   := doStore && !misalignedAtomic
  io.dcache_wdata := writeData
  io.dcache_wstrb := Mux(doStore && !misalignedAtomic, writeMask, 0.U(8.W))

  io.dcache_valid :=
    io.in.valid &&
    (
      io.in.isLoad  ||
      io.in.isStore ||
      atomicValid
    )


  // ───────────────────────────────────────────────────────────────────────────
  // Result to writeback
  // ───────────────────────────────────────────────────────────────────────────
  //
  // LR    -> loaded value
  // SC    -> 0 on success, 1 on failure
  // AMO   -> old memory value
  // Load  -> loaded value
  // Store -> address / ALU result

  io.out.result := MuxCase(io.in.result, Seq(
    io.in.isLoad -> loadResult,
    io.in.isLR   -> loadResult,
    io.in.isSC   -> Mux(scSuccess, 0.U(64.W), 1.U(64.W)),
    io.in.isAmo  -> memVal
  ))

  io.out.rd    := io.in.rd
  io.out.valid := io.in.valid && !io.dcache_stall
}