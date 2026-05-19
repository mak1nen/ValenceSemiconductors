.section .text.start
.global _start

_start:
    # set up stack pointer
    la   sp, _stack_top

    # clear BSS
    la   t0, _bss_start
    la   t1, _bss_end
bss_loop:
    bgeu t0, t1, bss_done
    sd   zero, 0(t0)
    addi t0, t0, 8
    j    bss_loop
bss_done:

    # jump to C main
    call main

    # infinite loop if main returns
halt:
    j halt