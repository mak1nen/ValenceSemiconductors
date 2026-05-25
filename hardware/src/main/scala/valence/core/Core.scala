package valence.core

import chisel3._
import chisel3.util._
import valence.pipeline._
import valence.privileged.CSRFile
import valence.params.CoreParams

class Core(p: CoreParams) extends Module {
  val io = IO(new Bundle {
    // ICache
    val icache_addr  = Output(UInt(64.W))
    val icache_req   = Output(Bool())
    val icache_data  = Input(UInt(32.W))
    val icache_stall = Input(Bool())

    // DCache
    val dcache_addr  = Output(UInt(64.W))
    val dcache_wen   = Output(Bool())
    val dcache_wdata = Output(UInt(64.W))
    val dcache_wstrb = Output(UInt(8.W))
    val dcache_valid = Output(Bool())
    val dcache_rdata = Input(UInt(64.W))
    val dcache_stall = Input(Bool())

    // interrupts
    val timer_irq = Input(Bool())
    val soft_irq  = Input(Bool())
  })

  // ---------------------------------------------------------------------------
  // Pipeline stages
  // ---------------------------------------------------------------------------
  val frontend  = Module(new Frontend)
  val decode    = Module(new Decode)
  val regfile   = Module(new RegFile(p.xlen))
  val execute   = Module(new Execute)
  val memory    = Module(new Memory)
  val writeback = Module(new Writeback)
  val hazard    = Module(new HazardUnit)
  val forward   = Module(new ForwardingUnit)
  val csr       = Module(new CSRFile(p.xlen))
  val trap      = Module(new TrapUnit(p.xlen))

  // ---------------------------------------------------------------------------
  // Pipeline registers
  // ---------------------------------------------------------------------------
  val if_id  = Module(new PipelineReg(new IFIDReg))
  val id_ex  = Module(new PipelineReg(new IDEXReg))
  val ex_mem = Module(new PipelineReg(new EXMEMReg))
  val mem_wb = Module(new PipelineReg(new MEMWBReg))

  // ---------------------------------------------------------------------------
  // CSR instruction support
  //
  // CSR funct3 encodings:
  //   001 CSRRW
  //   010 CSRRS
  //   011 CSRRC
  //   101 CSRRWI
  //   110 CSRRSI
  //   111 CSRRCI
  //
  // CSR instruction result to rd is always the old CSR value.
  // CSRFile only sees final write data.
  // ---------------------------------------------------------------------------

  csr.io.addr := Mux(id_ex.io.out.isCsr, id_ex.io.out.csrAddr, 0.U(12.W))

  val csrOld = csr.io.rdata

  val csrUimmXlen = Cat(0.U((p.xlen - 5).W), id_ex.io.out.csrUimm)

  val csrSrc = Mux(
    id_ex.io.out.csrOp(2),
    csrUimmXlen,
    id_ex.io.out.rs1_val
  )

  val csrWriteData = MuxLookup(id_ex.io.out.csrOp, csrOld)(Seq(
    "b001".U -> csrSrc,             // CSRRW
    "b010".U -> (csrOld | csrSrc),  // CSRRS
    "b011".U -> (csrOld & ~csrSrc), // CSRRC
    "b101".U -> csrSrc,             // CSRRWI
    "b110".U -> (csrOld | csrSrc),  // CSRRSI
    "b111".U -> (csrOld & ~csrSrc)  // CSRRCI
  ))

  val csrIsWriteType =
    id_ex.io.out.csrOp === "b001".U || // CSRRW
    id_ex.io.out.csrOp === "b101".U    // CSRRWI

  val csrIsSetClearType =
    id_ex.io.out.csrOp === "b010".U || // CSRRS
    id_ex.io.out.csrOp === "b011".U || // CSRRC
    id_ex.io.out.csrOp === "b110".U || // CSRRSI
    id_ex.io.out.csrOp === "b111".U    // CSRRCI

  val csrSrcNonZero = csrSrc =/= 0.U

  val csrWriteEnable =
    id_ex.io.out.valid &&
    id_ex.io.out.isCsr &&
    (csrIsWriteType || (csrIsSetClearType && csrSrcNonZero))

  val exStageResult = Mux(
    id_ex.io.out.isCsr,
    csrOld,
    execute.io.out.result
  )

  // ---------------------------------------------------------------------------
  // Hazard control
  // ---------------------------------------------------------------------------
  hazard.io.id_rs1 := decode.io.out.rs1
  hazard.io.id_rs2 := decode.io.out.rs2

  hazard.io.ex_rd      := id_ex.io.out.rd
  hazard.io.ex_is_load := id_ex.io.out.isLoad && id_ex.io.out.valid

  hazard.io.mem_rd      := ex_mem.io.out.rd
  hazard.io.mem_wen     := ex_mem.io.out.valid
  hazard.io.mem_is_load := ex_mem.io.out.isLoad && ex_mem.io.out.valid

  hazard.io.branch_taken := execute.io.out.branch_taken

  // Memory-stage backpressure.
  //
  // This is asserted by SoC.scala when, for example, software writes UART while
  // the UART transmitter is busy. The pending memory operation must remain held
  // in EX/MEM until the memory/peripheral accepts it.
  val mem_stall  = io.dcache_stall
  val pipe_stall = hazard.io.stall || mem_stall

  // ---------------------------------------------------------------------------
  // Frontend
  // ---------------------------------------------------------------------------
  frontend.io.stall        := pipe_stall
  frontend.io.flush        := hazard.io.flush
  frontend.io.redirect     := execute.io.out.branch_taken
  frontend.io.target       := execute.io.out.branch_target
  frontend.io.instr        := io.icache_data
  frontend.io.icache_stall := io.icache_stall

  io.icache_addr := frontend.io.pc
  io.icache_req  := frontend.io.req

  // ---------------------------------------------------------------------------
  // IF/ID register
  // ---------------------------------------------------------------------------
  if_id.io.stall    := pipe_stall
  if_id.io.flush    := hazard.io.flush
  if_id.io.in.pc    := frontend.io.out_pc
  if_id.io.in.instr := frontend.io.out_instr
  if_id.io.in.valid := frontend.io.out_valid

  // ---------------------------------------------------------------------------
  // Decode
  // ---------------------------------------------------------------------------
  decode.io.instr := if_id.io.out.instr

  // ---------------------------------------------------------------------------
  // Register file read
  // ---------------------------------------------------------------------------
  regfile.io.raddr1 := decode.io.out.rs1
  regfile.io.raddr2 := decode.io.out.rs2

  // ---------------------------------------------------------------------------
  // Forwarding
  // ---------------------------------------------------------------------------
  forward.io.ex_rs1 := decode.io.out.rs1
  forward.io.ex_rs2 := decode.io.out.rs2

  forward.io.ex_rd  := id_ex.io.out.rd
  forward.io.ex_wen := id_ex.io.out.valid || id_ex.io.out.isJal || id_ex.io.out.isJalr

  forward.io.mem_rd  := ex_mem.io.out.rd
  forward.io.mem_wen := ex_mem.io.out.valid

  forward.io.wb_rd  := mem_wb.io.out.rd
  forward.io.wb_wen := mem_wb.io.out.valid

  val fwd_rs1 = MuxLookup(forward.io.fwd_a, regfile.io.rdata1)(Seq(
    ForwardingUnit.FWD_EX.U  -> exStageResult,
    ForwardingUnit.FWD_MEM.U -> memory.io.out.result,
    ForwardingUnit.FWD_WB.U  -> mem_wb.io.out.result
  ))

  val fwd_rs2 = MuxLookup(forward.io.fwd_b, regfile.io.rdata2)(Seq(
    ForwardingUnit.FWD_EX.U  -> exStageResult,
    ForwardingUnit.FWD_MEM.U -> memory.io.out.result,
    ForwardingUnit.FWD_WB.U  -> mem_wb.io.out.result
  ))

  // ---------------------------------------------------------------------------
  // ID/EX register
  //
  // On normal load-use hazard, insert a bubble.
  // On memory/peripheral stall, hold ID/EX so decode/execute do not run ahead.
  // ---------------------------------------------------------------------------
  id_ex.io.stall := mem_stall
  id_ex.io.flush := hazard.io.stall || hazard.io.flush

  id_ex.io.in.pc       := if_id.io.out.pc
  id_ex.io.in.rs1_val  := fwd_rs1
  id_ex.io.in.rs2_val  := fwd_rs2
  id_ex.io.in.imm      := decode.io.out.imm
  id_ex.io.in.rd       := decode.io.out.rd
  id_ex.io.in.aluOp    := decode.io.out.aluOp
  id_ex.io.in.brOp     := decode.io.out.brOp
  id_ex.io.in.memOp    := decode.io.out.memOp
  id_ex.io.in.csrAddr  := decode.io.out.csrAddr
  id_ex.io.in.csrOp    := decode.io.out.csrOp
  id_ex.io.in.csrUimm  := decode.io.out.csrUimm
  id_ex.io.in.useImm   := decode.io.out.useImm
  id_ex.io.in.isLoad   := decode.io.out.isLoad
  id_ex.io.in.isStore  := decode.io.out.isStore
  id_ex.io.in.isBranch := decode.io.out.isBranch
  id_ex.io.in.isJal    := decode.io.out.isJal
  id_ex.io.in.isJalr   := decode.io.out.isJalr
  id_ex.io.in.isLui    := decode.io.out.isLui
  id_ex.io.in.isAuipc  := decode.io.out.isAuipc
  id_ex.io.in.isCsr    := decode.io.out.isCsr
  id_ex.io.in.valid    := if_id.io.out.valid && !hazard.io.stall

  // ---------------------------------------------------------------------------
  // Execute
  // ---------------------------------------------------------------------------
  execute.io.in := id_ex.io.out

  // ---------------------------------------------------------------------------
  // EX/MEM register
  //
  // This is the critical fix for UART backpressure:
  // when dcache_stall is high, hold the memory-stage operation in EX/MEM.
  // Otherwise the UART store disappears before uart.tx_ready comes back.
  // ---------------------------------------------------------------------------
  ex_mem.io.stall := mem_stall
  ex_mem.io.flush := false.B

  // CSR read result is injected here. For CSR instructions, rd gets csrOld.
  ex_mem.io.in.result  := exStageResult
  ex_mem.io.in.rd      := Mux(id_ex.io.out.isCsr, id_ex.io.out.rd, execute.io.out.rd)
  ex_mem.io.in.rs2_val := execute.io.out.rs2_val
  ex_mem.io.in.memOp   := execute.io.out.memOp
  ex_mem.io.in.isLoad  := execute.io.out.isLoad
  ex_mem.io.in.isStore := execute.io.out.isStore && execute.io.out.valid

  // JAL/JALR produce a writeback result even though they redirect control flow.
  // CSR instructions also produce a writeback result.
  ex_mem.io.in.valid :=
    execute.io.out.valid ||
    id_ex.io.out.isJal ||
    id_ex.io.out.isJalr ||
    (id_ex.io.out.isCsr && id_ex.io.out.valid)

  // ---------------------------------------------------------------------------
  // Memory
  // ---------------------------------------------------------------------------
  memory.io.in           := ex_mem.io.out
  memory.io.dcache_rdata := io.dcache_rdata
  memory.io.dcache_stall := io.dcache_stall

  io.dcache_addr  := memory.io.dcache_addr
  io.dcache_wen   := memory.io.dcache_wen
  io.dcache_wdata := memory.io.dcache_wdata
  io.dcache_wstrb := memory.io.dcache_wstrb
  io.dcache_valid := memory.io.dcache_valid

  // ---------------------------------------------------------------------------
  // MEM/WB register
  //
  // Let writeback drain even while the memory stage is stalled.
  // memory.io.out.valid is already suppressed during dcache_stall.
  // ---------------------------------------------------------------------------
  mem_wb.io.stall     := false.B
  mem_wb.io.flush     := false.B
  mem_wb.io.in.result := memory.io.out.result
  mem_wb.io.in.rd     := memory.io.out.rd
  mem_wb.io.in.valid  := memory.io.out.valid

  // ---------------------------------------------------------------------------
  // Writeback
  // ---------------------------------------------------------------------------
  writeback.io.in := mem_wb.io.out

  regfile.io.wen   := writeback.io.wen
  regfile.io.waddr := writeback.io.waddr
  regfile.io.wdata := writeback.io.wdata

  // ---------------------------------------------------------------------------
  // CSR + TrapUnit — Phase 0 stub plus CSR instruction support
  //
  // CSR instructions are now integrated enough for:
  //   CSRRW/CSRRS/CSRRC/CSRRWI/CSRRSI/CSRRCI
  //
  // Trap handling is still not integrated into the pipeline.
  // ---------------------------------------------------------------------------

  csr.io.wen   := csrWriteEnable
  csr.io.wdata := csrWriteData

  // Count retired instructions. This is approximate until precise commit/traps.
  csr.io.retire := mem_wb.io.out.valid

  csr.io.takeTrap  := false.B
  csr.io.trapEpc   := 0.U(p.xlen.W)
  csr.io.trapCause := 0.U(p.xlen.W)
  csr.io.trapTval  := 0.U(p.xlen.W)
  csr.io.takeMret  := false.B
  csr.io.mtipIn    := io.timer_irq
  csr.io.msipIn    := io.soft_irq
  csr.io.meipIn    := false.B

  trap.io.pc                       := 0.U(p.xlen.W)
  trap.io.instr                    := 0.U(32.W)
  trap.io.illegalInstr             := false.B
  trap.io.ecall                    := false.B
  trap.io.ebreak                   := false.B
  trap.io.instrAddrMisaligned      := false.B
  trap.io.loadAddrMisaligned       := false.B
  trap.io.storeAddrMisaligned      := false.B
  trap.io.badAddr                  := 0.U(p.xlen.W)
  trap.io.mret                     := false.B
  trap.io.mtvec                    := csr.io.mtvec
  trap.io.mepc                     := csr.io.mepc
  trap.io.mstatus                  := csr.io.mstatus
  trap.io.mie                      := csr.io.mie
  trap.io.machineSoftwareInterrupt := io.soft_irq
  trap.io.machineTimerInterrupt    := io.timer_irq
  trap.io.machineExternalInterrupt := false.B
}

// -----------------------------------------------------------------------------
// Pipeline register data types
// -----------------------------------------------------------------------------
class IFIDReg extends Bundle {
  val pc    = UInt(64.W)
  val instr = UInt(32.W)
  val valid = Bool()
}

class IDEXReg extends Bundle {
  val pc       = UInt(64.W)
  val rs1_val  = UInt(64.W)
  val rs2_val  = UInt(64.W)
  val imm      = UInt(64.W)
  val rd       = UInt(5.W)
  val aluOp    = UInt(5.W)
  val brOp     = UInt(3.W)
  val memOp    = UInt(3.W)

  val csrAddr  = UInt(12.W)
  val csrOp    = UInt(3.W)
  val csrUimm  = UInt(5.W)

  val useImm   = Bool()
  val isLoad   = Bool()
  val isStore  = Bool()
  val isBranch = Bool()
  val isJal    = Bool()
  val isJalr   = Bool()
  val isLui    = Bool()
  val isAuipc  = Bool()
  val isCsr    = Bool()
  val valid    = Bool()
}

class EXMEMReg extends Bundle {
  val result  = UInt(64.W)
  val rd      = UInt(5.W)
  val rs2_val = UInt(64.W)
  val memOp   = UInt(3.W)
  val isLoad  = Bool()
  val isStore = Bool()
  val valid   = Bool()
}

class MEMWBReg extends Bundle {
  val result = UInt(64.W)
  val rd     = UInt(5.W)
  val valid  = Bool()
}