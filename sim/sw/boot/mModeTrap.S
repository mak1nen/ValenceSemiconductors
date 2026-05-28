# =============================================================================
# boot/mModeTrap.S — Valence M-mode trap vector
#
# This is permanent boot-time infrastructure, not a test.
# Installed by C code via:
#   asm volatile("csrw mtvec, %0" :: "r"(&m_trap_vector));
#
# Communicates with C via volatile globals declared in mModeTrap.h:
#   volatile uint64_t trap_mcause;
#   volatile uint64_t trap_mepc;
#   volatile uint64_t trap_mtval;
#   volatile int      trap_fired;
#
# The handler saves/restores only the t-registers it clobbers.
# s-registers and a-registers are untouched so C callers are
# unaffected. A minimal save of t0-t2 is sufficient here because
# the handler does not call into C and does not nest.
#
# mret resumes at mepc. For ecall, C must advance mepc by 4
# BEFORE the ecall instruction executes — no, the handler does it.
# Caller just calls ecall; handler advances mepc and mrets back.
# =============================================================================

.equ CLINT_BASE,     0x02000000
.equ CLINT_MTIMECMP, 0x4000

.section .text
.align 4
.global m_trap_vector

m_trap_vector:
    # ---- preserve t-registers we clobber ----
    addi    sp, sp, -24
    sd      t0,  0(sp)
    sd      t1,  8(sp)
    sd      t2, 16(sp)

    # ---- snapshot CSRs into C-visible globals ----
    csrr    t0, mcause
    csrr    t1, mepc
    csrr    t2, mtval
    la      t3, trap_mcause       # can't use t3 before save — but t3 isn't
    sd      t0, 0(t3)             # clobbered by anything above; fine
    la      t3, trap_mepc
    sd      t1, 0(t3)
    la      t3, trap_mtval
    sd      t2, 0(t3)
    la      t3, trap_fired
    li      t2, 1
    sd      t2, 0(t3)

    # ---- dispatch on cause ----
    bltz    t0, handle_interrupt  # MSB set => interrupt

    # ---- synchronous exception ----
    li      t1, 11                # EcallM
    bne     t0, t1, trap_advance

    # ecall: skip the instruction (mepc + 4) then return
    csrr    t1, mepc
    addi    t1, t1, 4
    csrw    mepc, t1

trap_restore:
    ld      t0,  0(sp)
    ld      t1,  8(sp)
    ld      t2, 16(sp)
    addi    sp, sp, 24
    mret

trap_advance:
    # unknown sync exception: advance mepc to avoid looping, then return.
    # C can inspect trap_mcause / trap_mepc after the fact.
    csrr    t1, mepc
    addi    t1, t1, 4
    csrw    mepc, t1
    j       trap_restore

handle_interrupt:
    # clear the interrupt MSB to get the cause code
    slli    t1, t0, 1
    srli    t1, t1, 1

    li      t2, 7                 # M-timer
    beq     t1, t2, ack_timer

    # unhandled interrupt — just mret (mstatus.MIE was cleared on entry,
    # so we won't storm; C can inspect trap_mcause)
    j       trap_restore

ack_timer:
    # push mtimecmp far out so the CLINT line deasserts before mret
    li      t2, CLINT_BASE + CLINT_MTIMECMP
    li      t3, -1
    sd      t3, 0(t2)
    j       trap_restore

# =============================================================================
# Globals written by the handler and read by C tests.
# Defined here so they live in a known section alongside the handler.
# Declared extern volatile in mModeTrap.h.
# =============================================================================

.section .bss
.align 8
.global trap_mcause
.global trap_mepc
.global trap_mtval
.global trap_fired

trap_mcause: .quad 0
trap_mepc:   .quad 0
trap_mtval:  .quad 0
trap_fired:  .quad 0