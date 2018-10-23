module cpu_top (input logic CLOCK,
			input typePack::instruction_t INST,
			output reg[31:0] PC);

	logic[31:0] sign_extendded_imm;
	assign sign_extendded_imm =  { {20{INST.itype.imm [11]}}, INST.itype.imm [11:0] };
	reg[31:0] GPREGS[31:0];


	always_ff @(posedge CLOCK) begin
		PC <= PC +4;
		unique case(INST.itype.opcode)
			typePack::LUI :
				GPREGS[INST.utype.rd] <= {INST.utype.imm,{12{1'b0}}};
			typePack::AUIPC :
				GPREGS[INST.utype.rd] <= {INST.utype.imm,{12{1'b0}}} + PC;
			typePack::IMM :
				unique case(INST.itype.funct3)
					typePack::OR :
						GPREGS[INST.itype.rd] <= sign_extendded_imm | GPREGS[INST.itype.rs1];
					typePack::AND :
						GPREGS[INST.itype.rd] <= sign_extendded_imm & GPREGS[INST.itype.rs1];
					typePack::ADD :
						GPREGS[INST.itype.rd] <= sign_extendded_imm + GPREGS[INST.itype.rs1];
					typePack::XOR :
						GPREGS[INST.itype.rd] <= sign_extendded_imm ^ GPREGS[INST.itype.rs1];
					typePack::SLT :
						GPREGS[INST.itype.rd] <= $signed(sign_extendded_imm) > $signed(GPREGS[INST.itype.rs1]);
					typePack::SLTU :
						GPREGS[INST.itype.rd] <= sign_extendded_imm > GPREGS[INST.itype.rs1];
					typePack::SLL :
						GPREGS[INST.itype.rd] <= GPREGS[INST.itype.rs1] << INST.itype.imm[4:0];
					typePack::SRL :
						if (INST.itype.imm[10] == 1)
							GPREGS[INST.itype.rd] <= $signed(GPREGS[INST.itype.rs1]) >>> INST.itype.imm[4:0];
						else
							GPREGS[INST.itype.rd] <= GPREGS[INST.itype.rs1] >> INST.itype.imm[4:0];
				endcase
			typePack::OP :
				unique case(INST.rtype.funct3)
					typePack::OR :
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs2] | GPREGS[INST.rtype.rs1];
					typePack::AND :
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs2] & GPREGS[INST.rtype.rs1];
					typePack::ADD :
						if (INST.rtype.funct7[5] == 1)
							GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs1] - GPREGS[INST.rtype.rs2];
						else
							GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs2] + GPREGS[INST.rtype.rs1];
					typePack::XOR :
						GPREGS[INST.itype.rd] <= sign_extendded_imm ^ GPREGS[INST.itype.rs1];
					typePack::SLT :
						GPREGS[INST.rtype.rd] <= $signed(sign_extendded_imm) > $signed(GPREGS[INST.itype.rs1]);
					typePack::SLTU :
						GPREGS[INST.itype.rd] <= sign_extendded_imm > GPREGS[INST.itype.rs1];
					typePack::SLL :
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs1] << GPREGS[INST.rtype.rs2];
					typePack::SRL :
						if (INST.rtype.funct7[5] == 1)
							GPREGS[INST.rtype.rd] <= $signed(GPREGS[INST.rtype.rs1]) >>> GPREGS[INST.rtype.rs2];
						else
							GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs1] >>  GPREGS[INST.rtype.rs2];
				endcase
			typePack::OMM :
				GPREGS[1] <= 0;
			default :
				GPREGS[1] <= 0;
		endcase
		GPREGS[0] <= 0;
	end



endmodule

