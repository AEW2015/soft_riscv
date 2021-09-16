TARGET=cpu
.PHONY: $(TARGET) bin
RTLSRC=../rtl
all: directories $(TARGET) bin
BINSRC=bin_src
BINOBJ=bin_obj

objects := $(wildcard *.v)

LDFLAGS=
CFLAGS=-g -O3

MKDIR_P = mkdir -p
directories: ${BINOBJ}

${BINOBJ}:
	${MKDIR_P} ${BINOBJ}

$(TARGET): 
	verilator -Wno-fatal -I$(RTLSRC)/ -cc typePack.v $(@)_top.v  --prefix $(@) --trace --exe  ../$(@)tb.cpp ../inst.cpp ../simriscv.cpp -Mdir $(@) -CFLAGS "$(CFLAGS)"
	make -C $(@) -f $(@).mk
clean::
	rm -rf *.coe test.mem test.comments *.o $(TARGET) ${BINOBJ}
distclean:: clean
	rm -rf *~ *.txt *.vcd *.mif *.orig

ESCAPED_FLAGS :=\"$(FLAGS_STR)\"

coes: core_1.coe core_10.coe core_40.coe corem_1.coe corem_10.coe corem_40.coe

core_1.coe: 
	riscv-none-embed-gcc -march=rv32i	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=1 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin core_1 test.comments

core_10.coe: 
	riscv-none-embed-gcc -march=rv32i	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=10 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin core_10 test.comments

core_40.coe: 
	riscv-none-embed-gcc -march=rv32i	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=40 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin core_40 test.comments

corem_1.coe: 
	riscv-none-embed-gcc -march=rv32im	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=1 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin corem_1 test.comments

corem_10.coe: 
	riscv-none-embed-gcc -march=rv32im	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=10 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin corem_10 test.comments

corem_40.coe: 
	riscv-none-embed-gcc -march=rv32im	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -Os -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=10 -DITERATIONS=40 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x00000000 16384 $(BINOBJ)/test.bin corem_40 test.comments


