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
	rm -rf test.mem test.comments *.o $(TARGET) ${BINOBJ}
distclean:: clean
	rm -rf *~ *.txt *.vcd *.mif *.orig
bin: syscalls.o
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O3 -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/test.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -static -nostdlib -nostartfiles -lgcc  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 16384 $(BINOBJ)/test.bin test.mem test.comments
	
syscalls.o:
	riscv-none-embed-gcc -march=rv32i	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o

dhry: syscalls.o
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O3 -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/dhry_1.c $(BINSRC)/dhry_2.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -static -nostdlib -nostartfiles -lgcc  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 65536 $(BINOBJ)/test.bin test.mem test.comments
	
