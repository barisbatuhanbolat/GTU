module memory_blocktb();

	reg memWrite,memRead,clk;
	reg [17:0] address;
   reg [31:0] write_data;
	wire [31:0] read_data;
	reg [31:0] registers[31:0];

memory_block dm(memWrite,memRead,clk,address,write_data,read_data);

initial begin
	clk <= 0;
   forever begin
		#10 clk <= ~clk;
	end
end


initial begin
		 memWrite=1;
		 memRead=0;
	#20 write_data = 32'd15;
		 address = 18'd0;
	#20 write_data= 32'd92;
		 address = 18'd4;
	#20 memWrite=0;
	#20 write_data = 32'd66;
		 address = 18'd8; 
	#20 memRead=1;
		 address=18'd0;
	#20 address=18'd4;
	#30 address=18'd8;
end



initial begin
	$monitor("memWrite:%b,memRead=%b,address=%d,write_data=%d,read_data=%d",memWrite,memRead,address,write_data,read_data);
end

endmodule
	
