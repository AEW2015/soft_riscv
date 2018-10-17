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