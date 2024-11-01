module cla_4bit(
    input [3:0] a, b,
    input cin,
    output [3:0] sum,
    output cout
);
    
    wire [3:0] p, g;
    
    wire a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, o1, o2, o3, o4;
	 wire c0,c1,c2,c3;
    
    or(p[0], a[0], b[0]);
    or(p[1], a[1], b[1]);
    or(p[2], a[2], b[2]);
    or(p[3], a[3], b[3]);
    and(g[0], a[0], b[0]);
    and(g[1], a[1], b[1]);
    and(g[2], a[2], b[2]);
    and(g[3], a[3], b[3]);
    
	 and(a1, p[1], g[0]);
    and(a2, p[1], p[0], cin);
    or(c2, g[1], a1, a2);
	 
	 and(a3, p[2], g[1]);
    and(a4, p[2], p[1], g[0]);
	 and(a5, p[2], p[1], p[0], cin);
    or(c3, g[2], a3, a4, a5);
	 
    and(a6, p[3], g[2]);
    and(a7, p[3], p[2], g[1]);
	 and(a8, p[3], p[2], p[1], g[0]);
    and(a9, p[3], p[2], p[1], p[0],cin);
    or(cout, g[3], a6, a7, a8,a9);
    
    fullAdder fa0(a[0], b[0], cin, sum[0]);
    fullAdder fa1(a[1], b[1], g[0], sum[1]);
    fullAdder fa2(a[2], b[2], c2, sum[2]);
    fullAdder fa3(a[3], b[3], c3, sum[3]);
    
endmodule