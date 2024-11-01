module ALUless_than(
		input [31:0] a,b,
		output less_than
);
		wire [31:0] difference;
		wire borrow;
		subtractor sub(a,b,difference,borrow);
		
		or or1(less_than,0,difference[31]);
endmodule		