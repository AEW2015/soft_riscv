package typePack;

typedef enum logic[6:0]{
	LUI = 7'b0110111,
	AUIPC = 7'b0010111,
	IMM = 7'b0010011,
	OMM = 7'b0000011
}
opcodes /* verilator public */;

typedef enum logic[2:0]{
	ADDI = 3'b000,
	SLTI = 3'b010,
	SLTIU = 3'b011,
	XORI = 3'b100,
	ORI = 3'b110,
	ANDI = 3'b111
} FIMM  /* verilator public */;

localparam ASUB = 7'b0100000;



typedef struct packed
{
	logic[11:0] imm;
	logic [4:0] rs1;
	logic [2:0] funct3;
	logic [4:0] rd;
	opcodes opcode;


} ITYPE_T  /* verilator public */;typedef struct packed
{
	logic[19:0] imm;
	logic [4:0] rd;
	opcodes opcode;


} UTYPE_T  /* verilator public */;

typedef union packed
{
  ITYPE_T itype;
  UTYPE_T utype;
} instruction_t /* verilator public */;


endpackage : typePack