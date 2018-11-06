#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "inst.h"
#include "def.h"
#include "cpu_typePack.h"

uint32_t itype_inst (int rd, int rs, int imm, int fimm, int opcode){
	uint32_t cmd =  imm<<20|
					rs<<15|
					fimm<<12|
					rd<<7|
					opcode;
	return cmd;
}
uint32_t btype_inst (int rs1, int rs2, int imm, int bimm){
	uint32_t cmd =  (imm&0x800)<<20|
					(imm&0x3F0)<<21|
					rs2<<20|
					rs1<<15|
					bimm<<12|
					(imm&0x00F)<<8|
					(imm&0x400)>>3|
					0b1100011;
	return cmd;
}
uint32_t stype_inst (int rs1, int rs2, int imm, int simm){
	uint32_t cmd =  (imm&0xFE0)<<20|
					rs2<<20|
					rs1<<15|
					simm<<12|
					(imm&0x01F)<<7|
					0b0100011;
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
uint32_t slt (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::SLT);
	return cmd;
}
uint32_t sltu (int rd, int rs1, int rs2){

	uint32_t cmd = op_inst(rd,rs1,rs2,cpu_typePack::FIMM::SLTU);
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
uint32_t jalr (int rd, int rs, int imm){
	uint32_t cmd = itype_inst(rd,rs,imm,0,cpu_typePack::opcodes::JALR);
	return cmd;
}
uint32_t beq (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BEQ);
	return cmd;
}
uint32_t bne (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BNE);
	return cmd;
}
uint32_t blt (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BLT);
	return cmd;
}
uint32_t bge (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BGE);
	return cmd;
}
uint32_t bltu (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BLTU);
	return cmd;
}
uint32_t bgeu (int rs1, int rs2, int imm){
	uint32_t cmd = btype_inst(rs1,rs2,imm,cpu_typePack::BIMM::BGEU);
	return cmd;
}
uint32_t sw (int rs1, int rs2, int imm){
	uint32_t cmd = stype_inst(rs1,rs2,imm,cpu_typePack::SIMM::WORD);
	return cmd;
}
uint32_t sh (int rs1, int rs2, int imm){
	uint32_t cmd = stype_inst(rs1,rs2,imm,cpu_typePack::SIMM::SHORT);
	return cmd;
}
uint32_t sb (int rs1, int rs2, int imm){
	uint32_t cmd = stype_inst(rs1,rs2,imm,cpu_typePack::SIMM::BYTE);
	return cmd;
}

uint32_t jal (int rd, int imm){
		uint32_t cmd =  (imm&0x80000)<<12|
					(imm&0x003FF)<<21|
					(imm&0x00400)<<10|
					(imm&0x7F800)<<1|
					rd<<7|
					cpu_typePack::opcodes::JAL;
	//std::cout << HEX imm << std::endl;
	//std::cout << HEX (imm<<1) << std::endl;
	//std::cout << HEX cmd << std::endl;
	return cmd;
}
