module shift_left_2 (
		input [31:0] address, 
		output [31:0] shifted_address
);
	and(shifted_address[0], address[0], 1'b0);
	and(shifted_address[1], address[0], 1'b0);
	or(shifted_address[2], address[0], 1'b0);
	or(shifted_address[3], address[1], 1'b0);
	or(shifted_address[4], address[2], 1'b0);
	or(shifted_address[5], address[3], 1'b0);
	or(shifted_address[6], address[4], 1'b0);
	or(shifted_address[7], address[5], 1'b0);
	or(shifted_address[8], address[6], 1'b0);
	or(shifted_address[9], address[7], 1'b0);
	or(shifted_address[10], address[8], 1'b0);
	or(shifted_address[11], address[9], 1'b0);
	or(shifted_address[12], address[10], 1'b0);
	or(shifted_address[13], address[11], 1'b0);
	or(shifted_address[14], address[12], 1'b0);
	or(shifted_address[15], address[13], 1'b0);
	or(shifted_address[16], address[14], 1'b0);
	or(shifted_address[17], address[15], 1'b0);
	or(shifted_address[18], address[16], 1'b0);
	or(shifted_address[19], address[17], 1'b0);
	or(shifted_address[20], address[18], 1'b0);
	or(shifted_address[21], address[19], 1'b0);
	or(shifted_address[22], address[20], 1'b0);
	or(shifted_address[23], address[21], 1'b0);
	or(shifted_address[24], address[22], 1'b0);
	or(shifted_address[25], address[23], 1'b0);
	or(shifted_address[26], address[24], 1'b0);
	or(shifted_address[27], address[25], 1'b0);
	or(shifted_address[28], address[26], 1'b0);
	or(shifted_address[29], address[27], 1'b0);
	or(shifted_address[30], address[28], 1'b0);
	or(shifted_address[31], address[29], 1'b0);
endmodule