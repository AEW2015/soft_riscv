#ifndef INST_H
#define INST_H
#include "stdint.h"



uint32_t itype_inst (int rd, int rs, int imm, int fimm, int opcode);

uint32_t imm_inst (int rd, int rs, int imm, int fimm);
//1 creat a inst coder
uint32_t ori (int rd, int rs, int imm);

#endif