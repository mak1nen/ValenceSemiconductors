TOP      = SoC
RTL_DIR  = ../../hardware/generated
SW_DIR   = ../sw
CC       = riscv64-unknown-elf-gcc
OBJCOPY  = riscv64-unknown-elf-objcopy
CFLAGS   = -march=rv64im_zicsr_zicntr -mabi=lp64 -nostdlib -O2

VERILATOR_FLAGS = --cc --exe --build \
    --top-module $(TOP) \
    -Wno-WIDTHTRUNC \
    -Wno-WIDTHEXPAND

# default test — override with: make run TEST=002_ipc_bench
TEST    ?= 000_hello
CYCLES  ?= 10000000

ELF     = $(SW_DIR)/$(TEST).elf
HEX     = $(SW_DIR)/$(TEST).hex
SIM     = ./obj_dir/sim_$(TOP)

.PHONY: all sim sw run clean

# ── build everything ──────────────────────────────────────────────────────────
all: sim sw

# ── verilator sim binary ──────────────────────────────────────────────────────
sim:
	verilator $(VERILATOR_FLAGS) \
	    -I$(RTL_DIR) \
	    $(RTL_DIR)/$(TOP).sv \
	    tb_soc.cpp \
	    -o sim_$(TOP)

# ── compile a test to hex ─────────────────────────────────────────────────────
sw: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O verilog $< $@

$(ELF): $(SW_DIR)/tests/$(TEST).c $(SW_DIR)/boot/start.S
	$(CC) $(CFLAGS) \
	    -T $(SW_DIR)/linker.id \
	    $(SW_DIR)/boot/start.S \
	    $< \
	    -o $@

# ── run ───────────────────────────────────────────────────────────────────────
run: $(HEX)
	$(SIM) +hex=$(HEX) +cycles=$(CYCLES)

# ── run, strip debug noise ────────────────────────────────────────────────────
run-clean: $(HEX)
	$(SIM) +hex=$(HEX) +cycles=$(CYCLES) 2>&1 | grep -v "^\[sim\] cycle\|ra-debug"

# ── clean sw artifacts only ───────────────────────────────────────────────────
clean-sw:
	rm -f $(SW_DIR)/*.elf $(SW_DIR)/*.hex

# ── clean everything ──────────────────────────────────────────────────────────
clean:
	rm -rf obj_dir $(SW_DIR)/*.elf $(SW_DIR)/*.hex