// Valence RISC-V — first software test
// Prints "Hello from Valence!" over UART

#define UART_BASE 0x10000000
#define UART_TX   (*(volatile unsigned char*)(UART_BASE))

static void uart_putc(char c) {
    UART_TX = c;
}

static void uart_puts(const char* s) {
    while (*s) uart_putc(*s++);
}

int main(void) {
    uart_puts("Hello from Valence!\r\n");
    uart_puts("RV64 core running.\r\n");
    uart_puts("DONE\r\n");
    return 0;
}