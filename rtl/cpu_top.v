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
					typePack::ORI :
						GPREGS[INST.itype.rd] <= sign_extendded_imm | GPREGS[INST.itype.rs1];
					typePack::ANDI :
						GPREGS[INST.itype.rd] <= sign_extendded_imm & GPREGS[INST.itype.rs1];
					typePack::ADDI :
						GPREGS[INST.itype.rd] <= sign_extendded_imm + GPREGS[INST.itype.rs1];
					typePack::XORI :
						GPREGS[INST.itype.rd] <= sign_extendded_imm ^ GPREGS[INST.itype.rs1];
					typePack::SLTI :
						GPREGS[INST.itype.rd] <= $signed(sign_extendded_imm) > $signed(GPREGS[INST.itype.rs1]);
					typePack::SLTIU :
						GPREGS[INST.itype.rd] <= sign_extendded_imm > GPREGS[INST.itype.rs1];
				endcase
			typePack::OMM :
				GPREGS[1] <= 0;
			default :
				GPREGS[1] <= 0;
		endcase
		GPREGS[0] <= 0;
	end



endmodule

