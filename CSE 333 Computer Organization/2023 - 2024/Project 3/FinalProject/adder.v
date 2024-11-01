module adder( 
	   input [31:0] a, b,
		input cin,
		output [31:0] sum,
		output cout
);

		wire [1:0] p, g;

		wire a1, a2, a3, a4, a5, a6, o1, o2, o3;

		wire c0, c1, c2;

		cla_16bit adder0(a[15:0], b[15:0], cin, sum[15:0], c0);
		cla_16bit adder1(a[31:16], b[31:16], c0, sum[31:16], c1);

		or(p[0], a[15:0], b[15:0]);
		or(p[1], a[31:16], b[31:16]);
		and(g[0], a[15:0], b[15:0]);
		and(g[1], a[31:16], b[31:16]);

		and(a1, p[1], g[0]);
		and(a2, p[1], p[0], cin);
		or(c2, g[1], a1, a2);

		and(a3, p[1], c2);
		and(a4, p[1], p[0], c0);
		and(a5, p[1], p[0], cin);
		or(o1, g[1], a3, a4, a5);

		and(a6, p[1], o1);
		or(o2, o1, a6);

		or(cout, o2, o1);

endmodule