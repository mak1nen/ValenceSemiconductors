// tb_soc.cpp — Verilator testbench for Valence RISC-V SoC (OpenSBI + DTB)
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

#define SRAM_BASE    0x20000000UL
#define SRAM_WORDS   8192
#define DRAM_BASE    0x80000000UL
#define DRAM_WORDS   (256*1024*1024/8)  // 256MB
#define UART_BASE    0x10000000UL
#define UART_SIZE    0x1000UL
#define DTB_ADDR     0x87000000UL

struct UartDecoder {
    int baud_cycles, state, bit_count, sample_count, prev_tx;
    uint8_t shift;

    UartDecoder(int clk_hz, int baud)
        : baud_cycles(clk_hz / baud), state(0), bit_count(0),
          sample_count(0), prev_tx(1), shift(0) {}

    int tick(int tx) {
        int result = -1;

        switch (state) {
        case 0:
            if (prev_tx == 1 && tx == 0) {
                state = 1;
                sample_count = baud_cycles / 2;
            }
            break;

        case 1:
            if (--sample_count <= 0) {
                state = 2;
                bit_count = 0;
                shift = 0;
                sample_count = baud_cycles;
            }
            break;

        case 2:
            if (--sample_count <= 0) {
                shift |= (tx & 1) << bit_count;
                if (++bit_count == 8) {
                    state = 3;
                }
                sample_count = baud_cycles;
            }
            break;

        case 3:
            if (--sample_count <= 0) {
                result = (int)(unsigned char)shift;
                state = 0;
            }
            break;
        }

        prev_tx = tx;
        return result;
    }
};

static void load_hex(const char* path,
                     uint64_t* sram,
                     size_t sw,
                     uint64_t* dram,
                     size_t dw) {
    std::ifstream f(path);
    if (!f) {
        fprintf(stderr, "[sim] cannot open: %s\n", path);
        exit(1);
    }

    uint64_t addr = 0;
    size_t total = 0;
    std::string line;
    std::vector<uint8_t> bytes;

    auto flush = [&]() {
        for (size_t i = 0; i < bytes.size(); i++) {
            uint64_t ba = addr + i;

            if (ba >= SRAM_BASE && ba < SRAM_BASE + sw * 8) {
                uint64_t wi = (ba - SRAM_BASE) / 8;
                uint64_t bo = (ba - SRAM_BASE) % 8;

                sram[wi] &= ~(0xFFULL << (bo * 8));
                sram[wi] |= ((uint64_t)bytes[i] << (bo * 8));
                total++;

            } else if (ba >= DRAM_BASE && ba < DRAM_BASE + dw * 8) {
                uint64_t wi = (ba - DRAM_BASE) / 8;
                uint64_t bo = (ba - DRAM_BASE) % 8;

                dram[wi] &= ~(0xFFULL << (bo * 8));
                dram[wi] |= ((uint64_t)bytes[i] << (bo * 8));
                total++;
            }
        }

        bytes.clear();
    };

    while (std::getline(f, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '@') {
            flush();
            addr = std::stoull(line.substr(1), nullptr, 16);
        } else {
            std::istringstream ss(line);
            std::string t;

            while (ss >> t) {
                bytes.push_back((uint8_t)std::stoul(t, nullptr, 16));
            }
        }
    }

    flush();

    printf("[sim] Loaded %zu bytes from %s\n", total, path);
}

static void load_blob(const char* path,
                      uint64_t* dram,
                      size_t dw,
                      uint64_t phys) {
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        fprintf(stderr, "[sim] cannot open blob: %s\n", path);
        exit(1);
    }

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(f)),
                              std::istreambuf_iterator<char>());

    for (size_t i = 0; i < data.size(); i++) {
        uint64_t ba = phys + i;

        if (ba >= DRAM_BASE && ba < DRAM_BASE + dw * 8) {
            uint64_t wi = (ba - DRAM_BASE) / 8;
            uint64_t bo = (ba - DRAM_BASE) % 8;

            dram[wi] &= ~(0xFFULL << (bo * 8));
            dram[wi] |= ((uint64_t)data[i] << (bo * 8));
        }
    }

    printf("[sim] Loaded %zu byte blob from %s at 0x%llx\n",
           data.size(), path, (unsigned long long)phys);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    const char* hex = nullptr;
    const char* dtb = nullptr;
    uint64_t max_cycles = 50000000;
    bool dbg = false;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "+hex=", 5) == 0) {
            hex = argv[i] + 5;
        }

        if (strncmp(argv[i], "+dtb=", 5) == 0) {
            dtb = argv[i] + 5;
        }

        if (strncmp(argv[i], "+cycles=", 8) == 0) {
            max_cycles = atoll(argv[i] + 8);
        }

        if (strcmp(argv[i], "+dram_debug") == 0) {
            dbg = true;
        }
    }

    static uint64_t dram_mem[DRAM_WORDS];
    memset(dram_mem, 0, sizeof(dram_mem));

    VSoC* dut = new VSoC;

    if (hex) {
        auto& mem  = dut->rootp->SoC__DOT__sram__DOT__mem_ext__DOT__Memory;
        auto& fmem = dut->rootp->SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory;

        for (size_t i = 0; i < SRAM_WORDS; i++) {
            mem[i] = 0;
            fmem[i] = 0;
        }

        load_hex(hex, (uint64_t*)&mem[0], SRAM_WORDS, dram_mem, DRAM_WORDS);

        for (size_t i = 0; i < SRAM_WORDS; i++) {
            fmem[i] = mem[i];
        }
    }

    if (dtb) {
        load_blob(dtb, dram_mem, DRAM_WORDS, DTB_ADDR);
    }

    dut->reset = 1;
    dut->clock = 0;
    dut->io_uart_rx = 1;
    dut->io_dram_rdata = 0;

    for (int i = 0; i < 10; i++) {
        dut->clock = 0;
        dut->eval();

        dut->clock = 1;
        dut->eval();
    }

    dut->reset = 0;

    UartDecoder uart(50000000, 115200);

    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        dut->clock = 0;
        dut->eval();

        // --------------------------------------------------------------------
        // Two-phase DRAM/MMIO model.
        //
        // Important for AMOs:
        //   1. Core presents addr.
        //   2. Testbench drives io_dram_rdata from dram_mem/MMIO.
        //   3. dut->eval() lets AMO write data settle from that rdata.
        //   4. Testbench commits final write signals into dram_mem/MMIO.
        //
        // UART MMIO fallback is kept here, but normal UART accesses are now
        // handled inside SoC.scala. This block is harmless if not used.
        // --------------------------------------------------------------------
        {
            uint64_t addr = dut->io_dram_addr;

            // Phase 1: drive read data.
            if (addr >= UART_BASE && addr < UART_BASE + UART_SIZE) {
                uint64_t off = addr - UART_BASE;

                if ((off & 7ULL) == 5) {
                    // 16550 LSR: bit 5 THRE + bit 6 TEMT.
                    // Put 0x60 in every byte lane for robustness.
                    dut->io_dram_rdata = 0x6060606060606060ULL;
                } else {
                    dut->io_dram_rdata = 0;
                }

            } else if (addr >= DRAM_BASE &&
                       addr < DRAM_BASE + (uint64_t)DRAM_WORDS * 8) {
                uint64_t wi = (addr - DRAM_BASE) / 8;
                dut->io_dram_rdata = dram_mem[wi];

            } else {
                dut->io_dram_rdata = 0;
            }

            // Let combinational logic settle after rdata is provided.
            // This is critical for AMO write data.
            dut->eval();

            // Phase 2: commit writes using settled signals.
            addr = dut->io_dram_addr;

            if (addr >= UART_BASE && addr < UART_BASE + UART_SIZE) {
                uint64_t off = addr - UART_BASE;

                if (dut->io_dram_valid && dut->io_dram_wen && ((off & 7ULL) == 0)) {
                    uint64_t lane_shift = (addr & 7ULL) * 8ULL;
                    char ch = (char)((dut->io_dram_wdata >> lane_shift) & 0xff);

                    putchar(ch);
                    fflush(stdout);
                }

            } else if (addr >= DRAM_BASE &&
                       addr < DRAM_BASE + (uint64_t)DRAM_WORDS * 8) {
                uint64_t wi = (addr - DRAM_BASE) / 8;
                uint64_t old = dram_mem[wi];

                if (dut->io_dram_valid && dut->io_dram_wen) {
                    uint8_t strb = dut->io_dram_wstrb;
                    uint64_t val = dut->io_dram_wdata;
                    uint64_t msk = 0;

                    for (int b = 0; b < 8; b++) {
                        if (strb & (1 << b)) {
                            msk |= 0xFFULL << (b * 8);
                        }
                    }

                    uint64_t next = (old & ~msk) | (val & msk);
                    dram_mem[wi] = next;

                    if (dbg) {
                        printf("[DRAM-W] cy=%llu addr=0x%09llx old=0x%016llx new=0x%016llx strb=0x%02x\n",
                               (unsigned long long)cycle,
                               (unsigned long long)addr,
                               (unsigned long long)old,
                               (unsigned long long)dram_mem[wi],
                               (unsigned)strb);
                    }
                }
            }
        }

        dut->clock = 1;
        dut->eval();

        int ch = uart.tick(dut->io_uart_tx);
        if (ch >= 0) {
            putchar(ch);
            fflush(stdout);

            static char buf[16] = {};
            memmove(buf, buf + 1, 7);
            buf[7] = (char)ch;

            if (strncmp(buf + 4, "DONE", 4) == 0) {
                printf("\n[sim] DONE at cycle %llu\n", (unsigned long long)cycle);
                break;
            }
        }

        cycle++;
    }

    if (cycle >= max_cycles) {
        printf("\n[sim] cycle limit %llu reached\n", (unsigned long long)max_cycles);
    }

    dut->final();
    delete dut;

    return 0;
}