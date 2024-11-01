module subtractor_testbench;
  reg [31:0] A, B;
  wire [31:0] Difference;
  wire Borrow;

  subtractor UUT(A, B, Difference, Borrow);

  initial begin
    // Test case 1: A = 7, B = 3
    A = 7;
    B = 3;

    #10; // Wait for 10 time units

    // Display results
    $display("Test Case 1:");
    $display("A = %d", A);
    $display("B = %d", B);
    $display("Difference = %d", Difference);
    $display("Borrow = %d", Borrow);

    // Test case 2: A = 5, B = 9
    A = 5;
    B = 9;

    #10; // Wait for 10 time units

    // Display results
    $display("Test Case 2:");
    $display("A = %d", A);
    $display("B = %d", B);
    $display("Difference = %d", Difference);
    $display("Borrow = %d", Borrow);

    $finish;
  end
endmodule