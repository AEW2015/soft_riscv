  .section ".text.init"
  .globl _start
_start:
.option push
.option norelax
  la gp, __global_pointer$
.option pop

  la  tp, _end + 63
  and tp, tp, -64
  #define STKSHIFT 12
  sll a2, a0, STKSHIFT
  add tp, tp, a2
  add sp, a0, 1
  sll sp, sp, STKSHIFT
  add sp, sp, tp

  j _init

.section ".tdata.begin"
.globl _tdata_begin
_tdata_begin:

.section ".tdata.end"
.globl _tdata_end
_tdata_end:

.section ".tbss.end"
.globl _tbss_end
_tbss_end: