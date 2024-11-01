module _4x1Mux (
		output y, 
		input a, b, s
);
	   wire x;
	   // 2x1 muxes
	   _2x1Mux m0 (x, a, b, s);
	   _2x1Mux m1 (y, x, b, s);
endmodule