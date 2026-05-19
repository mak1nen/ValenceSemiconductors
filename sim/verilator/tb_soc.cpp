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

#define SRAM_BASE   0x20000000UL
#define SRAM_WORDS  8192
#define UART_BASE   0x10000000UL

struct UartDecoder {
    int     baud_cycles;
    int     state;        // 0=idle, 1=start, 2=data, 3=stop
    int     bit_count;
    int     sample_count;
    uint8_t shift;
    int     prev_tx;

    UartDecoder(int clk_hz, int baud) {
        baud_cycles  = clk_hz / baud;
        state        = 0;
        bit_count    = 0;
        sample_count = 0;
        shift        = 0;
        prev_tx      = 1;
    }

    int tick(int tx) {
        int result = -1;

        switch (state) {
        case 0:
            if (prev_tx == 1 && tx == 0) {
                state        = 1;
                sample_count = baud_cycles / 2;
            }
            break;

        case 1:
            if (--sample_count <= 0) {
                state        = 2;
                bit_count    = 0;
                shift        = 0;
                sample_count = baud_cycles;
            }
            break;

        case 2:
            if (--sample_count <= 0) {
                shift |= (tx & 1) << bit_count;
                bit_count++;
                sample_count = baud_cycles;

                if (bit_count == 8) {
                    state = 3;
                }
            }
            break;

        case 3:
            if (--sample_count <= 0) {
                result = (int)(unsigned char)shift;
                state  = 0;
            }
            break;
        }

        prev_tx = tx;
        return result;
    }
};

static void load_hex(const char* path, uint64_t* sram, size_t words) {
    std::ifstream f(path);
    if (!f) {
        fprintf(stderr, "[sim] Error: cannot open hex file: %s\n", path);
        exit(1);
    }

    uint64_t addr = 0;
    std::string line;
    size_t total = 0;
    std::vector<uint8_t> bytes;

    auto flush_bytes = [&]() {
        for (size_t i = 0; i < bytes.size(); i++) {
            uint64_t byte_addr = addr + i;

            if (byte_addr < SRAM_BASE) {
                continue;
            }

            uint64_t word_idx = (byte_addr - SRAM_BASE) / 8;
            uint64_t byte_off = (byte_addr - SRAM_BASE) % 8;

            if (word_idx < words) {
                sram[word_idx] &= ~(0xFFULL << (byte_off * 8));
                sram[word_idx] |=  ((uint64_t)bytes[i] << (byte_off * 8));
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
            flush_bytes();
            addr = std::stoull(line.substr(1), nullptr, 16);
        } else {
            std::istringstream ss(line);
            std::string token;

            while (ss >> token) {
                bytes.push_back((uint8_t)std::stoul(token, nullptr, 16));
            }
        }
    }

    flush_bytes();

    printf("[sim] Loaded %zu bytes from %s\n", total, path);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    const char* hex_image  = nullptr;
    uint64_t    max_cycles = 10000000;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "+hex=", 5) == 0) {
            hex_image = argv[i] + 5;
        }

        if (strncmp(argv[i], "+cycles=", 8) == 0) {
            max_cycles = atoll(argv[i] + 8);
        }
    }

    VSoC* dut = new VSoC;

    if (hex_image) {
        auto& mem = dut->rootp->SoC__DOT__sram__DOT__mem_ext__DOT__Memory;
        auto& fetch_mem = dut->rootp->SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory;

        for (size_t i = 0; i < SRAM_WORDS; i++) {
            mem[i] = 0;
            fetch_mem[i] = 0;
        }

        load_hex(hex_image, (uint64_t*)&mem[0], SRAM_WORDS);
        load_hex(hex_image, (uint64_t*)&fetch_mem[0], SRAM_WORDS);

        printf("[sim] SRAM data[0]  = 0x%016llx\n",
               (unsigned long long)mem[0]);
        printf("[sim] SRAM fetch[0] = 0x%016llx\n",
               (unsigned long long)fetch_mem[0]);
    }

    // Reset
    dut->reset      = 1;
    dut->clock      = 0;
    dut->io_uart_rx = 1;

    for (int i = 0; i < 10; i++) {
        dut->clock = 0;
        dut->eval();

        dut->clock = 1;
        dut->eval();
    }

    dut->reset = 0;

    // Must match UART(50000000, 115200) in SoC.scala.
    UartDecoder uart(50000000, 115200);

    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        dut->clock = 0;
        dut->eval();

        dut->clock = 1;
        dut->eval();

        bool tx_valid = dut->rootp->SoC__DOT____Vcellinp__uart__io_tx_valid;
        uint8_t tx_data = dut->rootp->SoC__DOT____Vcellinp__uart__io_tx_data;
        uint8_t uart_state = dut->rootp->SoC__DOT__uart__DOT__state;

        if (tx_valid && uart_state == 0) {
            uint64_t core_wdata = dut->rootp->SoC__DOT___core_io_dcache_wdata;
            uint64_t a0 = dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_10;
            uint64_t a4 = dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_14;
            uint64_t a5 = dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_15;

            printf("[uart-accept] cycle=%llu tx=0x%02x '%c' core_wdata=0x%016llx a0=0x%016llx a4=0x%016llx a5=0x%016llx\n",
                   (unsigned long long)cycle,
                   tx_data,
                   (tx_data >= 32 && tx_data <= 126) ? tx_data : '.',
                   (unsigned long long)core_wdata,
                   (unsigned long long)a0,
                   (unsigned long long)a4,
                   (unsigned long long)a5);
        }

        int ch = uart.tick(dut->io_uart_tx);
        if (ch >= 0) {
            putchar(ch);
            fflush(stdout);

            static char buf[8] = {};
            memmove(buf, buf + 1, 3);
            buf[3] = (char)ch;

            if (strncmp(buf, "DONE", 4) == 0) {
                printf("\n[sim] DONE received — stopping\n");
                break;
            }
        }

        if (cycle < 120) {

                        uint64_t idex_pc  = dut->rootp->SoC__DOT__core__DOT__id_ex__DOT__reg_pc;
                        uint8_t  idex_rd  = dut->rootp->SoC__DOT__core__DOT__id_ex__DOT__reg_rd;
                        bool     idex_jal = dut->rootp->SoC__DOT__core__DOT__id_ex__DOT__reg_isJal;
                        bool     idex_jalr= dut->rootp->SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr;
                        uint64_t ex_res   = dut->rootp->SoC__DOT__core__DOT___execute_io_out_result;
                        uint64_t x1       = dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_1;

                        if (idex_jal || idex_jalr || idex_rd == 1 || x1 == 9) {
                            printf("[ra-debug] cycle=%llu idex_pc=0x%08llx rd=x%u jal=%d jalr=%d ex_res=0x%016llx x1=0x%016llx\n",
                                (unsigned long long)cycle,
                                (unsigned long long)idex_pc,
                                idex_rd,
                                idex_jal,
                                idex_jalr,
                                (unsigned long long)ex_res,
                                (unsigned long long)x1);
                            }


            printf(
                "[sim] cycle %llu  frontend_pc=0x%08llx  if_id_pc=0x%08llx  if_id_instr=0x%08x  x1=0x%016llx  x5=0x%016llx  x6=0x%016llx\n",
                (unsigned long long)cycle,
                (unsigned long long)dut->rootp->SoC__DOT__core__DOT__frontend__DOT__pc,
                (unsigned long long)dut->rootp->SoC__DOT__core__DOT__if_id__DOT__reg_pc,
                (uint32_t)dut->rootp->SoC__DOT__core__DOT__if_id__DOT__reg_instr,
                (unsigned long long)dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_1,
                (unsigned long long)dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_5,
                (unsigned long long)dut->rootp->SoC__DOT__core__DOT__regfile__DOT__regs_6
            );
        }

        cycle++;
    }

    printf("[sim] completed %llu cycles\n", (unsigned long long)cycle);

    dut->final();
    delete dut;

    return 0;
}