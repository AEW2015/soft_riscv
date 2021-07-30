#include <verilated.h>
#include "cpu.h"
#include "cpu_typePack.h"
#include "verilated_vcd_c.h"
#include "simriscv.h"
#include <iostream>
#include <fstream>
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

long unsigned timer = 0;
int timer_ctl = 0;

void test_instr();
void excute_instr();
#define ASIZE 0x1000000
static int instructionM [ASIZE];
//static int dataM [2];
static bool done_flag = 0;

int main (int argc, char** argv)
{
	bool vcdTrace = false;
	tfp = NULL;
	int pflag = 0;
	long long maxcycles = 1000000;
	int c;
	  while ((c = getopt (argc, argv, "pl:")) != -1)
		switch (c)
		{
		case 'p':
			pflag = 1;
			break;
		case 'l':
			maxcycles = std::stoll(optarg);
			break;
		case '?':
			if (optopt == 'l')
			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
			fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
			fprintf (stderr,
					"Unknown option character `\\x%x'.\n",
					optopt);
			return 1;
		default:
			abort ();
      }

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

	// instructionM[0] = 0x00108093;//lbu(1,0,0);
	// instructionM[1] = 0x001080b3;//sw(0,1,4);
	// instructionM[2] = 0x00102023;
	// instructionM[3] = 0x00002083;

	// instructionM[0] = 0x800007b7;//lbu(1,0,0);
	// instructionM[1] = 0x03200713;//sw(0,1,4);
	// instructionM[2] = 0x02e7ae23;

	// instructionM[3] = 0x100007b7;//lbu(1,0,0);
	// instructionM[4] = 0x03100713;//sw(0,1,4);
	// instructionM[5] = 0x00e7a023;

	// instructionM[6] = 0x100007b7;//lbu(1,0,0);
	// instructionM[7] = 0x03000713;//sw(0,1,4);
	// instructionM[8] = 0x00e7a023;

	// instructionM[9] = 0x200007b7;//lbu(1,0,0);
	// instructionM[10] = 0x03000713;//sw(0,1,4);
	// instructionM[11] = 0x00e7a023;

	if(pflag){
		std::ifstream ifs("test.mem");

		std::string line;
		int index = 0;
		while(std::getline(ifs, line))
		{
			std::istringstream iss(line.c_str());
			unsigned int a,b;
			iss >>  std::hex >>  a;
			instructionM[index++]=a;
		}

	}

	for(long long cycle = 1;cycle<maxcycles;cycle++)
	{

		if(pflag){
			excute_instr();
			if(done_flag){
				printf("cycles : %llu",cycle);
				printf("\nExit\n");
				break;
			}
		}
		else{
			test_instr();
			std::stringstream str;
			if(SimRISCV::score(uut,str)){
				std::cout << "Errors @" <<  sc_time_stamp() << std::endl << str.str() << std::endl;
				break;
			}
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


	if(pflag&!done_flag){
	 printf("program did not finish\n");
	}


	if(tfp != NULL)
	{
		tfp->close();
		delete tfp;
	}

	delete uut;
	return 0;

}

#define CASES 37
void excute_instr(){

		if((timer_ctl&0x80) == 0x80){
			timer  = timer + 1;
		}
		
		uut->read_data = 0xFF;
		int cmd = instructionM[((unsigned)uut->PC>>2)%ASIZE];
		//printf("0x%08X := 0X%08X\n",((unsigned)uut->PC),cmd);
		//printf("%d\n",((unsigned)uut->PC>>2)%ASIZE);
		//printf("0x%08X\n",cmd);
		//printf("0x%08X\n",uut->cpu_top__DOT__GPREGS[0]);
		//printf("0x%08X\n",uut->cpu_top__DOT__GPREGS[1]);
		//printf("0x%08X\n",uut->cpu_top__DOT__GPREGS[2]);
		//printf("0x%08X\n",instructionM[0x3b6c]);
		//getchar();
		uut->INST = cmd;
		uut->eval();
		
		if(uut->write_en){
			//Uart 
			if(uut->addr == 0x10000004){
				char output = (char) (unsigned) uut->write_data;
				printf("%c",output);
			}
			else if(uut->addr == 0x10010000){
				timer_ctl = (int) (unsigned) uut->write_data;
			}
			else if(uut->addr == 0x10010004){
				timer = (long) (unsigned) uut->write_data;
			}
			else if(uut->addr == 0x10010014){
				timer = (long) (unsigned) uut->write_data;
			}
			//done flag
			else if(uut->addr == 0x20000000){
				done_flag = 1;
			}
			else{
			unsigned int tmp_data = instructionM[((unsigned)uut->addr>>2)%ASIZE];
			int tmp_write= uut->write_data;
			if(uut->byte_en==0xF)
			instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;
			else if(uut->byte_en==0x3){
				if(uut->addr%4==0){
					tmp_data = tmp_data & 0xFFFF0000;
					tmp_write = tmp_write & 0xFFFF;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;
				}else{
					tmp_data = tmp_data & 0xFFFF;
					tmp_write = (tmp_write & 0xFFFF)<<16;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;	
				}
			}else{
				if(uut->addr%4==0){
					tmp_data = tmp_data & 0xFFFFFF00;
					tmp_write = tmp_write & 0xFF;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;

				}else if(uut->addr%4==1){
					tmp_data = tmp_data & 0xFFFF00FF;
					tmp_write = (tmp_write & 0xFF)<<8;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;

				}else if(uut->addr%4==2){
					tmp_data = tmp_data & 0xFF00FFFF;
					tmp_write = (tmp_write & 0xFF)<<16;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;

				}else{
					tmp_data = tmp_data & 0xFFFFFF;
					tmp_write = (tmp_write & 0xFF)<<24;
					tmp_write = tmp_data | tmp_write;
					instructionM[((unsigned)uut->addr>>2)%ASIZE] = tmp_write;
				}


			}

			}

			
		}
		
		//printf("0x%08X\n\r",instructionM[15]);

		if (tfp != NULL)
			tfp->dump(main_time);
		uut->CLOCK = uut->CLOCK ? 0 : 1;
		uut->eval();
		main_time++;

		//check for read
		if(uut->read_en){
			
			if(uut->addr == 0x10000008){
				uut->read_data = 0x0;
			}
			else if(uut->addr == 0x10010008){
				uut->read_data = timer & 0xFFFFFFFF;
			}
			else if(uut->addr == 0x10010018){
				uut->read_data = timer >> 32;
			}else
			{
				
			int tmp_data = instructionM[((unsigned)uut->addr>>2)%ASIZE];
			if(uut->byte_en==0xF)
			uut->read_data = tmp_data;
			else if(uut->byte_en==0x3){
				if(uut->addr%4==0){
					tmp_data = tmp_data & 0xFFFF;
					uut->read_data = tmp_data;
				}else{
					tmp_data = (tmp_data & 0xFFFF0000)>>16;
					uut->read_data = tmp_data;	
				}
			}else{
				if(uut->addr%4==0){
					tmp_data = tmp_data & 0xFF;
					uut->read_data = tmp_data;

				}else if(uut->addr%4==1){
					tmp_data = (tmp_data & 0xFF00)>>8;
					uut->read_data = tmp_data;	

				}else if(uut->addr%4==2){
					tmp_data = (tmp_data & 0xFF0000)>>16;
					uut->read_data = tmp_data;	

				}else{
					tmp_data = (tmp_data & 0xFF000000)>>24;
					uut->read_data = tmp_data;	
				}


			}
			}
			
		}


		if (tfp != NULL)
			tfp->dump(main_time);
		uut->CLOCK = uut->CLOCK ? 0 : 1;
		uut->eval();
		main_time++;

		
		
}
void test_instr(){
		int randCase = rand()%CASES;
		int reg = rand()%32;
		int reg2 = rand()%32;
		int reg3 = rand()%32;
		int read_data = rand();
		int value = rand()%4096;
		int shamt = rand()%32;
		int value20 = rand()%1048576 - (1048576/2);
		int svalue = value - 2048;
		uint32_t cmd;
		uint32_t testv = 0x800;
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
			case 19:cmd =  slt(reg,reg2,reg3); SimRISCV::slt(reg,reg2,reg3); break;
			case 20:cmd =  sltu(reg,reg2,reg3); SimRISCV::sltu(reg,reg2,reg3); break;
			case 21:cmd =  jal(reg,value20); SimRISCV::jal(reg,value20); break;
			case 22:cmd =  jalr(reg,reg2,svalue); SimRISCV::jalr(reg,reg2,svalue); break;
			case 23:cmd =  beq(reg,reg2,svalue); SimRISCV::beq(reg,reg2,svalue); break;
			case 24:cmd =  bne(reg,reg2,svalue); SimRISCV::bne(reg,reg2,svalue); break;
			case 25:cmd =  blt(reg,reg2,svalue); SimRISCV::blt(reg,reg2,svalue); break;
			case 26:cmd =  bge(reg,reg2,svalue); SimRISCV::bge(reg,reg2,svalue); break;
			case 27:cmd =  bltu(reg,reg2,svalue); SimRISCV::bltu(reg,reg2,svalue); break;
			case 28:cmd =  bgeu(reg,reg2,svalue); SimRISCV::bgeu(reg,reg2,svalue); break;
			case 29:cmd =  sw(reg,reg2,svalue); SimRISCV::sw(reg,reg2,svalue); break;
			case 30:cmd =  sh(reg,reg2,svalue); SimRISCV::sh(reg,reg2,svalue); break;
			case 31:cmd =  sb(reg,reg2,svalue); SimRISCV::sb(reg,reg2,svalue); break;
			case 32:cmd =  lb(reg,reg2,svalue); SimRISCV::lb(reg,reg2,svalue,read_data); break;
			case 33:cmd =  lh(reg,reg2,svalue); SimRISCV::lh(reg,reg2,svalue,read_data); break;
			case 34:cmd =  lw(reg,reg2,svalue); SimRISCV::lw(reg,reg2,svalue,read_data); break;
			case 35:cmd =  lbu(reg,reg2,svalue); SimRISCV::lbu(reg,reg2,svalue,read_data); break;
			case 36:cmd =  lhu(reg,reg2,svalue); SimRISCV::lhu(reg,reg2,svalue,read_data); break;
		}
		uut->read_data = read_data;
		uut->INST = cmd;
		uut->eval();
		

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