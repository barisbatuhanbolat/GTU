`timescale 1ns / 1ps

module mod_testbench;

  reg clk;
  reg reset;
  reg [31:0] a, b;
  wire [31:0] result;

  mod mod_inst (
    .clk(clk),
    .reset(reset),
    .a(a),
    .b(b),
    .result(result)
  );

  // Clock generation
  always begin
    #5 clk = ~clk;
  end

  // Initial block
  initial begin
    // Test Case 1
    clk = 0;
    reset = 0;
    a = 25;
    b = 8;

    // Apply reset
    reset = 1;
    #10 reset = 0;

    // Apply stimulus
    #10 a = 40;
    #10 b = 12;

    // Wait for some time
    #100;

    // Display result
    $display("Test Case 1: Result: %d", result);

    // Test Case 2
    clk = 0;
    reset = 0;
    a = 30;
    b = 10;

    // Apply reset
    reset = 1;
    #10 reset = 0;

    // Apply stimulus
    #10 a = 45;
    #10 b = 15;

    // Wait for some time
    #100;

    // Display result
    $display("Test Case 2: Result: %d", result);

    // Finish simulation
    $stop;
  end

endmodule