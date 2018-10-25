#ifndef SIMRISV_H
#define SIMRISV_H

#include <iostream>
#include <sstream>  
#include "stdint.h"
#include "cpu.h"

class SimRISCV
{
private:
	SimRISCV();
	static SimRISCV *get_sim();
	uint32_t pc;
	int32_t gpregs[32];	
public:
	static void reset();
	static void ori(int rd,int rs1,int imm);
	static void andi(int rd,int rs1,int imm);
	static void andr(int rd,int rs1,int rs2);
	static void orr(int rd,int rs1,int rs2);
	static void xorr(int rd,int rs1,int rs2);
	static void slt(int rd,int rs1,int rs2);
	static void sltu(int rd,int rs1,int rs2);
	static void addi(int rd,int rs1,int imm);
	static void xori(int rd,int rs1,int imm);
	static void slti(int rd,int rs1,int imm);
	static void sltiu(int rd,int rs1,int imm);
	static void slli(int rd,int rs1,int shamt);
	static void sll(int rd,int rs1,int rs2);
	static void srl(int rd,int rs1,int rs2);
	static void sra(int rd,int rs1,int rs2);
	static void srli(int rd,int rs1,int shamt);
	static void srai(int rd,int rs1,int shamt);
	static void add(int rd,int rs1,int rs2);
	static void sub(int rd,int rs1,int rs2);
	static void lui(int rd,int imm);
	static void auipc(int rd,int imm);
	static void jal(int rd,int imm);
	static void jalr(int rd,int rs, int imm);
	static void beq(int rs1,int rs2, int imm);
	static void bne(int rs1,int rs2, int imm);
	static uint32_t score(cpu* uut,std::stringstream& emesg);
};







#endif