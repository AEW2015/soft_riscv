#include <verilated.h>
#include "cpu.h"
#include "cpu_typePack.h"
#include "verilated_vcd_c.h"
#include "simriscv.h"
#include <iostream>
#include <sstream>  
#include <string>
#include <cstdlib>
#include <cstdio>
#include "inst.h"

cpu *uut;
VerilatedVcdC* tfp;
vluint64_t main_time = 0;
double sc_time_stamp () {
	return main_time;
}

//TODO:

//2 assert
//3 random testing of ORI
void assertSignal (uint32_t a, uint32_t b){
	if(a != b){
			std::cout << "Assert failed @" <<  sc_time_stamp();
			std::cout << ": " << std::hex << std::uppercase << a;
			std::cout << "!=" << std::hex << std::uppercase << b;
			std::cout <<std::endl;
		}
}

void excute_instr();

int main (int argc, char** argv)
{
	bool vcdTrace = true;
	tfp = NULL;

	Verilated::commandArgs(argc, argv);
	uut = new cpu;
	uut->eval();
	uut->eval();

	if (vcdTrace)
	{
		Verilated::traceEverOn(true);

		tfp = new VerilatedVcdC;
		uut->trace(tfp, 99);

		std::string vcdname = argv[0];
		vcdname += ".vcd";
		std::cout << vcdname << std::endl;
		tfp->open(vcdname.c_str());

	}

	uut->CLOCK = 1;


	for(int cycle = 1;cycle<1000000;cycle++)
	{

		excute_instr();
		std::stringstream str;
		if(SimRISCV::score(uut,str)){
			std::cout << "Errors @" <<  sc_time_stamp() << std::endl << str.str() << std::endl;
			break;
		}
			
	}
	if (tfp != NULL)
		tfp->dump(main_time);
	uut->CLOCK = uut->CLOCK ? 0 : 1;
	uut->eval();
	main_time++;


	if (tfp != NULL)
		tfp->dump(main_time);
	uut->CLOCK = uut->CLOCK ? 0 : 1;
	uut->eval();
	main_time++;


	uut->final();

	if(tfp != NULL)
	{
		tfp->close();
		delete tfp;
	}

	delete uut;
	return 0;

}

#define CASES 19

void excute_instr(){
		int randCase = rand()%CASES;
		int reg = rand()%32;
		int reg2 = rand()%32;
		int reg3 = rand()%32;
		int value = rand()%4096;
		int shamt = rand()%32;
		int value20 = rand()%1048576;
		int svalue = value - 2048;
		uint32_t cmd;

		switch (randCase){
			case 0:cmd =   ori(reg,reg2,svalue); SimRISCV::ori(reg,reg2,svalue); break;
			case 1:cmd =  andi(reg,reg2,svalue); SimRISCV::andi(reg,reg2,svalue); break;
			case 2:cmd =  addi(reg,reg2,svalue); SimRISCV::addi(reg,reg2,svalue); break;
			case 3:cmd =  xori(reg,reg2,svalue); SimRISCV::xori(reg,reg2,svalue); break;
			case 4:cmd =  slti(reg,reg2,svalue); SimRISCV::slti(reg,reg2,svalue); break;
			case 5:cmd =  sltiu(reg,reg2,svalue); SimRISCV::sltiu(reg,reg2,svalue); break;
			case 6:cmd =  lui(reg,value20); SimRISCV::lui(reg,value20); break;
			case 7:cmd =  auipc(reg,value20); SimRISCV::auipc(reg,value20); break;
			case 8:cmd =  slli(reg,reg2,shamt); SimRISCV::slli(reg,reg2,shamt); break;
			case 9:cmd =  srli(reg,reg2,shamt); SimRISCV::srli(reg,reg2,shamt); break;
			case 10:cmd =  srai(reg,reg2,shamt); SimRISCV::srai(reg,reg2,shamt); break;
			case 11:cmd =  add(reg,reg2,reg3); SimRISCV::add(reg,reg2,reg3); break;
			case 12:cmd =  sub(reg,reg2,reg3); SimRISCV::sub(reg,reg2,reg3); break;
			case 13:cmd =  sll(reg,reg2,reg3); SimRISCV::sll(reg,reg2,reg3); break;
			case 14:cmd =  srl(reg,reg2,reg3); SimRISCV::srl(reg,reg2,reg3); break;
			case 15:cmd =  sra(reg,reg2,reg3); SimRISCV::sra(reg,reg2,reg3); break;
			case 16:cmd =  andr(reg,reg2,reg3); SimRISCV::andr(reg,reg2,reg3); break;
			case 17:cmd =  orr(reg,reg2,reg3); SimRISCV::orr(reg,reg2,reg3); break;
			case 18:cmd =  xorr(reg,reg2,reg3); SimRISCV::xorr(reg,reg2,reg3); break;
		}
		uut->INST = cmd;
		

		if (tfp != NULL)
			tfp->dump(main_time);
		uut->CLOCK = uut->CLOCK ? 0 : 1;
		uut->eval();
		main_time++;


		if (tfp != NULL)
			tfp->dump(main_time);
		uut->CLOCK = uut->CLOCK ? 0 : 1;
		uut->eval();
		main_time++;

		
		
}