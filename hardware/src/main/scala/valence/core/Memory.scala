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
  // Width / alignment checks
  // ───────────────────────────────────────────────────────────────────────────

  val isWordOp  = io.in.memOp === "b010".U
  val isDwordOp = io.in.memOp === "b011".U

  val isAtomic =
    io.in.isLR ||
    io.in.isSC ||
    io.in.isAmo

  val misalignedAtomic =
    isAtomic &&
    (
      (isWordOp  && io.in.result(1, 0) =/= 0.U) ||
      (isDwordOp && io.in.result(2, 0) =/= 0.U)
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
    isDwordOp,
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
    "b000".U -> Cat(Fill(56, shiftedLoad(7)),  shiftedLoad(7,  0)), // LB
    "b001".U -> Cat(Fill(48, shiftedLoad(15)), shiftedLoad(15, 0)), // LH
    "b010".U -> Cat(Fill(32, shiftedLoad(31)), shiftedLoad(31, 0)), // LW
    "b011".U -> shiftedLoad,                                        // LD
    "b100".U -> Cat(0.U(56.W), shiftedLoad(7,  0)),                 // LBU
    "b101".U -> Cat(0.U(48.W), shiftedLoad(15, 0)),                 // LHU
    "b110".U -> Cat(0.U(32.W), shiftedLoad(31, 0))                  // LWU
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
  //
  // Critical RISC-V rule:
  //   AMO rd gets the OLD memory value.
  //   Memory gets the NEW computed value.
  //
  // For .W AMOs on RV64:
  //   rd = sign_extend(old_mem_word)
  //   memory word = computed_new_word
  //
  // For .D AMOs:
  //   rd = old_mem_dword
  //   memory dword = computed_new_dword
  // ───────────────────────────────────────────────────────────────────────────

  val rs2 = io.in.rs2_val

  // Dword AMO operates on the raw 64-bit memory beat.
  // Dword atomics must be naturally aligned, so byteOffset should be zero.
  val oldDword = io.dcache_rdata
  val rs2Dword = rs2

  val oldDwordS = oldDword.asSInt
  val rs2DwordS = rs2Dword.asSInt

  val amoAddD = (oldDword + rs2Dword)(63, 0)

  val amoNewDword = MuxLookup(io.in.amoOp, oldDword)(Seq(
    "b00001".U -> rs2Dword,                                      // AMOSWAP.D
    "b00000".U -> amoAddD,                                       // AMOADD.D
    "b00100".U -> (oldDword ^ rs2Dword),                         // AMOXOR.D
    "b01100".U -> (oldDword & rs2Dword),                         // AMOAND.D
    "b01000".U -> (oldDword | rs2Dword),                         // AMOOR.D
    "b10000".U -> Mux(oldDwordS < rs2DwordS, oldDword, rs2Dword), // AMOMIN.D
    "b10100".U -> Mux(oldDwordS > rs2DwordS, oldDword, rs2Dword), // AMOMAX.D
    "b11000".U -> Mux(oldDword < rs2Dword, oldDword, rs2Dword),   // AMOMINU.D
    "b11100".U -> Mux(oldDword > rs2Dword, oldDword, rs2Dword)    // AMOMAXU.D
  ))

  // Word AMO operates on the selected 32-bit word from the 64-bit beat.
  // For addresses ending in ...0 use low word; for ...4 use high word.
  val oldWord = shiftedLoad(31, 0)
  val rs2Word = rs2(31, 0)

  val oldWordS = oldWord.asSInt
  val rs2WordS = rs2Word.asSInt

  val amoAddW = (oldWord + rs2Word)(31, 0)

  val amoNewWord = MuxLookup(io.in.amoOp, oldWord)(Seq(
    "b00001".U -> rs2Word,                                    // AMOSWAP.W
    "b00000".U -> amoAddW,                                    // AMOADD.W
    "b00100".U -> (oldWord ^ rs2Word),                        // AMOXOR.W
    "b01100".U -> (oldWord & rs2Word),                        // AMOAND.W
    "b01000".U -> (oldWord | rs2Word),                        // AMOOR.W
    "b10000".U -> Mux(oldWordS < rs2WordS, oldWord, rs2Word), // AMOMIN.W
    "b10100".U -> Mux(oldWordS > rs2WordS, oldWord, rs2Word), // AMOMAX.W
    "b11000".U -> Mux(oldWord < rs2Word, oldWord, rs2Word),   // AMOMINU.W
    "b11100".U -> Mux(oldWord > rs2Word, oldWord, rs2Word)    // AMOMAXU.W
  ))

  val amoReturnW =
    Cat(Fill(32, oldWord(31)), oldWord)

  val amoReturnD =
    oldDword

  val amoReturnValue =
    Mux(isWordOp, amoReturnW, amoReturnD)

  val amoWriteDataW =
    Cat(0.U(32.W), amoNewWord) << bitShift

  val amoWriteDataD =
    amoNewDword

  val amoWriteData =
    Mux(isWordOp, amoWriteDataW, amoWriteDataD)

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
    io.in.isAmo -> amoWriteData,
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
  // AMO   -> OLD memory value
  // Load  -> loaded value
  // Store -> address / ALU result
  // ───────────────────────────────────────────────────────────────────────────

  io.out.result := MuxCase(io.in.result, Seq(
    io.in.isLoad -> loadResult,
    io.in.isLR   -> loadResult,
    io.in.isSC   -> Mux(scSuccess, 0.U(64.W), 1.U(64.W)),
    io.in.isAmo  -> amoReturnValue
  ))

  io.out.rd    := io.in.rd
  io.out.valid := io.in.valid && !io.dcache_stall
}