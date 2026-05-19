TOP      = SoC
RTL_DIR  = ../../hardware/generated
SW_DIR   = ../sw
CC       = riscv64-unknown-elf-gcc
CFLAGS   = -march=rv64i -mabi=lp64 -nostdlib -O2
VERILATOR_FLAGS = --cc --exe --build \
    --top-module $(TOP) \
    -Wno-WIDTHTRUNC \
    -Wno-WIDTHEXPAND

.PHONY: all sim hello clean

all: sim hello

# compile Verilator sim
sim:
	verilator $(VERILATOR_FLAGS) \
	    -I$(RTL_DIR) \
	    $(RTL_DIR)/$(TOP).sv \
	    tb_soc.cpp \
	    -o sim_$(TOP)

# compile hello.c test
hello:
	$(CC) $(CFLAGS) \
	    -T $(SW_DIR)/linker.ld \
	    $(SW_DIR)/boot/start.S \
	    $(SW_DIR)/tests/hello.c \
	    -o hello.elf
	riscv64-unknown-elf-objcopy -O binary hello.elf hello.bin

# run hello
run: sim hello
	./obj_dir/sim_$(TOP) +image=hello.bin +cycles=5000000

clean:
	rm -rf obj_dir *.elf *.bin