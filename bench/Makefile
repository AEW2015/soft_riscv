TARGET=cpu
.PHONY: $(TARGET)
RTLSRC=../rtl
all: $(TARGET)

objects := $(wildcard *.v)

LDFLAGS=
CFLAGS=-g -O3

$(TARGET):
	verilator -Wno-fatal -I$(RTLSRC)/ -cc typePack.v $(@)_top.v  --prefix $(@) --trace --exe  ../$(@)tb.cpp ../inst.cpp ../simriscv.cpp -Mdir $(@) -CFLAGS "$(CFLAGS)"
	make -C $(@) -f $(@).mk
clean::
	rm -rf *.o $(TARGET)
distclean:: clean
	rm -rf *~ *.txt *.vcd *.mif *.orig
