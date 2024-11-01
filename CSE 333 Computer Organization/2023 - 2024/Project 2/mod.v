module mod(
    input  clk, reset,
    input  [31:0] a,
    input  [31:0] b,
    output [31:0] result
);
    wire load;
    wire enable;
    wire subtract;
	 wire temp_lt_B;

    mod_dp dp_inst (
        .clk(clk),
        .load(load),
        .a(a),
        .b(b),
        .result(result),
        .temp_lt_B(temp_lt_B)
    );

    mod_cu ctrl_inst (
			.temp_lt_B(temp_lt_B),
        .clk(clk),
        .reset(reset),
        .opcode(2'b00),
        .load(load),
        .enable(enable),
        .subtract(subtract)
    );

endmodule