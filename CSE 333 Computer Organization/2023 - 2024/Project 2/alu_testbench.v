module alu_testbench;
  // Inputs
  reg [31:0] A, B;
  reg [2:0] ALUop;
  reg clk, reset;
  // Outputs
  wire [31:0] result;
  // Instantiate the Unit Under Test (UUT)
  alu uut (
    .A(A), 
    .B(B), 
    .ALUop(ALUop), 
    .clk(clk),
    .reset(reset),
    .result(result)
  );
  // Initialize inputs
  initial begin
    // Test each opcode with two different examples
    // and print each example to the screen
    $display("Testing ALU with different opcodes and operands");
    $display("-------------------------------------------------");
    // Test AND operation
    ALUop = 3'b000;
    A = 10;
    B = 15;
    #10;
    $display("AND: A = %b, B = %b, result = %b", A, B, result);
    A = 255;
    B = 0;
    #10;
    $display("AND: A = %b, B = %b, result = %b", A, B, result);
    // Test OR operation
    ALUop = 3'b001;
    A = 10;
    B = 15;
    #10;
    $display("OR: A = %b, B = %b, result = %b", A, B, result);
    A = 255;
    B = 0;
    #10;
    $display("OR: A = %b, B = %b, result = %b", A, B, result);
    // Test XOR operation
    ALUop = 3'b010;
    A = 10;
    B = 15;
    #10;
    $display("XOR: A = %b, B = %b, result = %b", A, B, result);
    A = 255;
    B = 0;
    #10;
    $display("XOR: A = %b, B = %b, result = %b", A, B, result);
    // Test NOR operation
    ALUop = 3'b011;
    A = 10;
    B = 15;
    #10;
    $display("NOR: A = %b, B = %b, result = %b", A, B, result);
    A = 255;
    B = 0;
    #10;
    $display("NOR: A = %b, B = %b, result = %b", A, B, result);
    // Test less than operation
    ALUop = 3'b100;
    A = 10;
    B = 15;
    #10;
    $display("Less than: A = %b, B = %b, result = %b", A, B, result[31]);
    A = 0;
    B = 255;
    #10;
    $display("Less than: A = %b, B = %b, result = %b", A, B, result[31]);
    // Test addition operation
    ALUop = 3'b101;
    A = 15;
    B = 10;
    #10;
    $display("Addition: A = %b, B = %b, result = %b", A, B, result);
    A = 255;
    B = 256;
    #10;
    $display("Addition: A = %b, B = %b, result = %b", A, B, result);
    // Test subtraction operation
    ALUop = 3'b110;
    A = 15;
    B = 10;
    #10;
    $display("Subtraction: A = %b, B = %b, result = %b", A, B, result);
    A = 1;
    B = 255;
    #10;
    $display("Subtraction: A = %b, B = %b, result = %b", A, B, result);
    // Test mod operation
    ALUop = 3'b111;
    A = 10;
    B = 15;
    clk = 0;
    reset = 0;
	 // Apply reset
    reset = 1;
    #10 reset = 0;
	 
	 #10 A = 10;
    #10 B = 15;
	 
    #100;
    $display("Mod: A = %b, B = %b, result = %b", A, B, result);
    A = 15;
    B = 5;
    clk = 0;
    reset = 0;
	 // Apply reset
    reset = 1;
    #10 reset = 0;
	 
	 #10 A = 15;
    #10 B = 5;
	 
    #100;
    $display("Mod: A = %b, B = %b, result = %b", A, B, result);
    #10 $stop;
	 
  end
  // Generate clock signal for mod
  always #5 clk = ~clk;
endmodule
