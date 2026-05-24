int main(void) {

    volatile unsigned char buf[4] = {0x01, 0x02, 0x03, 0x04};


        if (buf[3]!= 0x04) {
            uart_puts("FAIL\r\n");
            return 1; }
        else {
            uart_puts("Success\r\n");
             return 0; }
    }
    
    // read values back
    // compare with expected values
    // print PASS or FAIL