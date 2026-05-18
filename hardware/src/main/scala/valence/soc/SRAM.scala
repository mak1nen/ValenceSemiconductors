// =============================================================================
// SRAM.scala — Valence RISC-V dual-port on-chip SRAM
// =============================================================================
//
// File:    hardware/src/main/scala/valence/soc/SRAM.scala
// Package: valence.soc
//
// Summary:
//   64KB on-chip SRAM with two independent access ports. Used as the primary
//   program + stack memory during simulation and bare-metal boot. Will be
//   replaced by an external DRAM controller in v2.
// =============================================================================
package valence.soc

import chisel3._
import chisel3.util._

class SRAM(sizeBytes: Int = 65536) extends Module {
  val depth = sizeBytes / 8  // 64-bit words
  val idxWidth = log2Ceil(depth)

  val io = IO(new Bundle {
    // ── Port 0: data ───────────────────────────────────────────────────────
    val addr  = Input(UInt(64.W))
    val wen   = Input(Bool())
    val wdata = Input(UInt(64.W))
    val wstrb = Input(UInt(8.W))
    val valid = Input(Bool())
    val rdata = Output(UInt(64.W))

    // ── Port 1: fetch ──────────────────────────────────────────────────────
    val fetch_addr  = Input(UInt(64.W))
    val fetch_valid = Input(Bool())
    val fetch_data  = Output(UInt(64.W))
  })

  // Simulation-friendly SRAM:
  // - mem is used for data loads/stores
  // - fetch_mem mirrors mem for combinational instruction fetch
  //
  // Your Verilator loader should continue initializing BOTH memories:
  //   mem_ext.Memory
  //   fetch_mem_ext.Memory
  val mem       = Mem(depth, UInt(64.W))
  val fetch_mem = Mem(depth, UInt(64.W))

  // Convert byte address to 64-bit word index within SRAM.
  val offsetFull = (io.addr - MemoryMap.SRAM_BASE.U) >> 3
  val offset     = offsetFull(idxWidth - 1, 0)

  val fetchOffsetFull = (io.fetch_addr - MemoryMap.SRAM_BASE.U) >> 3
  val fetchOffset     = fetchOffsetFull(idxWidth - 1, 0)

  // ── Port 0: data ─────────────────────────────────────────────────────────
  val oldWord = mem.read(offset)

  val mergedBytes = Wire(Vec(8, UInt(8.W)))
  for (i <- 0 until 8) {
    val oldByte = oldWord(8 * i + 7, 8 * i)
    val newByte = io.wdata(8 * i + 7, 8 * i)
    mergedBytes(i) := Mux(io.wstrb(i), newByte, oldByte)
  }

  val mergedWord = mergedBytes.asUInt

  io.rdata := Mux(io.valid && !io.wen, oldWord, 0.U)

  when(io.valid && io.wen) {
    mem.write(offset, mergedWord)
    fetch_mem.write(offset, mergedWord)
  }

  // ── Port 1: fetch ────────────────────────────────────────────────────────
  io.fetch_data := Mux(io.fetch_valid, fetch_mem.read(fetchOffset), 0.U)
}