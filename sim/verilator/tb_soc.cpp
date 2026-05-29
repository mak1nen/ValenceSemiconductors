// =============================================================================
// tb_soc.cpp — Verilator testbench for Valence RISC-V SoC
// =============================================================================

#include "VSoC.h"
#include "VSoC___024root.h"
#include "verilated.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Memory map — must match MemoryMap.scala and linker scripts
#define SRAM_BASE    0x20000000UL
#define SRAM_WORDS   8192           // 64KB / 8 bytes
#define DRAM_BASE    0x80000000UL
#define DRAM_WORDS   (64*1024*1024/8)  // 64MB / 8 bytes — enough for OpenSBI + kernel
#define UART_BASE    0x10000000UL

// ─── UART decoder ────────────────────────────────────────────────────────────

struct UartDecoder {
    int     baud_cycles;
    int     state;
    int     bit_count;
    int     sample_count;
    uint8_t shift;
    int     prev_tx;

    UartDecoder(int clk_hz, int baud)
        : baud_cycles(clk_hz / baud), state(0), bit_count(0),
          sample_count(0), shift(0), prev_tx(1) {}

    int tick(int tx) {
        int result = -1;
        switch (state) {
        case 0:
            if (prev_tx == 1 && tx == 0) { state = 1; sample_count = baud_cycles / 2; }
            break;
        case 1:
            if (--sample_count <= 0) { state = 2; bit_count = 0; shift = 0; sample_count = baud_cycles; }
            break;
        case 2:
            if (--sample_count <= 0) {
                shift |= (tx & 1) << bit_count;
                if (++bit_count == 8) state = 3;
                sample_count = baud_cycles;
            }
            break;
        case 3:
            if (--sample_count <= 0) { result = (int)(unsigned char)shift; state = 0; }
            break;
        }
        prev_tx = tx;
        return result;
    }
};

// ─── Hex loader ──────────────────────────────────────────────────────────────
//
// Supports two region targets: SRAM and DRAM.
// The @addr records in the hex file select which region receives bytes.

static void load_hex(const char* path,
                     uint64_t* sram, size_t sram_words,
                     uint64_t* dram, size_t dram_words) {
    std::ifstream f(path);
    if (!f) { fprintf(stderr, "[sim] cannot open: %s\n", path); exit(1); }

    uint64_t addr  = 0;
    size_t   total = 0;
    std::string line;
    std::vector<uint8_t> bytes;

    auto flush = [&]() {
        for (size_t i = 0; i < bytes.size(); i++) {
            uint64_t ba = addr + i;

            if (ba >= SRAM_BASE && ba < SRAM_BASE + sram_words * 8) {
                uint64_t wi = (ba - SRAM_BASE) / 8;
                uint64_t bo = (ba - SRAM_BASE) % 8;
                sram[wi] &= ~(0xFFULL << (bo * 8));
                sram[wi] |=  ((uint64_t)bytes[i] << (bo * 8));
                total++;
            } else if (ba >= DRAM_BASE && ba < DRAM_BASE + dram_words * 8) {
                uint64_t wi = (ba - DRAM_BASE) / 8;
                uint64_t bo = (ba - DRAM_BASE) % 8;
                dram[wi] &= ~(0xFFULL << (bo * 8));
                dram[wi] |=  ((uint64_t)bytes[i] << (bo * 8));
                total++;
            }
        }
        bytes.clear();
    };

    while (std::getline(f, line)) {
        if (line.empty()) continue;
        if (line[0] == '@') {
            flush();
            addr = std::stoull(line.substr(1), nullptr, 16);
        } else {
            std::istringstream ss(line);
            std::string tok;
            while (ss >> tok) bytes.push_back((uint8_t)std::stoul(tok, nullptr, 16));
        }
    }
    flush();
    printf("[sim] Loaded %zu bytes from %s\n", total, path);
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    const char* hex_image  = nullptr;
    uint64_t    max_cycles = 50000000;   // 50M — enough for OpenSBI banner

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "+hex=",    5) == 0) hex_image  = argv[i] + 5;
        if (strncmp(argv[i], "+cycles=", 8) == 0) max_cycles = atoll(argv[i] + 8);
    }

    // ── DRAM model (heap-allocated — 64MB) ──────────────────────────────────
    static uint64_t dram_mem[DRAM_WORDS];
    memset(dram_mem, 0, sizeof(dram_mem));

    VSoC* dut = new VSoC;

    if (hex_image) {
        // Zero and populate SRAM
        auto& mem       = dut->rootp->SoC__DOT__sram__DOT__mem_ext__DOT__Memory;
        auto& fetch_mem = dut->rootp->SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory;
        for (size_t i = 0; i < SRAM_WORDS; i++) { mem[i] = 0; fetch_mem[i] = 0; }

        load_hex(hex_image,
                 (uint64_t*)&mem[0], SRAM_WORDS,
                 dram_mem,           DRAM_WORDS);

        // Mirror SRAM data into fetch port
        for (size_t i = 0; i < SRAM_WORDS; i++) fetch_mem[i] = mem[i];

        printf("[sim] DRAM[0] = 0x%016llx  (first word at 0x80000000)\n",
               (unsigned long long)dram_mem[0]);
    }

    // ── Reset ────────────────────────────────────────────────────────────────
    dut->reset      = 1;
    dut->clock      = 0;
    dut->io_uart_rx = 1;
    dut->io_dram_rdata = 0;

    for (int i = 0; i < 10; i++) {
        dut->clock = 0; dut->eval();
        dut->clock = 1; dut->eval();
    }
    dut->reset = 0;

    // Must match UART(50000000, 115200) in SoC.scala.
    UartDecoder uart(50000000, 115200);

    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        // ── Rising edge ──────────────────────────────────────────────────────
        dut->clock = 0; dut->eval();
        dut->clock = 1; dut->eval();

        // ── Service DRAM port ────────────────────────────────────────────────
        // Zero-latency model: present rdata on the same cycle as the request.
        // OpenSBI/Linux are fine with this; add a latency register here later
        // if you want to model realistic DRAM timing.
        if (dut->io_dram_valid) {
            uint64_t addr = dut->io_dram_addr;

            if (addr >= DRAM_BASE && addr < DRAM_BASE + (uint64_t)DRAM_WORDS * 8) {
                uint64_t wi = (addr - DRAM_BASE) / 8;

                if (dut->io_dram_wen) {
                    // Byte-enable write
                    uint8_t strb = dut->io_dram_wstrb;
                    uint64_t old = dram_mem[wi];
                    uint64_t val = (uint64_t)dut->io_dram_wdata;
                    uint64_t msk = 0;
                    for (int b = 0; b < 8; b++)
                        if (strb & (1 << b)) msk |= 0xFFULL << (b * 8);
                    dram_mem[wi] = (old & ~msk) | (val & msk);
                }

                dut->io_dram_rdata = dram_mem[wi];
            } else {
                dut->io_dram_rdata = 0;
            }
        }

        // ── UART probe (fires when transmitter latches a new byte) ───────────
        {
            bool    tx_valid  = dut->rootp->SoC__DOT____Vcellinp__uart__io_tx_valid;
            uint8_t uart_state= dut->rootp->SoC__DOT__uart__DOT__state;

            if (tx_valid && uart_state == 0) {
                uint8_t  tx_data = dut->rootp->SoC__DOT__uart__DOT__shift_reg;
                uint64_t a0 = dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_10;
                printf("[uart-accept] cycle=%llu tx=0x%02x '%c' a0=0x%016llx\n",
                       (unsigned long long)cycle, tx_data,
                       (tx_data >= 32 && tx_data <= 126) ? tx_data : '.',
                       (unsigned long long)a0);
            }
        }

        // ── UART decode + DONE detection ─────────────────────────────────────
        int ch = uart.tick(dut->io_uart_tx);
        if (ch >= 0) {
            putchar(ch);
            fflush(stdout);

            static char buf[16] = {};
            memmove(buf, buf + 1, 7);
            buf[7] = (char)ch;

            if (strncmp(buf + 4, "DONE", 4) == 0) {
                printf("\n[sim] DONE received — stopping at cycle %llu\n",
                       (unsigned long long)cycle);
                break;
            }
        }

        // ── Early boot trace (first 200 cycles) ─────────────────────────────
        if (cycle < 200) {
            printf("[boot] cycle=%-5llu  pc=0x%08llx  instr=0x%08x\n",
                   (unsigned long long)cycle,
                   (unsigned long long)dut->rootp->SoC__DOT__core__DOT__if_id__DOT__reg_pc,
                   (uint32_t)dut->rootp->SoC__DOT__core__DOT__if_id__DOT__reg_instr);
        }

        cycle++;
    }

    if (cycle >= max_cycles)
        printf("[sim] cycle limit %llu reached\n", (unsigned long long)max_cycles);

    dut->final();
    delete dut;
    return 0;
}