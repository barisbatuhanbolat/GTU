module instruction_block_tb;

reg clk;
reg [31:0] pc;

wire [31:0] instruction;

instruction_block dut (
	.clk(clk),
	.pc(pc),
	.instruction(instruction)
);

initial begin
	clk = 0;
	pc = 0;
	#50;
	pc = 4;
	#50;
	pc = 8;
	#50;
	pc = 12;
	#50;
	pc = 16;
	#50;
	pc = 20;
	#50;
	pc = 24;	
	#50;
	pc = 28;	
	#1000;
	
	$finish;
end

always #5 clk = ~clk;

initial $monitor ($time, " pc = %d, instruction = %b", pc, instruction);

endmodule
