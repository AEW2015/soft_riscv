#ifndef INST_H
#define INST_H
#include "stdint.h"



uint32_t itype_inst (int rd, int rs, int imm, int fimm, int opcode);

uint32_t imm_inst (int rd, int rs, int imm, int fimm);
//1 creat a inst coder
uint32_t ori (int rd, int rs, int imm);

uint32_t andi (int rd, int rs, int imm);

uint32_t addi (int rd, int rs, int imm);
uint32_t add (int rd, int rs1, int rs2);
uint32_t sub (int rd, int rs1, int rs2);

uint32_t xori (int rd, int rs, int imm);

uint32_t slti (int rd, int rs, int imm);

uint32_t sltiu (int rd, int rs, int imm);

uint32_t lui (int rd, int imm);
uint32_t auipc (int rd, int imm);
uint32_t slli (int rd, int rs, int shamt);
uint32_t sll (int rd, int rs1, int rs2);
uint32_t srl (int rd, int rs1, int rs2);
uint32_t andr (int rd, int rs1, int rs2);
uint32_t sra (int rd, int rs1, int rs2);
uint32_t srli (int rd, int rs, int shamt);
uint32_t srai (int rd, int rs, int shamt);

#endif