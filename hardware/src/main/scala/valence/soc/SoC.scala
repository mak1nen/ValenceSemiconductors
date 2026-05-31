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

  val uart_write =
    core.io.dcache_valid &&
    core.io.dcache_wen &&
    uart_sel

  // Data path owns the shared DRAM port whenever it issues a DRAM access.
  // Declared up here so the fetch path can stall on it.
  val dram_data_req =
    core.io.dcache_valid &&
    dram_sel

  // -------------------------------------------------------------------------
  // ICache — fetch path, bypassed from BootROM, SRAM, or DRAM
  //
  // DRAM is a single shared port. When the data path owns the port, instruction
  // fetch must stall so the frontend does not consume data-path bytes as code.
  // -------------------------------------------------------------------------

  icache.io.req.valid := core.io.icache_req
  icache.io.req.addr  := core.io.icache_addr

  bootrom.io.addr := core.io.icache_addr
  bootrom.io.valid :=
    (core.io.icache_addr - MemoryMap.BOOTROM_BASE.U) < MemoryMap.BOOTROM_SIZE.U

  val sram_fetch_sel =
    (core.io.icache_addr - MemoryMap.SRAM_BASE.U) < MemoryMap.SRAM_SIZE.U

  val dram_fetch_sel =
    (core.io.icache_addr - MemoryMap.DRAM_BASE.U) < MemoryMap.DRAM_SIZE.U

  // Stall fetch while data owns external DRAM.
  core.io.icache_stall := dram_data_req

  sram.io.fetch_addr  := core.io.icache_addr
  sram.io.fetch_valid := sram_fetch_sel

  val sram_instr = Mux(
    core.io.icache_addr(2),
    sram.io.fetch_data(63, 32),
    sram.io.fetch_data(31, 0)
  )

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
  // DCache — load/store path
  // -------------------------------------------------------------------------

  dcache.io.req.valid := core.io.dcache_valid
  dcache.io.req.addr  := core.io.dcache_addr
  dcache.io.req.wen   := core.io.dcache_wen
  dcache.io.req.wdata := core.io.dcache_wdata

  dcache.io.mem.valid := sram.io.valid && !core.io.dcache_wen
  dcache.io.mem.data  := sram.io.rdata

  // -------------------------------------------------------------------------
  // UART read path
  //
  // OpenSBI ns16550a / uart8250 polls:
  //   UART_BASE + 5 = Line Status Register
  //
  // It waits for:
  //   bit 5 = THRE, transmit holding register empty
  //
  // We return:
  //   0x60 = THRE | TEMT
  //
  // Use 0x60 in every byte lane because the core load unit shifts by
  // address byte offset. This makes LB/LBU from UART_BASE+5 robust.
  // -------------------------------------------------------------------------

  val uart_offset = core.io.dcache_addr - MemoryMap.UART_BASE.U
  val uart_rdata  = WireDefault(0.U(64.W))

  when (uart_sel) {
    when (uart_offset(11, 0) === 5.U) {
      uart_rdata := "h6060606060606060".U(64.W)
    } .otherwise {
      uart_rdata := 0.U
    }
  }

  // UART writes may need to stall until the UART transmitter can accept a byte.
  // UART reads are always ready.
  core.io.dcache_stall := uart_write && !uart.io.tx_ready

  core.io.dcache_rdata := MuxCase(dcache.io.resp.rdata, Seq(
    sram_sel -> sram.io.rdata,
    dram_sel -> io.dram_rdata,
    uart_sel -> uart_rdata
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
  // DRAM port out
  // -------------------------------------------------------------------------

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