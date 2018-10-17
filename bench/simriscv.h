#ifndef SIMRISV_H
#define SIMRISV_H

#include "stdint.h"

class SimRISCV
{
private:
	SimRISCV();

	static SimRISCV *get_sim();
	uint32_t pc;
	uint32_t gpregs[32];	
public:
	static void reset();
	static void ori(int rd,int rs1,int imm);
};







#endif