module _8x1Mux (
		output o, 
		input i1,i2,i3,i4,i5,i6,i7,i8, 
		input [2:0] s
);
		wire [3:0] m, n;
		wire a, b, c;

		_4x1Mux m0 (m[0], i1, i2, s[0]);
		_4x1Mux m1 (m[1], i3, i4, s[0]);
		_4x1Mux m2 (m[2], i5, i6, s[0]);
		_4x1Mux m3 (m[3], i7, i8, s[0]);
		_2x1Mux n0 (n[0], m[0], m[1], s[1]);
		_2x1Mux n1 (n[1], m[2], m[3], s[1]);
		_2x1Mux n2 (o, n[0], n[1], s[2]);
endmodule
