module mips(
	input clock,
	input [31:0] pc,
	output reg [31:0] updatedPc
);

  wire [31:0] instruction, read_data1, alu_result, read_data, read_data2;
  wire zero_bit, regDst, branch, memRead, memWrite, ALUsrc, regWrite, jump, move;
  wire [2:0] ALUop;
  wire [5:0] opcode, function_code;
  wire [15:0] imm;
  wire [17:0] address;
  
  wire [31:0] sign_ext_imm, shifted_address, alu_src1, alu_src2;
  reg [31:0] write_data;
  wire [2:0] alu_ctr;
  wire [4:0] read_reg1, read_reg2, write_reg;
  wire byteOperations;
  
  register_block reg_block(write_data,read_reg1,read_reg2,write_reg,regWrite,clock,read_data1,read_data2);
  instruction_block inst_block(clock,pc,instruction);
  memory_block mem_block(memWrite,memRead,clock,address,write_data,read_data);
  control_unit ctrl_unit(opcode,ALUop,regDst,branch,memRead,ALUsrc,memWrite,regWrite,jump,move);
  alu alu_unit(alu_src1, alu_src2, alu_ctr,zero_bit, alu_result);
  alu_control alu_ctrl_unit(ALUop,function_code,alu_ctr);
  sign_extend sign_ext_unit(imm,sign_ext_imm);
  shift_left_2 shift_unit(address,shifted_address);
  
  assign opcode = instruction[31:26];
  assign read_reg1 = instruction[25:21];
  assign read_reg2 = instruction[20:16];
  assign write_reg = (regDst == 1) ? instruction[15:11] : instruction[20:16];
  assign function_code = instruction[5:0];
  assign imm = instruction[15:0];
  assign address = instruction[17:0];
  assign alu_src1 = read_data1;
  assign alu_src2 = (ALUsrc == 1) ? sign_ext_imm : read_data2;
  assign byteOperations = 0;
  
    always @(negedge clock) begin
		if(jump) begin
			updatedPc = instruction[25:0];
		end
		else if (branch & zero_bit) begin
			updatedPc = pc + 4 + shifted_address;
		end
		else begin
			updatedPc = pc + 4;
		end
	end
  
  
	reg [31:0] read_data_reg;
	always @(negedge clock) begin 
		if (memRead) begin 
			read_data_reg <= read_data; 
		end 
	end

	always @(negedge clock) begin 
		if (memRead) begin 
			write_data = read_data_reg; 
		end 
		else if (move) begin 
			write_data = read_data1; 
		end 
		else begin 
			write_data = alu_result; 
		end
	end
  
  
endmodule