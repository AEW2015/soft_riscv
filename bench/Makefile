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
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O0 -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/test.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -static -nostdlib -nostartfiles -lm -lgcc  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 65536 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/output.bin
	
syscalls.o:
	riscv-none-embed-gcc -march=rv32imf	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls.o

dhry: syscalls.o
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/dhry_1.c $(BINSRC)/dhry_2.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/dhry_noelv.bin
	
ESCAPED_FLAGS :=\"$(FLAGS_STR)\"


coremark: 
	riscv-none-embed-gcc -march=rv32imf -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast 	-ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -DFLAGS_STR=$(ESCAPED_FLAGS) -DPERFORMANCE_RUN=1 -DITERATIONS=6000 -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/coremf.bin

linpack: 
	riscv-none-embed-gcc -march=rv32imf -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/linpack-patched.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin  -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/linpacdmf.bin

stream: 
	riscv-none-embed-gcc -march=rv32imf -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/stream.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin  -static -nostartfiles  -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/streammf.bin

kiss: 
	riscv-none-embed-gcc -march=rv32im -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls.o $(BINSRC)/kiss_fft.c $(BINSRC)/kiss_fftr.c  $(BINSRC)/kiss_fftnd.c  $(BINSRC)/kiss_fftndr.c $(BINSRC)/pstats.c $(BINSRC)/benchkiss.c $(BINSRC)/crt.S -o $(BINOBJ)/test.bin -Dkiss_fft_scalar=int -static  -nostartfiles -lm -lgcc -T $(BINSRC)/test.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/test.bin test.mem test.comments
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/test.bin $(BINOBJ)/kissm3.bin