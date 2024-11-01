module memory_block(
	input memWrite,memRead,clk,
	input [17:0] address,
   input [31:0] write_data,
	output reg [31:0] read_data
);
	reg [31:0] registers[31:0]; // 18-bit address can access 2^18 locations
	initial begin
		$readmemb("memory.mem",registers);
	end
	always @(negedge clk) begin	
		$writememb("memory.mem",registers); // write the updated registers array to the file
	   $readmemb("memory.mem",registers); // read the file back into the registers array
		if(memWrite) begin
			registers[address] <= write_data;				
		end
		if(memRead) begin
			read_data <= registers[address];
		end
	end
endmodule
