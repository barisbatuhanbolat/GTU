module mod_dp(
    input  clk,load,
    input  [31:0] a,
    input  [31:0] b,
    output reg [31:0] result,
	 output temp_lt_B
);
	reg [31:0] temp_reg;
	wire borrow;
	wire [31:0] difference;
	
	comparator comp(temp_lt_B,temp_reg,b);
	
	subtractor sub(temp_reg,b,difference,borrow);
		
	always @(posedge clk) begin
	    if (load) begin
            temp_reg <= a;
        end
			else if (temp_lt_B)  begin
				result <= temp_reg;
		 end
		 else begin
			  temp_reg <= difference;
		 end 		 
	end
	
endmodule