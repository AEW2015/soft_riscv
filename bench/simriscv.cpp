#include <iostream>
#include "simriscv.h"


SimRISCV::SimRISCV(){
	pc = 0;
	for(uint8_t i = 0;i<32;i++){
		gpregs[i]=0;
	}

}
SimRISCV * SimRISCV::get_sim(){

	static SimRISCV instance;

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

	std::cout << tmp->pc<<std::endl;
	tmp->gpregs[rd] = imm | tmp->gpregs[rs1];
	std::cout << tmp->gpregs[1]<<std::endl;

}
int main () {
	SimRISCV::reset();
	SimRISCV::ori(1,1,1);
	SimRISCV::ori(1,1,2);
	return 0;
}