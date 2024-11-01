module subtractor (
		input [31:0] a,
		input [31:0] b,
		output [31:0] difference,
		output borrow
);

		wire [31:0] b_complement;
		wire dummy;
		wire cin;

		not(b_complement[0],b[0]);
		not(b_complement[1],b[1]);
		not(b_complement[2],b[2]);
		not(b_complement[3],b[3]);
		not(b_complement[4],b[4]);
		not(b_complement[5],b[5]);
		not(b_complement[6],b[6]);
		not(b_complement[7],b[7]);
		not(b_complement[8],b[8]);
		not(b_complement[9],b[9]);
		not(b_complement[10],b[10]);
		not(b_complement[11],b[11]);
		not(b_complement[12],b[12]);
		not(b_complement[13],b[13]);
		not(b_complement[14],b[14]);
		not(b_complement[15],b[15]);
		not(b_complement[16],b[16]);
		not(b_complement[17],b[17]);
		not(b_complement[18],b[18]);
		not(b_complement[19],b[19]);
		not(b_complement[20],b[20]);
		not(b_complement[21],b[21]);
		not(b_complement[22],b[22]);
		not(b_complement[23],b[23]);
		not(b_complement[24],b[24]);
		not(b_complement[25],b[25]);
		not(b_complement[26],b[26]);
		not(b_complement[27],b[27]);
		not(b_complement[28],b[28]);
		not(b_complement[29],b[29]);
		not(b_complement[30],b[30]);
		not(b_complement[31],b[31]);


		subtractor_adder sub(difference, borrow, dummy, a, b_complement, 1);

endmodule

module full_subtractor(
		output sum, cout,
		input a, b, cin
);
		wire temp_sum, first_cout, second_cout;

		xor sum_of_digits(temp_sum, a, b);
		and carry_of_sum(first_cout, a, b);

		xor sum_of_digits_2(sum, temp_sum, cin);
		and carry_of_sum_2(second_cout, temp_sum, cin);

		or final_carry_out(cout, second_cout, first_cout);

endmodule

module subtractor_adder(
		output [31:0] S,
		output cout,
		output C30,
		input [31:0] A,B,
		input C0
);

		wire [29:0] C;

		full_subtractor   FA0(S[0], C[0], A[0], B[0], C0),
								FA1(S[1], C[1], A[1], B[1], C[0]),
								FA2(S[2], C[2], A[2], B[2], C[1]),
								FA3(S[3], C[3], A[3], B[3], C[2]),
								FA4(S[4], C[4], A[4], B[4], C[3]),
								FA5(S[5], C[5], A[5], B[5], C[4]),
								FA6(S[6], C[6], A[6], B[6], C[5]),
								FA7(S[7], C[7], A[7], B[7], C[6]),
								FA8(S[8], C[8], A[8], B[8], C[7]),
								FA9(S[9], C[9], A[9], B[9], C[8]),
								FA10(S[10], C[10], A[10], B[10], C[9]),
								FA11(S[11], C[11], A[11], B[11], C[10]),
								FA12(S[12], C[12], A[12], B[12], C[11]),
								FA13(S[13], C[13], A[13], B[13], C[12]),
								FA14(S[14], C[14], A[14], B[14], C[13]),
								FA15(S[15], C[15], A[15], B[15], C[14]),
								FA16(S[16], C[16], A[16], B[16], C[15]),
								FA17(S[17], C[17], A[17], B[17], C[16]),
								FA18(S[18], C[18], A[18], B[18], C[17]),
								FA19(S[19], C[19], A[19], B[19], C[18]),
								FA20(S[20], C[20], A[20], B[20], C[19]),
								FA21(S[21], C[21], A[21], B[21], C[20]),
								FA22(S[22], C[22], A[22], B[22], C[21]),
								FA23(S[23], C[23], A[23], B[23], C[22]),
								FA24(S[24], C[24], A[24], B[24], C[23]),
								FA25(S[25], C[25], A[25], B[25], C[24]),
								FA26(S[26], C[26], A[26], B[26], C[25]),
								FA27(S[27], C[27], A[27], B[27], C[26]),
								FA28(S[28], C[28], A[28], B[28], C[27]),
								FA29(S[29], C[29], A[29], B[29], C[28]),
								FA30(S[30], C30, A[30], B[30], C[29]),					
								FA31(S[31], cout, A[31], B[31], C30);
				
endmodule