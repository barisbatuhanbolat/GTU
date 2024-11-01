module comparator ( 
		output lt,
		input [31:0] x, y
);

wire [32:0] sub;

assign sub = x - y;

assign lt = sub[32];

endmodule