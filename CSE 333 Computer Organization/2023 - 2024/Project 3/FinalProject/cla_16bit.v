module cla_16bit( 
		input [15:0] a, b,
		input cin,
		output [15:0] sum,
		output cout
);

		wire [3:0] p, g;

		wire a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, o1, o2, o3, o4;

		wire c0, c1, c2, c3, c4;

		cla_4bit adder0(a[3:0], b[3:0], cin, sum[3:0], c0);
		cla_4bit adder1(a[7:4], b[7:4], c0, sum[7:4], c1);
		cla_4bit adder2(a[11:8], b[11:8], c1, sum[11:8], c2);
		cla_4bit adder3(a[15:12], b[15:12], c2, sum[15:12], c3);

		or(p[0], a[3:0], b[3:0]);
		or(p[1], a[7:4], b[7:4]);
		or(p[2], a[11:8], b[11:8]);
		or(p[3], a[15:12], b[15:12]);
		and(g[0], a[3:0], b[3:0]);
		and(g[1], a[7:4], b[7:4]);
		and(g[2], a[11:8], b[11:8]);
		and(g[3], a[15:12], b[15:12]);

		and(a1, p[1], g[0]);
		and(a2, p[1], p[0], cin);
		or(c4, g[1], a1, a2);

		and(a3, p[2], g[1]);
		and(a4, p[2], p[1], g[0]);
		and(a5, p[2], p[1], p[0], cin);
		or(o1, g[2], a3, a4, a5);

		and(a6, p[3], g[2]);
		and(a7, p[3], p[2], g[1]);
		and(a8, p[3], p[2], p[1], g[0]);
		and(a9, p[3], p[2], p[1], p[0], cin);
		or(o2, g[3], a6, a7, a8, a9);

		and(a10, p[3], o1);
		and(a11, p[3], p[2], c4);
		and(a12, p[3], p[2], p[1], cin);
		or(o3, o2, a10, a11, a12);

		or(cout, o3, o2);

endmodule