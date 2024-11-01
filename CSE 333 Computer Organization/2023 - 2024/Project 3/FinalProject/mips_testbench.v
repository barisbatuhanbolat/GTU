// mips testbench code
module mips_testbench;

	  // input clock signal
	  reg clock;
		wire [31:0] updated_pc;
		reg [31:0] prog_ctr;	  
	  // instantiate the mips module
	  mips dut(clock,prog_ctr,updated_pc);
  
	initial begin
		clock <= 0;
		prog_ctr = 32'b00000000000000000000000000000000;
		forever begin
			#10 clock <= ~clock;
		end
	end

  // dump the waveforms to a file
  initial begin
    $dumpfile("mips_test.vcd");
    $dumpvars(0, mips_testbench);
  end
  
always @(negedge clock) begin
	#60 prog_ctr <= updated_pc;
end

  // run the simulation for 1000 ns
initial begin
	#1000;
	$finish();
end
  
endmodule
