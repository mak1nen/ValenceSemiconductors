// =============================================================================
// tests/005_trap.c — M-mode trap path bring-up test
//
// Subtest 1: synchronous ECALL
//   Install mtvec, fire ecall, verify handler ran and mepc was advanced.
//
// Subtest 2: M-mode timer interrupt via CLINT
//   Program mtimecmp = mtime + delta, enable mie.MTIE + mstatus.MIE,
//   spin until handler fires, verify cause.
//
// Pass/fail is left in a0 (via return value) for the testbench to read,
// and "PASS"/"FAIL" + "DONE" are emitted over UART to stop the sim.
// =============================================================================

#include <stdint.h>

// -----------------------------------------------------------------------------
// Trap handler globals — defined in boot/mModeTrap.S
// -----------------------------------------------------------------------------
extern volatile uint64_t trap_mcause;
extern volatile uint64_t trap_mepc;
extern volatile uint64_t trap_mtval;
extern volatile int      trap_fired;

// -----------------------------------------------------------------------------
// Trap vector entry symbol — defined in boot/mModeTrap.S
// -----------------------------------------------------------------------------
extern void m_trap_vector(void);

// -----------------------------------------------------------------------------
// Memory map
// -----------------------------------------------------------------------------
#define UART_BASE        0x10000000UL
#define CLINT_BASE       0x02000000UL

#define CLINT_MTIME      (CLINT_BASE + 0xBFF8UL)
#define CLINT_MTIMECMP0  (CLINT_BASE + 0x4000UL)

// -----------------------------------------------------------------------------
// UART
//
// Replace with your working UART implementation if needed.
// -----------------------------------------------------------------------------
#define UART_TX_REG     (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_STATUS_REG (*(volatile uint32_t *)(UART_BASE + 0x08))

#define UART_TX_READY   (1u << 0)

static void putc(char c) {
    UART_TX_REG = (uint32_t)c;
}

static void puts_uart(const char *s) {
    while (*s) {
        putc(*s++);
    }
}

// -----------------------------------------------------------------------------
// CSR helpers
// -----------------------------------------------------------------------------
#define csr_write(csr, val) \
    asm volatile("csrw " #csr ", %0" :: "r"((uint64_t)(val)))

#define csr_read(csr, dst) \
    asm volatile("csrr %0, " #csr : "=r"(dst))

#define csr_set(csr, bits) \
    asm volatile("csrs " #csr ", %0" :: "r"((uint64_t)(bits)))

#define csr_clear(csr, bits) \
    asm volatile("csrc " #csr ", %0" :: "r"((uint64_t)(bits)))

// -----------------------------------------------------------------------------
// CLINT MMIO
// -----------------------------------------------------------------------------
static inline uint64_t clint_mtime(void) {
    return *(volatile uint64_t *)CLINT_MTIME;
}

static inline void clint_set_mtimecmp(uint64_t val) {
    *(volatile uint64_t *)CLINT_MTIMECMP0 = val;
}

// -----------------------------------------------------------------------------
// Subtest bookkeeping
// -----------------------------------------------------------------------------
static int passed    = 0;
static int attempted = 0;

static void check(const char *name, int ok) {
    attempted++;

    if (ok) {
        passed++;
        puts_uart("  [PASS] ");
    } else {
        puts_uart("  [FAIL] ");
    }

    puts_uart(name);
    putc('\n');
}

// -----------------------------------------------------------------------------
// Reset trap state between subtests
// -----------------------------------------------------------------------------
static void clear_trap_state(void) {
    trap_mcause = 0;
    trap_mepc   = 0;
    trap_mtval  = 0;
    trap_fired  = 0;
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main(void) {

    // -------------------------------------------------------------------------
    // Install machine trap vector
    // mtvec low bits = 00 => direct mode
    // -------------------------------------------------------------------------
    csr_write(mtvec, (uint64_t)m_trap_vector);

    puts_uart("005_trap\n");

    // =========================================================================
    // Subtest 1 — synchronous ECALL from M-mode
    // =========================================================================

    clear_trap_state();

    uint64_t sentinel = 0xCAFEBABEUL;

    asm volatile("ecall");

    // execution resumes here after trap handler:
    //   mepc += 4
    //   mret

    check("ecall: handler fired",
          trap_fired == 1);

    check("ecall: mcause == 11",
          trap_mcause == 11);

    check("ecall: sentinel intact",
          sentinel == 0xCAFEBABEUL);

    // =========================================================================
    // Subtest 2 — M-mode timer interrupt
    // =========================================================================

    clear_trap_state();

    uint64_t now = clint_mtime();

    clint_set_mtimecmp(now + 50);

    // Enable MTIE
    csr_set(mie, (1UL << 7));

    // Enable global MIE
    csr_set(mstatus, (1UL << 3));

    // Spin until interrupt fires or timeout occurs
    for (uint64_t i = 0; i < 2000000UL && !trap_fired; i++) {
        asm volatile("nop");
    }

    // Disable MTIE after test
    csr_clear(mie, (1UL << 7));

    // Interrupt mcause:
    //   bit63 = interrupt
    //   low bits = 7 => machine timer interrupt
    uint64_t expected_timer =
        (1ULL << 63) | 7ULL;

    check("timer: handler fired",
          trap_fired == 1);

    check("timer: mcause == INT|7",
          trap_mcause == expected_timer);

    // =========================================================================
    // Final report
    // =========================================================================

    putc('\n');

    if (passed == attempted) {
        puts_uart("PASS\n");
    } else {
        puts_uart("FAIL\n");
    }

    puts_uart("DONE\n");

    // -------------------------------------------------------------------------
    // Return convention
    //
    // a0 = passed
    // a1 = attempted
    // -------------------------------------------------------------------------

    register uint64_t a1 asm("a1") = (uint64_t)attempted;

    asm volatile("" :: "r"(a1));

    return passed;
}