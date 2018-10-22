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
//1 creat a inst coder
uint32_t ori (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::ORI);
	return cmd;
}

//1 creat a inst coder
uint32_t andi (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::ANDI);
	return cmd;
}

uint32_t addi (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::ADDI);
	return cmd;
}

uint32_t xori (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::XORI);
	return cmd;
}

uint32_t slti (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::SLTI);
	return cmd;
}

uint32_t sltiu (int rd, int rs, int imm){

	uint32_t cmd = imm_inst(rd,rs,imm,cpu_typePack::FIMM::SLTIU);
	return cmd;
}
