
#include "simriscv.h"

#include "def.h"
#define V 0
std::stringstream lastCmd;

SimRISCV::SimRISCV(){
	pc = 0;
	for(uint8_t i = 0;i<32;i++){
		gpregs[i]=0;
	}

}
SimRISCV * SimRISCV::get_sim(){

	static SimRISCV instance;
	instance.gpregs[0] = 0;
	return &instance;
}

void SimRISCV::reset(){
	SimRISCV* tmp = get_sim();
	tmp->pc = 0;
	std::cout << tmp->pc<<std::endl;
	for(uint8_t i = 0;i<32;i++){
		tmp->gpregs[i]=0;
	}
}
void SimRISCV::ori(int rd,int rs1,int imm){
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm | tmp->gpregs[rs1];
	lastCmd.str("");
	lastCmd << "ori "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;


}
void SimRISCV::andi(int rd,int rs1,int imm){
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm & tmp->gpregs[rs1];
	lastCmd.str("");
	lastCmd << "andi "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;

}
void SimRISCV::addi(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "addi "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm + tmp->gpregs[rs1];
	

}
void SimRISCV::xori(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "xori "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm ^ tmp->gpregs[rs1];
	

}
void SimRISCV::slti(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "slti "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if(tmp->gpregs[rs1]<imm)
		tmp->gpregs[rd] = 1;
	else
		tmp->gpregs[rd] = 0;
	

}
void SimRISCV::sltiu(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "sltiu "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs1]<(uint32_t)imm)
		tmp->gpregs[rd] = 1;
	else
		tmp->gpregs[rd] = 0;
	

}
void SimRISCV::slli(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "slli "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]<<shamt;
	

}
void SimRISCV::srli(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "srli "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (uint32_t)tmp->gpregs[rs1]>>shamt;
	

}
void SimRISCV::sll(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sll "<< rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] = 0;
	else
	tmp->gpregs[rd] = ((uint32_t)tmp->gpregs[rs1])<<((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::srl(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "srl "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] = 0;
	else
	tmp->gpregs[rd] = ((uint32_t)tmp->gpregs[rs1])>>((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::andr(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "and "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (tmp->gpregs[rs1])&(tmp->gpregs[rs2]);


}
void SimRISCV::sra(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sra "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] =  (tmp->gpregs[rs1])>>(31);
	else
	tmp->gpregs[rd] = (tmp->gpregs[rs1])>>((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::srai(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "srai "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]>>shamt;
	

}
void SimRISCV::add(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "add "<< L2 rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]+tmp->gpregs[rs2];
	

}
void SimRISCV::sub(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sub "<< L2 rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]-tmp->gpregs[rs2];
	

}
void SimRISCV::lui(int rd,int imm){
	lastCmd.str("");
	lastCmd << "lui "<< rd <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm<<12;
	

}
void SimRISCV::auipc(int rd,int imm){
	lastCmd.str("");
	lastCmd << "auipc "<< rd <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->gpregs[rd] = tmp->pc +  (imm<<12);
	tmp->pc += 4;
	
	

}
//return error string
uint32_t SimRISCV::score(cpu* uut,std::stringstream& emesg){
	SimRISCV* tmp = get_sim();
	uint32_t errors = 0;
	emesg << "Last Cmd => " << lastCmd.str() << std::endl;
	emesg << HEX uut->PC<< std::endl;
	if(uut->PC!=tmp->pc){
		//emesg << "Bad PC" << "\n";
		emesg << "Pc = " << HEX uut->PC << " expected = " << HEX tmp->pc << std::endl;
		errors++;
	}
	for(int i = 0;i<32;i++){
		if(uut->cpu_top__DOT__GPREGS[i]!=tmp->gpregs[i]){
			//emesg.append("Bad reg");
			emesg << "GPREG["<< L2 i <<"] = ";
			emesg << HEX uut->cpu_top__DOT__GPREGS[i] << " expected = "<< HEX tmp->gpregs[i] << std::endl;
			errors++;
		}
	}

	return errors;
}