TARGET=cpu
.PHONY: $(TARGET) bin
RTLSRC=../rtl
all: directories $(TARGET) bin
BINSRC=bin_src
BINOBJ=bin_obj
BINTST=bin_test
BINEXP=bin_export
RSTLOG=result_logs
RSTEXP=result_export

objects := $(wildcard *.v)

LDFLAGS=
CFLAGS=-g -O3
ESCAPED_FLAGS :=\"$(FLAGS_STR)\"

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

build_dirs:
	mkdir -p $(BINSRC)
	mkdir -p $(BINTST)
	mkdir -p $(BINEXP)
	mkdir -p $(RSTLOG)
	mkdir -p $(RSTEXP)

ddr_jump: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32 $(BINSRC)/ddr_jump.s -o $(BINOBJ)/ddr_jump.bin -static -nostartfiles -T $(BINSRC)/bram.ld
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/ddr_jump.bin $(BINEXP)/ddr_jump.bin_dump


syscalls:
	riscv-none-embed-gcc -march=rv32i	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls_i.o
	riscv-none-embed-gcc -march=rv32im	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls_im.o
	riscv-none-embed-gcc -march=rv32imf	 -mabi=ilp32  -c $(BINSRC)/syscalls.c -o $(BINOBJ)/syscalls_imf.o

dhry_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/dhry_1.c $(BINSRC)/dhry_2.c $(BINSRC)/crt.S -o $(BINOBJ)/dhry_bram_i.bin -static -nostartfiles -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/dhry_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/dhry_bram_i.bin $(BINEXP)/dhry_noelv.bin_dump
	
core_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -DPERFORMANCE_RUN=1 -DITERATIONS=100 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/core_bram_i.bin -DFLAGS_STR=$(ESCAPED_FLAGS)  -static -nostartfiles  -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/core_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/core_bram_i.bin $(BINEXP)/core_bram_i.bin_dump

linpack_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DSP=true -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/linpack-patched.c $(BINSRC)/crt.S -o $(BINOBJ)/linpack_bram_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/linpack_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/linpack_bram_i.bin $(BINEXP)/linpack_bram_i.bin_dump

linpacd_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DDP=true -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/linpack-patched.c $(BINSRC)/crt.S -o $(BINOBJ)/linpacd_bram_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/linpacd_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/linpacd_bram_i.bin $(BINEXP)/linpacd_bram_i.bin_dump

stream_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/stream.c $(BINSRC)/crt.S -o $(BINOBJ)/stream_bram_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/stream_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/stream_bram_i.bin $(BINEXP)/stream_bram_i.bin_dump

kiss_bram_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/kiss_fft.c $(BINSRC)/kiss_fftr.c  $(BINSRC)/kiss_fftnd.c  $(BINSRC)/kiss_fftndr.c $(BINSRC)/pstats.c $(BINSRC)/benchkiss.c $(BINSRC)/crt.S -o $(BINOBJ)/kiss_bram_i.bin -Dkiss_fft_scalar=int -static  -nostartfiles -lm -lgcc -T $(BINSRC)/bram.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x60000000 131072 $(BINOBJ)/kiss_bram_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/kiss_bram_i.bin $(BINEXP)/kiss_bram_i.bin_dump

dhry_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/dhry_1.c $(BINSRC)/dhry_2.c $(BINSRC)/crt.S -o $(BINOBJ)/dhry_ddr_i.bin -static -nostartfiles -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/dhry_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/dhry_ddr_i.bin $(BINEXP)/dhry_noelv.bin_dump
	
core_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -DPERFORMANCE_RUN=1 -DITERATIONS=100 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/coremark/core_list_join.c $(BINSRC)/coremark/core_main.c $(BINSRC)/coremark/core_matrix.c $(BINSRC)/coremark/core_state.c $(BINSRC)/coremark/core_util.c $(BINSRC)/coremark/core_portme.c $(BINSRC)/crt.S -o $(BINOBJ)/core_ddr_i.bin -DFLAGS_STR=$(ESCAPED_FLAGS)  -static -nostartfiles  -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/core_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/core_ddr_i.bin $(BINEXP)/core_ddr_i.bin_dump

linpack_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DSP=true -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/linpack-patched.c $(BINSRC)/crt.S -o $(BINOBJ)/linpack_ddr_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/linpack_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/linpack_ddr_i.bin $(BINEXP)/linpack_ddr_i.bin_dump

linpacd_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DDP=true -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/linpack-patched.c $(BINSRC)/crt.S -o $(BINOBJ)/linpacd_ddr_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/linpacd_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/linpacd_ddr_i.bin $(BINEXP)/linpacd_ddr_i.bin_dump

stream_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/stream.c $(BINSRC)/crt.S -o $(BINOBJ)/stream_ddr_i.bin  -static -nostartfiles -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/stream_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/stream_ddr_i.bin $(BINEXP)/stream_ddr_i.bin_dump

kiss_ddr_i: 
	riscv-none-embed-gcc -march=rv32i -mabi=ilp32  -DPREALLOCATE=1 -mstrict-align -mcmodel=medany -static -std=gnu99 -O3 -Ofast -ffast-math -fno-common -fno-builtin-printf $(BINOBJ)/syscalls_i.o $(BINSRC)/kiss_fft.c $(BINSRC)/kiss_fftr.c  $(BINSRC)/kiss_fftnd.c  $(BINSRC)/kiss_fftndr.c $(BINSRC)/pstats.c $(BINSRC)/benchkiss.c $(BINSRC)/crt.S -o $(BINOBJ)/kiss_ddr_i.bin -Dkiss_fft_scalar=int -static  -nostartfiles -lm -lgcc -T $(BINSRC)/ddr.ld
	python3 $(BINSRC)/convert.py riscv-none-embed- 0x80000000 131072 $(BINOBJ)/kiss_ddr_i.bin $(BINTST)/
	riscv-none-embed-objcopy -O binary -j .text* -j .*data* -j .rodata* -j .*bss --set-section-flags .bss=alloc,load,contents $(BINOBJ)/kiss_ddr_i.bin $(BINEXP)/kiss_ddr_i.bin_dump


all: cpu build_dirs ddr_jump syscalls dhry_bram_i core_bram_i linpack_bram_i linpacd_bram_i stream_bram_i kiss_bram_i dhry_ddr_i core_ddr_i linpack_ddr_i linpacd_ddr_i stream_ddr_i kiss_ddr_i

test_all:
	for name in $(BINTST)/*.mem; do\
        echo $${name};\
		./cpu/cpu -p $${name} -l 10000000000;\
    done

log_all:
	for name in $(BINTST)/*.mem; do\
        echo $${name};\
		./cpu/cpu -p $${name} -l 10000000000 > $(RSTLOG)/$$(basename $${name} .mem).log;\
    done

export_logs:
	cp $(RSTLOG)/* $(RSTEXP)/

diff_logs:
	diff -bur $(RSTLOG)/ $(RSTEXP)/