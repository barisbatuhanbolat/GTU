module register_block( 
	input [31:0] write_data,
	input [4:0] read_reg1, read_reg2, write_reg,
	input regWrite, clk,
	output reg [31:0] read_data1, read_data2
);
	
	reg [31:0] registers [31:0];
	initial begin
		$readmemb("registers.mem",registers);
	end	
	always @(negedge clk) begin

	  $writememb("registers.mem",registers);
	  $readmemb("registers.mem",registers);
	  if(regWrite & write_reg != 0) begin
		 registers[write_reg] <= write_data;
	  end
	  read_data1 <= registers[read_reg1];
	  read_data2 <= registers[read_reg2];
	end

	
endmodule