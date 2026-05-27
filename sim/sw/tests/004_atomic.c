// Valence RISC-V — A extension test
// Tests LR.D / SC.D basic operation

#define UART_TX (*(volatile unsigned char*)0x10000000UL)

static void uart_putc(char c) { UART_TX = c; }
static void uart_puts(const char* s) { while (*s) uart_putc(*s++); }

static void uart_putu(unsigned long long v) {
    char buf[32]; int i = 0;
    if (v == 0) { uart_putc('0'); return; }
    while (v > 0) { buf[i++] = '0' + (v % 10); v /= 10; }
    while (i--) uart_putc(buf[i]);
}

int main(void) {
    volatile long lock = 0;
    long result;
    long tmp;

    uart_puts("atomic test\r\n");

    // test 1: LR.D / SC.D basic — should succeed
    asm volatile (
        "lr.d  %0, (%2)\n"
        "sc.d  %1, %3, (%2)\n"
        : "=&r"(tmp), "=&r"(result)
        : "r"(&lock), "r"(1L)
        : "memory"
    );

    uart_puts("sc result (expect 0)=");
    uart_putu(result);
    uart_puts("\r\n");

    uart_puts("lock val (expect 1)=");
    uart_putu(lock);
    uart_puts("\r\n");

    // test 2: SC.D without LR — should fail (result=1)
    asm volatile (
        "sc.d %0, %2, (%1)\n"
        : "=&r"(result)
        : "r"(&lock), "r"(99L)
        : "memory"
    );

    uart_puts("sc no lr (expect 1)=");
    uart_putu(result);
    uart_puts("\r\n");

    uart_puts("lock val (expect 1)=");
    uart_putu(lock);
    uart_puts("\r\n");

    uart_puts("DONE\r\n");
    return 0;
}
