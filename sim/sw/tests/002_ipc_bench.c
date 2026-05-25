// Valence RISC-V — simple known-instruction IPC benchmark
// Hex-only version: no divide/remainder in print path.

#define UART_TX (*(volatile unsigned char*)0x10000000UL)

#define N 10000ULL
#define INSNS_PER_ITER 8ULL
#define TOTAL_INSNS (N * INSNS_PER_ITER)

static void uart_putc(char c) {
    UART_TX = c;
}

static void uart_puts(const char* s) {
    while (*s) uart_putc(*s++);
}

static void uart_puthex64(unsigned long long v) {
    for (unsigned int pos = 0; pos < 16; pos++) {
        unsigned int shift = (15U - pos) * 4U;
        unsigned int nibble = (v >> shift) & 0xFULL;

        if (nibble < 10)
            uart_putc('0' + nibble);
        else
            uart_putc('a' + nibble - 10);
    }
}

static inline unsigned long long rdcycle(void) {
    unsigned long long v;
    asm volatile ("rdcycle %0" : "=r"(v));
    return v;
}

static inline unsigned long long rdinstret(void) {
    unsigned long long v;
    asm volatile ("rdinstret %0" : "=r"(v));
    return v;
}

int main(void) {
    register unsigned long long a asm("t0") = 1;
    register unsigned long long b asm("t1") = 2;
    register unsigned long long c asm("t2") = 3;
    register unsigned long long d asm("t3") = 4;
    register unsigned long long n asm("t4") = N;

    unsigned long long start_cycle = rdcycle();
    unsigned long long start_instret = rdinstret();

    asm volatile (
        "1:\n"
        "add  %[a], %[a], %[b]\n"
        "xor  %[b], %[b], %[c]\n"
        "srl  %[c], %[c], 1\n"
        "or   %[d], %[d], %[a]\n"
        "add  %[a], %[a], %[d]\n"
        "xor  %[b], %[b], %[a]\n"
        "addi %[n], %[n], -1\n"
        "bnez %[n], 1b\n"
        : [a] "+r"(a),
          [b] "+r"(b),
          [c] "+r"(c),
          [d] "+r"(d),
          [n] "+r"(n)
        :
        : "memory"
    );

    unsigned long long end_cycle = rdcycle();
    unsigned long long end_instret = rdinstret();

    unsigned long long cycles = end_cycle - start_cycle;
    unsigned long long instret = end_instret - start_instret;

    uart_puts("start_cycle=0x");
    uart_puthex64(start_cycle);
    uart_puts("\r\n");

    uart_puts("end_cycle=0x");
    uart_puthex64(end_cycle);
    uart_puts("\r\n");

    uart_puts("cycles=0x");
    uart_puthex64(cycles);
    uart_puts("\r\n");

    uart_puts("start_instret=0x");
    uart_puthex64(start_instret);
    uart_puts("\r\n");

    uart_puts("end_instret=0x");
    uart_puthex64(end_instret);
    uart_puts("\r\n");

    uart_puts("instret=0x");
    uart_puthex64(instret);
    uart_puts("\r\n");

    uart_puts("expected_insns=0x");
    uart_puthex64(TOTAL_INSNS);
    uart_puts("\r\n");

    // Prevent compiler from discarding results.
    if ((a ^ b ^ c ^ d) == 0x12345678ULL) {
        uart_puts("unlikely\r\n");
    }

    uart_puts("done\r\n");

    return 0;
}