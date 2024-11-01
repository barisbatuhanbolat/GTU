module control_unit (
	  input [5:0] opcode,
	  output reg [2:0] ALUop,
	  output regDst, branch, memRead, ALUsrc, memWrite, regWrite, jump, move
);
	  wire [12:0] instr_type;
	  dec13 dec (.in(opcode), .out(instr_type));

	  or regDstOr(regDst,instr_type[0]);
	  or branchOr(branch,instr_type[10]);
	  or memReadOr(memRead,instr_type[5],instr_type[7]);
	  or ALUsrcOr(ALUsrc,instr_type[1],instr_type[2],instr_type[3],instr_type[4],instr_type[5],instr_type[6],instr_type[7],instr_type[8],instr_type[9],instr_type[12]); 
	  or memWriteOr(memWrite,instr_type[6], instr_type[8]);
	  or regWriteOr(regWrite,instr_type[0],instr_type[1],instr_type[2],instr_type[3],instr_type[4],instr_type[5],instr_type[7],instr_type[9],instr_type[12]);
	  or jumpOr(jump,instr_type[11]);
	  or moveOr(move,instr_type[12]);
	  
    parameter R_TYPE = 6'b000000;
    parameter ADDI = 6'b000010;
    parameter SUBTRI = 6'b000011;
    parameter ANDI = 6'b000100;
    parameter ORI = 6'b000101;
    parameter LW = 6'b001000;
    parameter SW = 6'b010000;
    parameter LB = 6'b001001;
    parameter SB = 6'b010001;
    parameter SLTI = 6'b000111;
    parameter BEQ = 6'b100011;
    parameter JUMP = 6'b111000;
    parameter JAL = 6'b111001;
    parameter MOVE = 6'b100000;

    always @* begin
        ALUop = 3'b000;
        if (opcode == R_TYPE)      ALUop = 3'b111;
        else if (opcode == ADDI)   ALUop = 3'b101;
        else if (opcode == SUBTRI) ALUop = 3'b110;
        else if (opcode == ANDI)   ALUop = 3'b000;
        else if (opcode == ORI)    ALUop = 3'b001;
        else if (opcode == LW)     ALUop = 3'b101;
        else if (opcode == SW)     ALUop = 3'b101;
        else if (opcode == LB)     ALUop = 3'b101;
        else if (opcode == SB)     ALUop = 3'b101;
        else if (opcode == SLTI)   ALUop = 3'b100;
        else if (opcode == BEQ)    ALUop = 3'b110;
        else if (opcode == JUMP || opcode == JAL) ALUop = 3'bXXX;
        else if (opcode == MOVE)   ALUop = 3'b101;
    end

endmodule

module dec13 (
	  input [5:0] in,
	  output [12:0] out
);
  	  and and1(out[0],~in[5],~in[4],~in[3],~in[2],~in[1],~in[0]);
	  
	  and and2(out[1],~in[5],~in[4],~in[3],~in[2],in[1],~in[0]);
	  
	  and and3(out[2],~in[5],~in[4],~in[3],~in[2],in[1],in[0]);
	  
	  and and4(out[3],~in[5],~in[4],~in[3],in[2],~in[1],~in[0]);
	  
	  and and5(out[4],~in[5],~in[4],~in[3],in[2],~in[1],in[0]);
	  
	  and and6(out[5],~in[5],~in[4],in[3],~in[2],~in[1],~in[0]);
	  
	  and and7(out[6],~in[5],in[4],~in[3],~in[2],~in[1],~in[0]);
	  
	  and and8(out[7],~in[5],~in[4],in[3],~in[2],~in[1],in[0]);
	  
	  and and9(out[8],~in[5],in[4],~in[3],~in[2],~in[1],in[0]);
	  
	  and and10(out[9],~in[5],~in[4],~in[3],in[2],in[1],in[0]);
	  
	  and and11(out[10],in[5],~in[4],~in[3],~in[2],in[1],in[0]);
	  
	  and and12(out[11],in[5],in[4],in[3],~in[2],~in[1],~in[0]);
	  
	  and and13(out[12],in[5],~in[4],~in[3],~in[2],~in[1],~in[0]);

endmodule
