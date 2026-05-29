// =============================================================================
// SoC.scala — Valence RISC-V top-level System on Chip
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

    // DRAM port — serviced by the Verilator testbench.
    // In future silicon this becomes an AXI4 memory controller port.
    val dram_addr  = Output(UInt(64.W))
    val dram_wen   = Output(Bool())
    val dram_wdata = Output(UInt(64.W))
    val dram_wstrb = Output(UInt(8.W))
    val dram_valid = Output(Bool())
    val dram_rdata = Input(UInt(64.W))
  })

  // -------------------------------------------------------------------------
  // Blocks
  // -------------------------------------------------------------------------
  val core    = Module(new Core(p))
  val icache  = Module(new ICache(
    nSets      = p.iCache.nSets,
    nWays      = p.iCache.nWays,
    blockBytes = p.iCache.blockBytes
  ))
  val dcache  = Module(new DCache(
    nSets      = p.dCache.nSets,
    nWays      = p.dCache.nWays,
    blockBytes = p.dCache.blockBytes
  ))
  val uart    = Module(new UART(50000000, 115200))
  val clint   = Module(new CLINT(p.nHarts))
  val bootrom = Module(new BootROM)
  val sram    = Module(new SRAM)

  // -------------------------------------------------------------------------
  // Address decode — data path
  // -------------------------------------------------------------------------
  val dram_sel =
    (core.io.dcache_addr - MemoryMap.DRAM_BASE.U) < MemoryMap.DRAM_SIZE.U

  val sram_sel =
    (core.io.dcache_addr - MemoryMap.SRAM_BASE.U) < MemoryMap.SRAM_SIZE.U

  val clint_sel =
    (core.io.dcache_addr - MemoryMap.CLINT_BASE.U) < MemoryMap.CLINT_SIZE.U

  val uart_sel =
    (core.io.dcache_addr - MemoryMap.UART_BASE.U) < MemoryMap.UART_SIZE.U

  val uart_write = core.io.dcache_valid && core.io.dcache_wen && uart_sel

  // -------------------------------------------------------------------------
  // ICache — fetch path (bypassed; instructions from BootROM or DRAM/SRAM)
  // -------------------------------------------------------------------------
  icache.io.req.valid  := core.io.icache_req
  icache.io.req.addr   := core.io.icache_addr
  core.io.icache_stall := false.B

  bootrom.io.addr  := core.io.icache_addr
  bootrom.io.valid :=
    (core.io.icache_addr - MemoryMap.BOOTROM_BASE.U) < MemoryMap.BOOTROM_SIZE.U

  val sram_fetch_sel =
    (core.io.icache_addr - MemoryMap.SRAM_BASE.U) < MemoryMap.SRAM_SIZE.U

  val dram_fetch_sel =
    (core.io.icache_addr - MemoryMap.DRAM_BASE.U) < MemoryMap.DRAM_SIZE.U

  sram.io.fetch_addr  := core.io.icache_addr
  sram.io.fetch_valid := sram_fetch_sel

  val sram_instr = Mux(
    core.io.icache_addr(2),
    sram.io.fetch_data(63, 32),
    sram.io.fetch_data(31, 0)
  )

  // DRAM instruction fetch: the testbench returns the 64-bit word; pick the
  // right 32-bit half.  dram_rdata is registered by the tb so we get valid
  // data one cycle after the address is presented — same as SRAM fetch.
  val dram_instr = Mux(
    core.io.icache_addr(2),
    io.dram_rdata(63, 32),
    io.dram_rdata(31, 0)
  )

  core.io.icache_data := MuxCase(0.U, Seq(
    bootrom.io.valid -> bootrom.io.data,
    sram_fetch_sel   -> sram_instr,
    dram_fetch_sel   -> dram_instr
  ))

  icache.io.mem.valid := false.B
  icache.io.mem.data  := 0.U

  // -------------------------------------------------------------------------
  // DCache — load/store path (pass-through to SRAM / DRAM / peripherals)
  // -------------------------------------------------------------------------
  dcache.io.req.valid := core.io.dcache_valid
  dcache.io.req.addr  := core.io.dcache_addr
  dcache.io.req.wen   := core.io.dcache_wen
  dcache.io.req.wdata := core.io.dcache_wdata

  dcache.io.mem.valid := sram.io.valid && !core.io.dcache_wen
  dcache.io.mem.data  := sram.io.rdata

  // Stall on UART backpressure only (DRAM in sim is zero-latency via tb).
  core.io.dcache_stall := uart_write && !uart.io.tx_ready

  // Read data mux: SRAM wins over DRAM; peripherals don't return read data
  // in the current minimal implementation.
  core.io.dcache_rdata := MuxCase(dcache.io.resp.rdata, Seq(
    sram_sel -> sram.io.rdata,
    dram_sel -> io.dram_rdata
  ))

  // -------------------------------------------------------------------------
  // SRAM data port
  // -------------------------------------------------------------------------
  sram.io.addr  := core.io.dcache_addr
  sram.io.wen   := core.io.dcache_wen && sram_sel
  sram.io.wdata := core.io.dcache_wdata
  sram.io.wstrb := core.io.dcache_wstrb
  sram.io.valid := core.io.dcache_valid && sram_sel

  // -------------------------------------------------------------------------
  // DRAM port (routed out to testbench / future AXI controller)
  //
  // The port carries both instruction-fetch and data-path accesses.
  // Fetch takes priority when the core is not doing a data access to DRAM.
  // In practice the 5-stage pipeline issues at most one memory request
  // per cycle, so a simple mux is safe.
  // -------------------------------------------------------------------------
  val dram_data_req = core.io.dcache_valid && dram_sel

  io.dram_addr  := Mux(dram_data_req, core.io.dcache_addr, core.io.icache_addr)
  io.dram_wen   := core.io.dcache_wen && dram_sel
  io.dram_wdata := core.io.dcache_wdata
  io.dram_wstrb := core.io.dcache_wstrb
  io.dram_valid := dram_data_req || dram_fetch_sel

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