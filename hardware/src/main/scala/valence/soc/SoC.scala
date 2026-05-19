// =============================================================================
// SoC.scala — Valence RISC-V top-level System on Chip
// =============================================================================
//
// Wires together all hardware blocks into a complete SoC:
//
//   Core        — RV64I 5-stage pipeline, parameterized via CoreParams
//   ICache      — instruction cache (currently bypassed — TODO fix word-addressing)
//   DCache      — data cache, fills from SRAM
//   BootROM     — read-only trampoline, jumps to SRAM_BASE on reset
//   SRAM        — 64KB dual-port on-chip memory (data + fetch ports)
//   UART        — serial console, 115200 8N1, TX/RX
//   CLINT       — timer and software interrupts per hart
//
// Memory map (see MemoryMap.scala):
//   0x0000_1000  BootROM   4KB    read-only, baked into RTL
//   0x0200_0000  CLINT     64KB   timer + soft IRQ
//   0x1000_0000  UART      4KB    byte store = transmit
//   0x2000_0000  SRAM      64KB   program + stack (sim target)
//   0x8000_0000  DRAM      256MB  reserved, v2
//
// Boot sequence:
//   1. CPU resets → PC = BOOTROM_BASE (0x0000_1000)
//   2. BootROM sets a0=hart_id, a1=dtb_ptr, jumps to SRAM_BASE
//   3. _start (start.S) sets up stack, clears BSS, calls main()
//   4. main() stores bytes to UART_BASE → serial output
//
// Generated from: sbt "hardware/runMain valence.soc.SoCElaborate"
// =============================================================================
package valence.soc

import chisel3._
import chisel3.util._
import valence.core.Core
import valence.caches.{ICache, DCache}
import valence.peripherals.{UART, CLINT}
import valence.params.CoreParams

class SoC(p: CoreParams) extends Module {
  val io = IO(new Bundle {
    val uart_tx = Output(Bool())
    val uart_rx = Input(Bool())
  })

  // -------------------------------------------------------------------------
  // Blocks
  // -------------------------------------------------------------------------
  val core = Module(new Core(p))

  val icache = Module(new ICache(
    nSets      = p.iCache.nSets,
    nWays      = p.iCache.nWays,
    blockBytes = p.iCache.blockBytes
  ))

  val dcache = Module(new DCache(
    nSets      = p.dCache.nSets,
    nWays      = p.dCache.nWays,
    blockBytes = p.dCache.blockBytes
  ))

  val uart    = Module(new UART(50000000, 115200))
  val clint   = Module(new CLINT(p.nHarts))
  val bootrom = Module(new BootROM)
  val sram    = Module(new SRAM)

  // -------------------------------------------------------------------------
  // Address decode helpers — data path
  // -------------------------------------------------------------------------
  val sram_sel =
    core.io.dcache_addr >= MemoryMap.SRAM_BASE.U &&
    core.io.dcache_addr <  (MemoryMap.SRAM_BASE + MemoryMap.SRAM_SIZE).U

  val clint_sel =
    core.io.dcache_addr >= MemoryMap.CLINT_BASE.U &&
    core.io.dcache_addr <  (MemoryMap.CLINT_BASE + MemoryMap.CLINT_SIZE).U

  val uart_sel =
    core.io.dcache_addr >= MemoryMap.UART_BASE.U &&
    core.io.dcache_addr <  (MemoryMap.UART_BASE + MemoryMap.UART_SIZE).U

  // UART write request from CPU data path.
  // Declare this here so both DCache stall logic and UART wiring can use it.
  val uart_write = core.io.dcache_valid && core.io.dcache_wen && uart_sel

  // -------------------------------------------------------------------------
  // ICache — fetch path
  // Bypass ICache for now: feed instructions directly from BootROM/SRAM.
  // TODO: fix ICache to be word-addressed (store multiple words per line).
  // -------------------------------------------------------------------------
  icache.io.req.valid  := core.io.icache_req
  icache.io.req.addr   := core.io.icache_addr
  core.io.icache_stall := false.B

  bootrom.io.addr := core.io.icache_addr

  // Subtraction-based range check — prevents CIRCT from optimizing the comparison away.
  bootrom.io.valid :=
    (core.io.icache_addr - MemoryMap.BOOTROM_BASE.U) < MemoryMap.BOOTROM_SIZE.U

  val sram_fetch_sel =
    (core.io.icache_addr - MemoryMap.SRAM_BASE.U) < MemoryMap.SRAM_SIZE.U

  sram.io.fetch_addr  := core.io.icache_addr
  sram.io.fetch_valid := sram_fetch_sel

  // Select correct 32-bit instruction from 64-bit SRAM word.
  // addr[2] chooses low/high halfword of the 64-bit fetch word.
  val sram_instr = Mux(
    core.io.icache_addr(2),
    sram.io.fetch_data(63, 32),
    sram.io.fetch_data(31, 0)
  )

  core.io.icache_data := Mux(bootrom.io.valid, bootrom.io.data, sram_instr)

  // Keep ICache memory port wired even though fetch currently bypasses it.
  icache.io.mem.valid := false.B
  icache.io.mem.data  := 0.U

  // -------------------------------------------------------------------------
  // DCache — load/store path
  // -------------------------------------------------------------------------
  dcache.io.req.valid := core.io.dcache_valid
  dcache.io.req.addr  := core.io.dcache_addr
  dcache.io.req.wen   := core.io.dcache_wen
  dcache.io.req.wdata := core.io.dcache_wdata

  dcache.io.mem.valid := sram.io.valid && !core.io.dcache_wen
  dcache.io.mem.data  := sram.io.rdata

  // Stall CPU while writing UART if UART is busy.
  // Without this, software writes the next byte long before the UART frame
  // for the previous byte has finished, and bytes after the first are dropped.
  core.io.dcache_stall := uart_write && !uart.io.tx_ready

  // Route data readback.
  // SRAM loads bypass DCache response because SRAM is directly connected here.
  core.io.dcache_rdata := Mux(sram_sel, sram.io.rdata, dcache.io.resp.rdata)

  // -------------------------------------------------------------------------
  // SRAM data port
  // -------------------------------------------------------------------------
  sram.io.addr  := core.io.dcache_addr
  sram.io.wen   := core.io.dcache_wen && sram_sel
  sram.io.wdata := core.io.dcache_wdata
  sram.io.wstrb := core.io.dcache_wstrb
  sram.io.valid := core.io.dcache_valid && sram_sel

  // -------------------------------------------------------------------------
  // CLINT
  // -------------------------------------------------------------------------
  clint.io.addr  := core.io.dcache_addr
  clint.io.wen   := core.io.dcache_wen && clint_sel
  clint.io.wdata := core.io.dcache_wdata
  clint.io.valid := core.io.dcache_valid && clint_sel

  core.io.timer_irq := clint.io.timer_irq(0)
  core.io.soft_irq  := clint.io.soft_irq(0)

  // -------------------------------------------------------------------------
  // UART
  // -------------------------------------------------------------------------
  uart.io.tx_data  := core.io.dcache_wdata(7, 0)
  uart.io.tx_valid := uart_write && uart.io.tx_ready
  uart.io.rx       := io.uart_rx

  io.uart_tx := uart.io.tx
}