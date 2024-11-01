module instruction_block(
	input clk,
	input [31:0] pc,
	output [31:0] instruction
);
	reg [31:0] instructions[1023:0];
	reg [31:0] temp;
	
	initial begin
		$readmemb("instructions.mem",instructions);
	end
	
	always @(negedge clk) begin
		temp <= instructions[pc/4];
	end
	
	assign instruction = temp;
	
	
	
endmodule
