// Valence RISC-V — IPC benchmark

#define UART_TX (*(volatile unsigned char*)0x10000000UL)

#define N               10000ULL
#define INSNS_PER_ITER  4ULL

// ── UART ──────────────────────────────────────────────────────────────────────

static void uart_putc(char c) {
    UART_TX = c;
}

static void uart_puts(const char* s) {
    while (*s) uart_putc(*s++);
}

static void uart_putu(unsigned long long v) {
    char buf[32];
    int i = 0;

    if (v == 0) {
        uart_putc('0');
        return;
    }

    while (v > 0) {
        buf[i++] = '0' + (v % 10);
        v /= 10;
    }

    while (i--)
        uart_putc(buf[i]);
}

// print fixed-point x1000 value
static void uart_put_fixed3(unsigned long long v) {
    uart_putu(v / 1000);
    uart_putc('.');
    
    unsigned long long frac = v % 1000;

    uart_putc('0' + (frac / 100) % 10);
    uart_putc('0' + (frac / 10) % 10);
    uart_putc('0' + frac % 10);
}

// ── cycle counter ─────────────────────────────────────────────────────────────

static inline unsigned long long rdcycle(void) {
    unsigned long long v;
    asm volatile ("rdcycle %0" : "=r"(v));
    return v;
}

// ── benchmark ─────────────────────────────────────────────────────────────────

int main(void) {

    volatile unsigned long long a = 1;
    volatile unsigned long long b = 2;
    volatile unsigned long long c = 3;
    volatile unsigned long long d = 4;

    unsigned long long start = rdcycle();

    for (unsigned long long i = 0; i < N; i++) {

        a = a + b;   // add
        b = b ^ c;   // xor
        c = c >> 1;  // srl
        d = d | a;   // or
    }

    unsigned long long end = rdcycle();

    unsigned long long cycles = end - start;
    unsigned long long insns  = N * INSNS_PER_ITER;

    // IPC scaled by 1000
    unsigned long long ipc_x1000 = (insns * 1000ULL) / cycles;

    uart_puts("cycles=");
    uart_putu(cycles);
    uart_puts("\r\n");

    uart_puts("insns=");
    uart_putu(insns);
    uart_puts("\r\n");

    uart_puts("ipc=");
    uart_put_fixed3(ipc_x1000);
    uart_puts("\r\n");

    return 0;
}