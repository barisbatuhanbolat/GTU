module control_tb; // top-level testbench module
  // declare signals for DUT connection
  reg [5:0] opCode; // 6-bit input for the opcode
  wire regDst, branch, memRead, memWrite, ALUsrc, regWrite, jump, byteOperations, move; // output signals
  wire [2:0] ALUop; // 3-bit output for the ALU operation
  
  // instantiate the DUT module
  control_unit dut (opCode, regDst,branch,memRead,memWrite,ALUsrc,regWrite,jump,byteOperations,move,ALUop);
  
  // generate input stimuli
  initial begin
    // create a waveform file
    $dumpfile("control_tb.vcd");
    $dumpvars(0, control_tb);
    
    // initialize the input signals
    opCode = 6'b000000; // R-type instruction
    #10; // wait for 10 time units
    
    // change the input signals
    opCode = 6'b000010; // add immediate instruction
    #10;
    
    opCode = 6'b000011; // subtract immediate instruction
    #10;
    
    opCode = 6'b000100;
    #10;
    
    opCode = 6'b000101; 
    #10;
    
    opCode = 6'b001000; 
    #10;
    
    opCode = 6'b010000; 
    #10;
    
    opCode = 6'b001001; 
    #10;
    
    opCode = 6'b010001; 
    #10;
    
    opCode = 6'b000111; 
    #10;
    
    opCode = 6'b100011; 
    #10;
    
    opCode = 6'b111000;
    #10;
    
    opCode = 6'b100000;
    #10;
    // end the simulation
    $finish;
  end
  
  // monitor the output values
  initial begin
    $monitor("opCode = %b, regDst = %b, branch = %b, memRead = %b, memWrite = %b, ALUop = %b, ALUsrc = %b, regWrite = %b, jump = %b, byteOperations = %b, move = %b",
    opCode, regDst, branch, memRead, memWrite, ALUop, ALUsrc, regWrite, jump, byteOperations, move);
  end
  
endmodule
