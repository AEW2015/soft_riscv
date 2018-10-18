module cpu_top (input logic CLOCK,
			input typePack::instruction_t INST,
			output reg[31:0] PC);


	reg[31:0] GPREGS[31:0];
	logic [6:0] test;
	assign test = INST.itype.opcode;
	always_ff @(posedge CLOCK) begin
		PC <= PC +4;
	end

	always_ff @(posedge CLOCK) begin
		unique case(INST.itype.opcode)
			typePack::IMM:
				unique case(INST.itype.funct3)
					typePack::ORI:
						GPREGS[INST.itype.rd] = INST.itype.imm | GPREGS[INST.itype.rs1];
						//do nothing
				endcase
			typePack::OMM:
				GPREGS[1] <= 0;
			default:
				GPREGS[1] <= 0;
		endcase

	end



endmodule

