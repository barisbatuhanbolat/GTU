module alu_control(
		input [2:0] aluOp,
		input [5:0] function_code,
		output[2:0] alu_ctr
);
		and and1(andc1,aluOp[2],~aluOp[1]);
		and and2(andc2,aluOp[2],aluOp[1],~aluOp[0]);
		and and3(andc3,aluOp[2],aluOp[1],aluOp[0],~function_code[2],function_code[1]);
		and and4(andc4,aluOp[2],aluOp[1],aluOp[0],function_code[2],function_code[1],function_code[0]);
		or or1(alu_ctr[2],andc1,andc2,andc3,andc4);
		
		and and5(andc5,~aluOp[2],aluOp[1]);
		and and6(andc6,aluOp[2],aluOp[1],~aluOp[0]);
		and and7(andc7,aluOp[2],aluOp[1],aluOp[0],~function_code[2],function_code[1],function_code[0]);
		or or2(alu_ctr[1],andc5,andc6,andc7);
		
		and and8(andc8,~aluOp[2],aluOp[0]);
		and and9(andc9,aluOp[2],~aluOp[1],aluOp[0]);
		and and10(andc10,aluOp[2],aluOp[1],aluOp[0],~function_code[2],function_code[1],~function_code[0]);
		and and11(andc11,aluOp[2],aluOp[1],aluOp[0],function_code[2],~function_code[1],function_code[0]);
		or or3(alu_ctr[0],andc8,andc9,andc10,andc11);

endmodule
