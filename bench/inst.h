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
uint32_t orr (int rd, int rs1, int rs2);
uint32_t xorr (int rd, int rs1, int rs2);
uint32_t slt (int rd, int rs1, int rs2);
uint32_t sltu (int rd, int rs1, int rs2);
uint32_t sra (int rd, int rs1, int rs2);
uint32_t srli (int rd, int rs, int shamt);
uint32_t srai (int rd, int rs, int shamt);
uint32_t jalr (int rd, int rs, int imm);
uint32_t beq (int rs1, int rs2, int imm);
uint32_t bne (int rs1, int rs2, int imm);
uint32_t blt (int rs1, int rs2, int imm);
uint32_t bge (int rs1, int rs2, int imm);
uint32_t bltu (int rs1, int rs2, int imm);
uint32_t bgeu (int rs1, int rs2, int imm);
uint32_t sw (int rs1, int rs2, int imm);
uint32_t sh (int rs1, int rs2, int imm);
uint32_t sb (int rs1, int rs2, int imm);
uint32_t lb (int rd, int rs1, int imm);
uint32_t lbu (int rd, int rs1, int imm);
uint32_t lh (int rd, int rs1, int imm);
uint32_t lhu (int rd, int rs1, int imm);
uint32_t lw (int rd, int rs1, int imm);
uint32_t jal (int rd, int imm);

#endif