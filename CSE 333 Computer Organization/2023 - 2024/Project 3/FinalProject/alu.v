module alu(
		input [31:0] alu_src1, alu_src2,
		input [2:0] alu_ctr,
      output zero_bit,
		output [31:0] result
);		
		wire [31:0] and_result, or_result, xor_result, nor_result, add_result, sub_result, mod_result;
		wire borrow,less_than;
		
		ALUand and_inst(alu_src1,alu_src2,and_result);
		ALUor or_inst(alu_src1,alu_src2,or_result);
		ALUxor xor_inst(alu_src1,alu_src2,xor_result);
		ALUnor nor_inst(alu_src1,alu_src2,nor_result);
		ALUless_than less(alu_src1,alu_src2,less_than);
		adder add_inst(alu_src1,alu_src2,0,add_result,borrow);
		subtractor sub_inst(alu_src1,alu_src2,sub_result,borrow);
		adder temp(alu_src1,alu_src2,0,mod_result,borrow);
		
		and zeros(zero_bit,sub_result[0],sub_result[1],sub_result[2],sub_result[3],sub_result[4],sub_result[5],sub_result[6],sub_result[7],sub_result[8],sub_result[9],sub_result[10],sub_result[11],sub_result[12],sub_result[13],sub_result[14],sub_result[15],sub_result[16],sub_result[17],sub_result[18],sub_result[19],sub_result[20],sub_result[21],sub_result[22],sub_result[23],sub_result[24],sub_result[25],sub_result[26],sub_result[27],sub_result[28],sub_result[29],sub_result[30],sub_result[31]);
		

		_8x1Mux mux0 (result[0], and_result[0], or_result[0], xor_result[0], nor_result[0], less_than, add_result[0], sub_result[0], mod_result[0], alu_ctr);
		_8x1Mux mux1 (result[1], and_result[1], or_result[1], xor_result[1], nor_result[1], less_than, add_result[1], sub_result[1], mod_result[1], alu_ctr);
		_8x1Mux mux2 (result[2], and_result[2], or_result[2], xor_result[2], nor_result[2], less_than, add_result[2], sub_result[2], mod_result[2], alu_ctr);
		_8x1Mux mux3 (result[3], and_result[3], or_result[3], xor_result[3], nor_result[3], less_than, add_result[3], sub_result[3], mod_result[3], alu_ctr);
		_8x1Mux mux4 (result[4], and_result[4], or_result[4], xor_result[4], nor_result[4], less_than, add_result[4], sub_result[4], mod_result[4], alu_ctr);
		_8x1Mux mux5 (result[5], and_result[5], or_result[5], xor_result[5], nor_result[5], less_than, add_result[5], sub_result[5], mod_result[5], alu_ctr);
		_8x1Mux mux6 (result[6], and_result[6], or_result[6], xor_result[6], nor_result[6], less_than, add_result[6], sub_result[6], mod_result[6], alu_ctr);
		_8x1Mux mux7 (result[7], and_result[7], or_result[7], xor_result[7], nor_result[7], less_than, add_result[7], sub_result[7], mod_result[7], alu_ctr);
		_8x1Mux mux8 (result[8], and_result[8], or_result[8], xor_result[8], nor_result[8], less_than, add_result[8], sub_result[8], mod_result[8], alu_ctr);
		_8x1Mux mux9 (result[9], and_result[9], or_result[9], xor_result[9], nor_result[9], less_than, add_result[9], sub_result[9], mod_result[9], alu_ctr);
		_8x1Mux mux10 (result[10], and_result[10], or_result[10], xor_result[10], nor_result[10], less_than, add_result[10], sub_result[10], mod_result[10], alu_ctr);
		_8x1Mux mux11 (result[11], and_result[11], or_result[11], xor_result[11], nor_result[11], less_than, add_result[11], sub_result[11], mod_result[11], alu_ctr);
		_8x1Mux mux12 (result[12], and_result[12], or_result[12], xor_result[12], nor_result[12], less_than, add_result[12], sub_result[12], mod_result[12], alu_ctr);
		_8x1Mux mux13 (result[13], and_result[13], or_result[13], xor_result[13], nor_result[13], less_than, add_result[13], sub_result[13], mod_result[13], alu_ctr);
		_8x1Mux mux14 (result[14], and_result[14], or_result[14], xor_result[14], nor_result[14], less_than, add_result[14], sub_result[14], mod_result[14], alu_ctr);
		_8x1Mux mux15 (result[15], and_result[15], or_result[15], xor_result[15], nor_result[15], less_than, add_result[15], sub_result[15], mod_result[15], alu_ctr);
		_8x1Mux mux16 (result[16], and_result[16], or_result[16], xor_result[16], nor_result[16], less_than, add_result[16], sub_result[16], mod_result[16], alu_ctr);
		_8x1Mux mux17 (result[17], and_result[17], or_result[17], xor_result[17], nor_result[17], less_than, add_result[17], sub_result[17], mod_result[17], alu_ctr);
		_8x1Mux mux18 (result[18], and_result[18], or_result[18], xor_result[18], nor_result[18], less_than, add_result[18], sub_result[18], mod_result[18], alu_ctr);
		_8x1Mux mux19 (result[19], and_result[19], or_result[19], xor_result[19], nor_result[19], less_than, add_result[19], sub_result[19], mod_result[19], alu_ctr);
		_8x1Mux mux20 (result[20], and_result[20], or_result[20], xor_result[20], nor_result[20], less_than, add_result[20], sub_result[20], mod_result[20], alu_ctr);
		_8x1Mux mux21 (result[21], and_result[21], or_result[21], xor_result[21], nor_result[21], less_than, add_result[21], sub_result[21], mod_result[21], alu_ctr);
		_8x1Mux mux22 (result[22], and_result[22], or_result[22], xor_result[22], nor_result[22], less_than, add_result[22], sub_result[22], mod_result[22], alu_ctr);
		_8x1Mux mux23 (result[23], and_result[23], or_result[23], xor_result[23], nor_result[23], less_than, add_result[23], sub_result[23], mod_result[23], alu_ctr);
		_8x1Mux mux24 (result[24], and_result[24], or_result[24], xor_result[24], nor_result[24], less_than, add_result[24], sub_result[24], mod_result[24], alu_ctr);
		_8x1Mux mux25 (result[25], and_result[25], or_result[25], xor_result[25], nor_result[25], less_than, add_result[25], sub_result[25], mod_result[25], alu_ctr);
		_8x1Mux mux26 (result[26], and_result[26], or_result[26], xor_result[26], nor_result[26], less_than, add_result[26], sub_result[26], mod_result[26], alu_ctr);
		_8x1Mux mux27 (result[27], and_result[27], or_result[27], xor_result[27], nor_result[27], less_than, add_result[27], sub_result[27], mod_result[27], alu_ctr);
		_8x1Mux mux28 (result[28], and_result[28], or_result[28], xor_result[28], nor_result[28], less_than, add_result[28], sub_result[28], mod_result[28], alu_ctr);
		_8x1Mux mux29 (result[29], and_result[29], or_result[29], xor_result[29], nor_result[29], less_than, add_result[29], sub_result[29], mod_result[29], alu_ctr);
		_8x1Mux mux30 (result[30], and_result[30], or_result[30], xor_result[30], nor_result[30], less_than, add_result[30], sub_result[30], mod_result[30], alu_ctr);
		_8x1Mux mux31 (result[31], and_result[31], or_result[31], xor_result[31], nor_result[31], less_than, add_result[31], sub_result[31], mod_result[31], alu_ctr);


endmodule