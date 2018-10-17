#include <verilated.h>
#include "cpu.h"
#include "cpu_typePack.h"
#include "verilated_vcd_c.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "inst.h"

cpu *uut;
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

int main (int argc, char** argv)
{
	bool vcdTrace = true;
	VerilatedVcdC* tfp = NULL;

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

	uut->CLOCK = 0;


	for(int cycle = 1;cycle<1000;cycle++)
	{

		int reg = rand()%32;
		int value = rand()%4096;
		uut->INST =  ori(reg,0,value);

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



		assertSignal(uut->PC,cycle);
		assertSignal(uut->cpu_top__DOT__GPREGS[reg],value);

	}
	uut->final();

	if(tfp != NULL)
	{
		tfp->close();
		delete tfp;
	}

	delete uut;
	return 0;

}
