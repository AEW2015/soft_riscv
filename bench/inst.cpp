#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "inst.h"
#include "cpu_typePack.h"

uint32_t itype_inst (int rd, int rs, int imm, int fimm, int opcode){
	uint32_t cmd =  imm<<20|
					rs<<15|
					fimm<<12|
					rd<<7|
					opcode;
	return cmd;
}
uint32_t utype_inst (int rd, int imm, int opcode){
	uint32_t cmd =  imm<<12|
					rd<<7|
					opcode;
	return cmd;
}
uint32_t rtype_inst (int rd, int rs1, int rs2, int fimm, int opcode){
	uint32_t cmd =  rs2<<20|
					rs1<<15|
					fimm<<12|
					rd<<7|
					opcode;
	return cmd;
}
uint32_t lui (int rd, int imm){

	uint32_t cmd = utype_inst(rd,imm,cpu_typePack::opcodes::LUI);
	return cmd;
}

uint32_t auipc (int rd, int imm){

	uint32_t cmd = utype_inst(rd,imm,cpu_typePack::opcodes::AUIPC);
	return cmd;
}


uint32_t imm_inst (int rd, int rs, int imm, int fimm){
	uint32_t cmd = itype_inst(rd,rs,imm,fimm,cpu_typePack::opcodes::IMM);
	return cmd;
}


uint32_t op_inst (int rd, int rs, int imm, int fimm){
	uint32_t cmd = rtype_inst(rd,rs,imm,fimm,cpu_typePack::opcodes::OP);
	return cmd;
}
//1 creat a inst coder
uint32_t ori (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::OR);
	return cmd;
}

//1 creat a inst coder
uint32_t andi (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::AND);
	return cmd;
}

uint32_t addi (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::ADD);
	return cmd;
}

uint32_t add (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::ADD);
	return cmd;
}

uint32_t sub (int rd, int rs1, int rs2){
	uint16_t tmp = 0x400 | rs2;
	uint32_t cmd = op_inst(rd,rs1,tmp,cpu_typePack::FIMM::ADD);
	return cmd;
}

uint32_t xori (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::XOR);
	return cmd;
}

uint32_t slti (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::SLT);
	return cmd;
}

uint32_t sltiu (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::SLTU);
	return cmd;
}

uint32_t slli (int rd, int rs, int shamt){

	uint32_t cmd = imm_inst(rd,rs,shamt,cpu_typePack::FIMM::SLL);
	return cmd;
}

uint32_t sll (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::SLL);
	return cmd;
}

uint32_t srl (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::SRL);
	return cmd;
}
uint32_t andr (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::AND);
	return cmd;
}
uint32_t orr (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::OR);
	return cmd;
}
uint32_t xorr (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::XOR);
	return cmd;
}

uint32_t sra (int rd, int rs1, int rs2){
	uint16_t tmp = 0x400 | rs2;
	uint32_t cmd = op_inst(rd,rs1,tmp,cpu_typePack::FIMM::SRL);
	return cmd;
}

uint32_t srli (int rd, int rs, int shamt){

	uint32_t cmd = imm_inst(rd,rs,shamt,cpu_typePack::FIMM::SRL);
	return cmd;
}

uint32_t srai (int rd, int rs, int shamt){
	uint16_t tmp = 0x400 | shamt;
	uint32_t cmd = imm_inst(rd,rs,tmp,cpu_typePack::FIMM::SRL);
	return cmd;
}
