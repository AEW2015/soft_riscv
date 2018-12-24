package typePack;

typedef enum logic[6:0]{
	LUI = 7'b0110111,
	JAL = 7'b1101111,
	JALR = 7'b1100111,
	AUIPC = 7'b0010111,
	IMM = 7'b0010011,
	BRANCH = 7'b1100011,
	OP = 7'b0110011,
	S = 7'b0100011,
	L = 7'b0000011
}
opcodes /* verilator public */;

typedef enum logic[2:0]{
	ADD = 3'b000,
	SLT = 3'b010,
	SLTU = 3'b011,
	SLL = 3'b001,
	SRL = 3'b101,
	XOR = 3'b100,
	OR = 3'b110,
	AND = 3'b111
} FIMM  /* verilator public */;

typedef enum logic[2:0]{
	BEQ = 3'b000,
	BNE = 3'b001,
	BGE = 3'b101,
	BGEU = 3'b111,
	BLTU = 3'b110,
	BLT = 3'b100
} BIMM  /* verilator public */;

typedef enum logic[2:0]{
	SBYTE = 3'b000,
	SSHORT = 3'b001,
	SWORD = 3'b010
} SIMM  /* verilator public */;

typedef enum logic[2:0]{
	LBYTE = 3'b000,
	LSHORT = 3'b001,
	LWORD = 3'b010,
	LUBYTE = 3'b100,
	LUSHORT = 3'b101
} LIMM  /* verilator public */;

localparam ASUB = 7'b0100000;



typedef struct packed
{
	logic[11:5] imm11_5;
	logic [4:0] rs2;
	logic [4:0] rs1;
	logic [2:0] funct3;
	logic [4:0] imm4_0;
	opcodes opcode;


} STYPE_T  /* verilator public */;
typedef struct packed
{
	logic[11:0] imm;
	logic [4:0] rs1;
	logic [2:0] funct3;
	logic [4:0] rd;
	opcodes opcode;


} ITYPE_T  /* verilator public */;
typedef struct packed
{
	logic [6:0] funct7;
	logic [4:0] rs2;
	logic [4:0] rs1;
	logic [2:0] funct3;
	logic [4:0] rd;
	opcodes opcode;


} RTYPE_T  /* verilator public */;
typedef struct packed
{
	logic[19:0] imm;
	logic [4:0] rd;
	opcodes opcode;


} UTYPE_T  /* verilator public */;
typedef struct packed
{
	logic imm20;
	logic [10:1] imm10_1;
	logic imm11;
	logic [19:12] imm19_12;
	logic [4:0] rd;
	opcodes opcode;


} JTYPE_T  /* verilator public */;
typedef struct packed
{
	logic imm12;
	logic [10:5] imm10_5;
	logic [4:0] rs2;
	logic [4:0] rs1;
	logic [2:0] funct3;
	logic [4:1] imm4_1;
	logic imm11;
	opcodes opcode;


} BTYPE_T  /* verilator public */;

typedef union packed
{
  ITYPE_T itype;
  STYPE_T stype;
  RTYPE_T rtype;
  UTYPE_T utype;
  JTYPE_T jtype;
  BTYPE_T btype;
} instruction_t /* verilator public */;


endpackage : typePack