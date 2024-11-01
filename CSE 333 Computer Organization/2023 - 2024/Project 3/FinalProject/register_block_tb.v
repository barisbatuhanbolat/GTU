module register_block_tb;
    reg [31:0] write_data;
    reg [4:0] read_reg1, read_reg2, write_reg;
    reg regWrite, clk;
    wire [31:0] read_data1, read_data2;

    register_block dut (
        .write_data(write_data),
        .read_reg1(read_reg1),
        .read_reg2(read_reg2),
        .write_reg(write_reg),
        .regWrite(regWrite),
        .clk(clk),
        .read_data1(read_data1),
        .read_data2(read_data2)
    );

    always #5 clk = ~clk;

    initial begin
        clk = 0;
        write_data = 0;
        read_reg1 = 0;
        read_reg2 = 0;
        write_reg = 0;
        regWrite = 0;
    end

    initial begin
        @(posedge clk);

        write_data = 42;
        write_reg = 1;
        regWrite = 1;
        @(posedge clk);

        write_data = 17;
        write_reg = 2;
        @(posedge clk);

        regWrite = 0;
        @(negedge clk);

        read_reg1 = 1;
        read_reg2 = 2;
        @(negedge clk);

        $display("Read data 1: %d", read_data1);
        $display("Read data 2: %d", read_data2);

        $finish;
    end
endmodule
