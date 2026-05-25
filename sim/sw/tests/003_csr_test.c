// Valence RISC-V — minimal CSR smoke test

#define UART_TX (*(volatile unsigned char*)0x10000000UL)

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

static inline unsigned long long read_mtvec(void) {
    unsigned long long v;
    asm volatile ("csrr %0, mtvec" : "=r"(v) :: "memory");
    return v;
}

static inline void write_mtvec(unsigned long long v) {
    asm volatile ("csrw mtvec, %0" :: "r"(v) : "memory");
}

static inline unsigned long long read_mscratch(void) {
    unsigned long long v;
    asm volatile ("csrr %0, mscratch" : "=r"(v) :: "memory");
    return v;
}

static inline void write_mscratch(unsigned long long v) {
    asm volatile ("csrw mscratch, %0" :: "r"(v) : "memory");
}

int main(void) {
    unsigned long long fails = 0;

    uart_puts("csr smoke start\r\n");

    unsigned long long mtvec_expected = 0x0000000020000100ULL;
    write_mtvec(mtvec_expected);

    unsigned long long mtvec_got = read_mtvec();

    uart_puts("mtvec got=0x");
    uart_puthex64(mtvec_got);
    uart_puts("\r\n");

    uart_puts("mtvec exp=0x");
    uart_puthex64(mtvec_expected);
    uart_puts("\r\n");

    if (mtvec_got != mtvec_expected) {
        fails++;
        uart_puts("mtvec FAIL\r\n");
    } else {
        uart_puts("mtvec PASS\r\n");
    }

    unsigned long long scratch_expected = 0x1122334455667788ULL;
    write_mscratch(scratch_expected);

    unsigned long long scratch_got = read_mscratch();

    uart_puts("scratch got=0x");
    uart_puthex64(scratch_got);
    uart_puts("\r\n");

    uart_puts("scratch exp=0x");
    uart_puthex64(scratch_expected);
    uart_puts("\r\n");

    if (scratch_got != scratch_expected) {
        fails++;
        uart_puts("scratch FAIL\r\n");
    } else {
        uart_puts("scratch PASS\r\n");
    }

    uart_puts("fails=0x");
    uart_puthex64(fails);
    uart_puts("\r\n");

    if (fails == 0) {
        uart_puts("CSR_SMOKE_PASS\r\n");
    } else {
        uart_puts("CSR_SMOKE_FAIL\r\n");
    }

    return 0;
}