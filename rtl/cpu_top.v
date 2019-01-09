module cpu_top (input logic CLOCK,
			input typePack::instruction_t INST,
			input  logic [31:0] read_data,
			output logic write_en,
			output logic read_en,
			output logic [3:0] byte_en,
			output logic [31:0] write_data,
			output logic [31:0] addr,
			output logic[31:0] PC);

	logic[31:0] sign_extendded_imm;
	logic[31:0] sign_pc_imm;
	logic[31:0] sign_extendded_bimm;
	logic[31:0] sign_extendded_simm;
	assign sign_extendded_imm =  { {20{INST.itype.imm [11]}}, INST.itype.imm [11:0] };
	assign sign_extendded_bimm =  { {20{INST.btype.imm12}}, INST.btype.imm11, INST.btype.imm10_5, INST.btype.imm4_1,1'b0 };
	assign sign_extendded_simm =  { {20{INST.stype.imm11_5[11]}}, INST.stype.imm11_5, INST.stype.imm4_0 };
	assign sign_pc_imm = { {12{INST.jtype.imm20}}, INST.jtype.imm19_12 , INST.jtype.imm11, INST.jtype.imm10_1, 1'b0 };
	reg[31:0] GPREGS[31:0];
	initial PC = 32'h80000000;

	always_ff @(posedge CLOCK) begin
		PC <= PC +4;
		write_en <= 0;
		read_en <= 0;
		byte_en <= 0;
		write_data <= 0;
		addr <= 0;
		unique case(INST.itype.opcode)
			typePack::LUI :
				GPREGS[INST.utype.rd] <= {INST.utype.imm,{12{1'b0}}};
			typePack::AUIPC :
				GPREGS[INST.utype.rd] <= {INST.utype.imm,{12{1'b0}}} + PC;
			typePack::JAL : begin
				GPREGS[INST.utype.rd] <= 4 + PC;
				PC <= PC + sign_pc_imm;
			end
			typePack::JALR : begin
				GPREGS[INST.itype.rd] <= 4 + PC;
				PC <= (GPREGS[INST.itype.rs1] + sign_extendded_imm) & 32'hFFFFFFFE;
			end
			typePack::BRANCH :
				unique case(INST.btype.funct3)
					typePack::BEQ :
						if(GPREGS[INST.btype.rs1]==GPREGS[INST.btype.rs2])
							PC <= PC + sign_extendded_bimm;
					typePack::BNE :
						if(GPREGS[INST.btype.rs1]!=GPREGS[INST.btype.rs2])
							PC <= PC + sign_extendded_bimm;
					typePack::BLT :
						if($signed(GPREGS[INST.btype.rs1])<$signed(GPREGS[INST.btype.rs2]))
							PC <= PC + sign_extendded_bimm;
					typePack::BLTU :
						if(GPREGS[INST.btype.rs1]<GPREGS[INST.btype.rs2])
							PC <= PC + sign_extendded_bimm;
					typePack::BGE :
						if($signed(GPREGS[INST.btype.rs1])>=$signed(GPREGS[INST.btype.rs2]))
							PC <= PC + sign_extendded_bimm;
					typePack::BGEU :
						if(GPREGS[INST.btype.rs1]>=GPREGS[INST.btype.rs2])
							PC <= PC + sign_extendded_bimm;
				endcase
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
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs2] ^ GPREGS[INST.rtype.rs1];
					typePack::SLT :
						GPREGS[INST.rtype.rd] <= $signed(GPREGS[INST.rtype.rs2]) > $signed(GPREGS[INST.rtype.rs1]);
					typePack::SLTU :
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs2] > GPREGS[INST.rtype.rs1];
					typePack::SLL :
						GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs1] << GPREGS[INST.rtype.rs2];
					typePack::SRL :
						if (INST.rtype.funct7[5] == 1)
							GPREGS[INST.rtype.rd] <= $signed(GPREGS[INST.rtype.rs1]) >>> GPREGS[INST.rtype.rs2];
						else
							GPREGS[INST.rtype.rd] <= GPREGS[INST.rtype.rs1] >>  GPREGS[INST.rtype.rs2];
				endcase
			typePack::S :
			begin
				write_en <= 1;
				write_data <= GPREGS[INST.stype.rs2];
				addr <= GPREGS[INST.stype.rs1]+sign_extendded_simm;
				unique case(INST.stype.funct3)
					typePack::SWORD :
						byte_en <= 4'b1111;
					typePack::SSHORT :
						byte_en <= 4'b0011;
					typePack::SBYTE :
						byte_en <= 4'b0001;
				endcase
			end
			typePack::L :
			begin
				addr <= GPREGS[INST.itype.rs1]+sign_extendded_imm;
				read_en <= 1;
				unique case (INST.itype.funct3)
					typePack::LBYTE :
						byte_en <= 4'b0001;
					typePack::LSHORT :
						byte_en <= 4'b0011;
					typePack::LWORD :
						byte_en <= 4'b1111;
					typePack::LUBYTE :
						byte_en <= 4'b0001;
					typePack::LUSHORT :
						byte_en <= 4'b0011;
				endcase
			end
			default :
				GPREGS[1] <= 0;
		endcase
		GPREGS[0] <= 0;
	end

	always_ff @(negedge CLOCK) begin
		unique case(INST.itype.opcode)
			typePack::L :
			begin
				unique case (INST.itype.funct3)
					typePack::LBYTE :
						GPREGS[INST.itype.rd] <=  { {24{read_data [7]}}, read_data [7:0] };
					typePack::LSHORT :
						GPREGS[INST.itype.rd] <=  { {16{read_data [15]}}, read_data [15:0] };
					typePack::LWORD :
						GPREGS[INST.itype.rd] <=   read_data;
					typePack::LUBYTE :
						GPREGS[INST.itype.rd] <=  { {24{1'b0}}, read_data [7:0] };
					typePack::LUSHORT :
						GPREGS[INST.itype.rd] <=  { {16{1'b0}}, read_data [15:0] };
				endcase
			end
		endcase
	GPREGS[0] <= 0;
	end
endmodule

