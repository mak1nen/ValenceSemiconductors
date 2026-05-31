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
  // ---------------------------------------------------------------------------

  csr.io.addr := Mux(
    id_ex.io.out.isCsr,
    id_ex.io.out.csrAddr,
    0.U(12.W)
  )

  val csrOld = csr.io.rdata

  val csrUimmXlen =
    Cat(0.U((p.xlen - 5).W), id_ex.io.out.csrUimm)

  val csrSrc = Mux(
    id_ex.io.out.csrOp(2),
    csrUimmXlen,
    id_ex.io.out.rs1_val
  )

  val csrWriteData = MuxLookup(
    id_ex.io.out.csrOp,
    csrOld
  )(Seq(
    "b001".U -> csrSrc,
    "b010".U -> (csrOld | csrSrc),
    "b011".U -> (csrOld & ~csrSrc),
    "b101".U -> csrSrc,
    "b110".U -> (csrOld | csrSrc),
    "b111".U -> (csrOld & ~csrSrc)
  ))

  val csrIsWriteType =
    id_ex.io.out.csrOp === "b001".U ||
    id_ex.io.out.csrOp === "b101".U

  val csrIsSetClearType =
    id_ex.io.out.csrOp === "b010".U ||
    id_ex.io.out.csrOp === "b011".U ||
    id_ex.io.out.csrOp === "b110".U ||
    id_ex.io.out.csrOp === "b111".U

  val csrSrcNonZero =
    csrSrc =/= 0.U

  // ---------------------------------------------------------------------------
  // Trap / interrupt resolution (EX stage)
  //
  // For this milestone traps resolve in EX, where id_ex.pc gives us mepc and
  // the existing branch-redirect path can carry the vector to the frontend.
  // Load/store/page-fault traps that are only known in MEM come later, when
  // EX/MEM gains pc + exception fields alongside the MMU work.
  // ---------------------------------------------------------------------------

  // Synchronous exceptions visible in EX.
  val excSync =
    id_ex.io.out.valid &&
    (id_ex.io.out.isEcall || id_ex.io.out.isEbreak || id_ex.io.out.illegal)

  // Asynchronous interrupt: globally enabled, pending & enabled, and there is a
  // real instruction in EX to pin mepc to. Sync exceptions take priority.
  val globalIE   = csr.io.mstatus(CSRFile.MSTATUS_MIE_BIT)
  val irqPending = (csr.io.mip & csr.io.mie) =/= 0.U
  val takeIrq    = globalIE && irqPending && id_ex.io.out.valid && !excSync

  val mretReq    = id_ex.io.out.valid && id_ex.io.out.isMret

  // ---------------------------------------------------------------------------
  // CSR software write enable
  //
  // Suppressed when this EX instruction is an interrupt victim — it will be
  // re-executed after the handler returns, so its CSR side effect must not
  // commit now.
  // ---------------------------------------------------------------------------

  val csrWriteEnable =
    id_ex.io.out.valid &&
    id_ex.io.out.isCsr &&
    (csrIsWriteType ||
    (csrIsSetClearType && csrSrcNonZero)) &&
    !takeIrq

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
  hazard.io.ex_is_load := id_ex.io.out.valid && (id_ex.io.out.isLoad || id_ex.io.out.isLR || id_ex.io.out.isAmo)

  hazard.io.mem_rd      := ex_mem.io.out.rd
  hazard.io.mem_wen     := ex_mem.io.out.valid
  hazard.io.mem_is_load := ex_mem.io.out.isLoad && ex_mem.io.out.valid

  hazard.io.branch_taken := execute.io.out.branch_taken

  val mem_stall = io.dcache_stall

  // Atomic serialization — hold IF/ID while atomic is in EX or MEM stage.
  // The atomic itself flows forward freely; only new instructions are blocked.
  val atomic_in_flight =
    id_ex.io.out.isLR || id_ex.io.out.isSC || id_ex.io.out.isAmo

  val pipe_stall =
    hazard.io.stall ||
    mem_stall

  // ---------------------------------------------------------------------------
  // Frontend
  //
  // Single redirect driver: a trap redirect overrides a branch redirect.
  // ---------------------------------------------------------------------------

  frontend.io.stall        := pipe_stall
  frontend.io.flush        := hazard.io.flush
  frontend.io.redirect     := execute.io.out.branch_taken || trap.io.redirect
  frontend.io.target       := Mux(
                                trap.io.redirect,
                                trap.io.redirectPc,
                                execute.io.out.branch_target
                              )
  frontend.io.instr        := io.icache_data
  frontend.io.icache_stall := io.icache_stall

  io.icache_addr := frontend.io.pc
  io.icache_req  := frontend.io.req

  // ---------------------------------------------------------------------------
  // IF/ID register
  // ---------------------------------------------------------------------------

  if_id.io.stall    := pipe_stall
  if_id.io.flush    := hazard.io.flush || trap.io.redirect

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
  forward.io.ex_wen := id_ex.io.out.valid ||
                       id_ex.io.out.isJal ||
                       id_ex.io.out.isJalr

  forward.io.mem_rd  := ex_mem.io.out.rd
  forward.io.mem_wen := ex_mem.io.out.valid

  forward.io.wb_rd  := mem_wb.io.out.rd
  forward.io.wb_wen := mem_wb.io.out.valid

  val fwd_rs1 = MuxLookup(
    forward.io.fwd_a,
    regfile.io.rdata1
  )(Seq(
    ForwardingUnit.FWD_EX.U  -> exStageResult,
    ForwardingUnit.FWD_MEM.U -> memory.io.out.result,
    ForwardingUnit.FWD_WB.U  -> mem_wb.io.out.result
  ))

  val fwd_rs2 = MuxLookup(
    forward.io.fwd_b,
    regfile.io.rdata2
  )(Seq(
    ForwardingUnit.FWD_EX.U  -> exStageResult,
    ForwardingUnit.FWD_MEM.U -> memory.io.out.result,
    ForwardingUnit.FWD_WB.U  -> mem_wb.io.out.result
  ))

  // ---------------------------------------------------------------------------
  // ID/EX register
  //
  // Flush when a trap redirect fires, so the instruction(s) already in flight
  // behind the trapping one are squashed (they belong to the wrong path).
  // ---------------------------------------------------------------------------

  id_ex.io.stall := mem_stall
  id_ex.io.flush := hazard.io.stall || hazard.io.flush || trap.io.redirect

  id_ex.io.in.pc       := if_id.io.out.pc
  id_ex.io.in.rs1_val  := fwd_rs1
  id_ex.io.in.rs2_val  := fwd_rs2
  id_ex.io.in.imm      := decode.io.out.imm
  id_ex.io.in.rd       := decode.io.out.rd
  id_ex.io.in.aluOp    := decode.io.out.aluOp
  id_ex.io.in.mulDivOp := decode.io.out.mulDivOp
  id_ex.io.in.brOp     := decode.io.out.brOp
  id_ex.io.in.memOp    := decode.io.out.memOp
  id_ex.io.in.csrAddr  := decode.io.out.csrAddr
  id_ex.io.in.csrOp    := decode.io.out.csrOp
  id_ex.io.in.csrUimm  := decode.io.out.csrUimm
  id_ex.io.in.isLR     := decode.io.out.isLR
  id_ex.io.in.isSC     := decode.io.out.isSC
  id_ex.io.in.isAmo    := decode.io.out.isAmo
  id_ex.io.in.amoOp    := decode.io.out.amoOp
  id_ex.io.in.aq       := decode.io.out.aq
  id_ex.io.in.rl       := decode.io.out.rl
  id_ex.io.in.useImm   := decode.io.out.useImm
  id_ex.io.in.isLoad   := decode.io.out.isLoad
  id_ex.io.in.isStore  := decode.io.out.isStore
  id_ex.io.in.isBranch := decode.io.out.isBranch
  id_ex.io.in.isJal    := decode.io.out.isJal
  id_ex.io.in.isJalr   := decode.io.out.isJalr
  id_ex.io.in.isLui    := decode.io.out.isLui
  id_ex.io.in.isAuipc  := decode.io.out.isAuipc
  id_ex.io.in.isCsr    := decode.io.out.isCsr
  id_ex.io.in.isMulDiv := decode.io.out.isMulDiv

  // System / privileged instructions (require matching DecodeOut fields).
  id_ex.io.in.isEcall  := decode.io.out.isEcall
  id_ex.io.in.isEbreak := decode.io.out.isEbreak
  id_ex.io.in.isMret   := decode.io.out.isMret
  id_ex.io.in.isWfi    := decode.io.out.isWfi
  id_ex.io.in.illegal  := decode.io.out.illegal

  id_ex.io.in.valid    := if_id.io.out.valid && !hazard.io.stall

  // ---------------------------------------------------------------------------
  // Execute
  // ---------------------------------------------------------------------------

  execute.io.in := id_ex.io.out

  // ---------------------------------------------------------------------------
  // EX/MEM register
  //
  // valid is suppressed for an interrupt victim so it does not commit a
  // load/store/AMO that will be re-run after the handler.
  // ---------------------------------------------------------------------------

  ex_mem.io.stall := mem_stall
  ex_mem.io.flush := false.B

  ex_mem.io.in.result  := exStageResult
  ex_mem.io.in.rd      := Mux(id_ex.io.out.isCsr, id_ex.io.out.rd, execute.io.out.rd)
  ex_mem.io.in.rs2_val := execute.io.out.rs2_val
  ex_mem.io.in.memOp   := execute.io.out.memOp
  ex_mem.io.in.isLoad  := execute.io.out.isLoad
  ex_mem.io.in.isStore := execute.io.out.isStore && execute.io.out.valid
  ex_mem.io.in.isLR    := execute.io.out.isLR
  ex_mem.io.in.isSC    := execute.io.out.isSC
  ex_mem.io.in.isAmo   := execute.io.out.isAmo
  ex_mem.io.in.amoOp   := execute.io.out.amoOp
  ex_mem.io.in.valid   := (
    execute.io.out.valid   ||
    id_ex.io.out.isJal     ||
    id_ex.io.out.isJalr    ||
    (id_ex.io.out.isCsr && id_ex.io.out.valid) ||
    id_ex.io.out.isLR      ||
    id_ex.io.out.isSC      ||
    id_ex.io.out.isAmo
  ) && !takeIrq

  // ---------------------------------------------------------------------------
  // Memory
  // ---------------------------------------------------------------------------

  memory.io.in.result  := ex_mem.io.out.result
  memory.io.in.rd      := ex_mem.io.out.rd
  memory.io.in.rs2_val := ex_mem.io.out.rs2_val
  memory.io.in.memOp   := ex_mem.io.out.memOp
  memory.io.in.isLoad  := ex_mem.io.out.isLoad
  memory.io.in.isStore := ex_mem.io.out.isStore
  memory.io.in.isLR    := ex_mem.io.out.isLR
  memory.io.in.isSC    := ex_mem.io.out.isSC
  memory.io.in.isAmo   := ex_mem.io.out.isAmo
  memory.io.in.amoOp   := ex_mem.io.out.amoOp
  memory.io.in.valid   := ex_mem.io.out.valid

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
  // Must stall in lockstep with MEM, or a load held in MEM by dcache_stall
  // latches into MEM/WB every cycle and writeback + retire fire repeatedly.
  // ---------------------------------------------------------------------------

  mem_wb.io.stall     := mem_stall
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
  // CSR file
  // ---------------------------------------------------------------------------

  csr.io.wen    := csrWriteEnable
  csr.io.wdata  := csrWriteData
  csr.io.retire := mem_wb.io.out.valid

  // Trap entry / mret — driven by TrapUnit, not hardwired.
  csr.io.takeTrap  := trap.io.takeTrap
  csr.io.trapEpc   := trap.io.trapEpc
  csr.io.trapCause := trap.io.trapCause
  csr.io.trapTval  := trap.io.trapTval
  csr.io.takeMret  := trap.io.takeMret

  csr.io.mtipIn    := io.timer_irq
  csr.io.msipIn    := io.soft_irq
  csr.io.meipIn    := false.B

  // ---------------------------------------------------------------------------
  // TrapUnit
  //
  // Inputs now carry the real EX-stage signals. Outputs (takeTrap / epc /
  // cause / tval / takeMret / redirect / target) are consumed above.
  // ---------------------------------------------------------------------------

  trap.io.pc                       := id_ex.io.out.pc
  trap.io.instr                    := 0.U(32.W)
  trap.io.illegalInstr             := id_ex.io.out.illegal && id_ex.io.out.valid
  trap.io.ecall                    := id_ex.io.out.isEcall && id_ex.io.out.valid
  trap.io.ebreak                   := id_ex.io.out.isEbreak && id_ex.io.out.valid
  trap.io.instrAddrMisaligned      := false.B
  trap.io.loadAddrMisaligned       := false.B
  trap.io.storeAddrMisaligned      := false.B
  trap.io.badAddr                  := 0.U(p.xlen.W)
  trap.io.mret                     := mretReq
  trap.io.mtvec                    := csr.io.mtvec
  trap.io.mepc                     := csr.io.mepc
  trap.io.mstatus                  := csr.io.mstatus
  trap.io.mie                      := csr.io.mie
  trap.io.machineSoftwareInterrupt := io.soft_irq
  trap.io.machineTimerInterrupt    := io.timer_irq
  trap.io.machineExternalInterrupt := false.B

  // ---------------------------------------------------------------------------
  // Temporary trap debug
  // ---------------------------------------------------------------------------

  when(excSync) {
    printf(p"[TRAP-sync] ")
    printf(p"pc=0x${Hexadecimal(id_ex.io.out.pc)} ")
    printf(p"ecall=${id_ex.io.out.isEcall} ")
    printf(p"ebreak=${id_ex.io.out.isEbreak} ")
    printf(p"illegal=${id_ex.io.out.illegal}\n")
  }

  when(takeIrq) {
    printf(p"[TRAP-irq] ")
    printf(p"pc=0x${Hexadecimal(id_ex.io.out.pc)} ")
    printf(p"mip=0x${Hexadecimal(csr.io.mip)} ")
    printf(p"mie=0x${Hexadecimal(csr.io.mie)} ")
    printf(p"mstatus=0x${Hexadecimal(csr.io.mstatus)}\n")
  }

  when(trap.io.takeTrap) {
    printf(p"[TRAP-enter] ")
    printf(p"cause=0x${Hexadecimal(trap.io.trapCause)} ")
    printf(p"epc=0x${Hexadecimal(trap.io.trapEpc)} ")
    printf(p"target=0x${Hexadecimal(trap.io.redirectPc)}\n")
  }

  when(trap.io.takeMret) {
    printf(p"[MRET] ")
    printf(p"mepc=0x${Hexadecimal(csr.io.mepc)}\n")
  }
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
  val mulDivOp = UInt(5.W)
  val brOp     = UInt(3.W)
  val memOp    = UInt(3.W)
  val csrAddr  = UInt(12.W)
  val csrOp    = UInt(3.W)
  val csrUimm  = UInt(5.W)
  val isLR     = Bool()
  val isSC     = Bool()
  val isAmo    = Bool()
  val amoOp    = UInt(5.W)
  val aq       = Bool()
  val rl       = Bool()
  val useImm   = Bool()
  val isLoad   = Bool()
  val isStore  = Bool()
  val isBranch = Bool()
  val isJal    = Bool()
  val isJalr   = Bool()
  val isLui    = Bool()
  val isAuipc  = Bool()
  val isCsr    = Bool()
  val isMulDiv = Bool()

  // System / privileged
  val isEcall  = Bool()
  val isEbreak = Bool()
  val isMret   = Bool()
  val isWfi    = Bool()
  val illegal  = Bool()

  val valid    = Bool()
}

class EXMEMReg extends Bundle {
  val result  = UInt(64.W)
  val rd      = UInt(5.W)
  val rs2_val = UInt(64.W)
  val memOp   = UInt(3.W)
  val isLoad  = Bool()
  val isStore = Bool()
  val isLR    = Bool()
  val isSC    = Bool()
  val isAmo   = Bool()
  val amoOp   = UInt(5.W)
  val valid   = Bool()
}

class MEMWBReg extends Bundle {
  val result = UInt(64.W)
  val rd     = UInt(5.W)
  val valid  = Bool()
}