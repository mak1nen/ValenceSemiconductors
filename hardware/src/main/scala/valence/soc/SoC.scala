package valence.soc

import chisel3._
import chisel3.util._
import valence.core.Core
import valence.caches.{ICache, DCache}
import valence.peripherals.{UART, CLINT}
import valence.bus.AXI4Xbar
import valence.params.CoreParams

class SoC(p: CoreParams) extends Module {
  val io = IO(new Bundle {
    val uart_tx  = Output(Bool())
    val uart_rx  = Input(Bool())
  })

  // core
  val core  = Module(new Core(p))

  // caches
  val icache = Module(new ICache(
    nSets     = p.iCache.nSets,
    nWays     = p.iCache.nWays,
    blockBytes= p.iCache.blockBytes
  ))
  val dcache = Module(new DCache(
    nSets     = p.dCache.nSets,
    nWays     = p.dCache.nWays,
    blockBytes= p.dCache.blockBytes
  ))

  // peripherals
  val uart    = Module(new UART(50000000, 115200))
  val clint   = Module(new CLINT(p.nHarts))
  val bootrom = Module(new BootROM)
  val sram    = Module(new SRAM)

  // -------------------------------------------------------------------------
  // Address decode helpers
  // -------------------------------------------------------------------------
  val sram_sel = core.io.dcache_addr >= MemoryMap.SRAM_BASE.U &&
                 core.io.dcache_addr <  (MemoryMap.SRAM_BASE + MemoryMap.SRAM_SIZE).U

  val clint_sel = core.io.dcache_addr >= MemoryMap.CLINT_BASE.U &&
                  core.io.dcache_addr <  (MemoryMap.CLINT_BASE + MemoryMap.CLINT_SIZE).U

  val uart_sel = core.io.dcache_addr >= MemoryMap.UART_BASE.U &&
                 core.io.dcache_addr <  (MemoryMap.UART_BASE + MemoryMap.UART_SIZE).U

  // -------------------------------------------------------------------------
  // ICache — fetch path
  // -------------------------------------------------------------------------
  icache.io.req.valid := core.io.icache_req
  icache.io.req.addr  := core.io.icache_addr
  core.io.icache_data := icache.io.resp.data
  core.io.icache_stall:= icache.io.resp.stall

  bootrom.io.addr  := core.io.icache_addr
  bootrom.io.valid := core.io.icache_req &&
    core.io.icache_addr >= MemoryMap.BOOTROM_BASE.U &&
    core.io.icache_addr <  (MemoryMap.BOOTROM_BASE + MemoryMap.BOOTROM_SIZE).U

  icache.io.mem.valid := bootrom.io.valid
  icache.io.mem.data  := bootrom.io.data

  // -------------------------------------------------------------------------
  // DCache — load/store path
  // -------------------------------------------------------------------------
  dcache.io.req.valid := core.io.dcache_valid
  dcache.io.req.addr  := core.io.dcache_addr
  dcache.io.req.wen   := core.io.dcache_wen
  dcache.io.req.wdata := core.io.dcache_wdata
  core.io.dcache_stall:= dcache.io.resp.stall

  // DCache refill comes from SRAM
  dcache.io.mem.valid := sram.io.valid && !core.io.dcache_wen
  dcache.io.mem.data  := sram.io.rdata

  // Route rdata: SRAM for data region, DCache otherwise
  core.io.dcache_rdata := Mux(sram_sel, sram.io.rdata, dcache.io.resp.rdata)

  // -------------------------------------------------------------------------
  // SRAM
  // -------------------------------------------------------------------------
  sram.io.addr  := core.io.dcache_addr
  sram.io.wen   := core.io.dcache_wen && sram_sel
  sram.io.wdata := core.io.dcache_wdata
  sram.io.wstrb := 0xFF.U
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
  uart.io.tx_valid := core.io.dcache_valid && core.io.dcache_wen && uart_sel
  uart.io.rx       := io.uart_rx

  io.uart_tx := uart.io.tx
}