module mod_cu(
    input clk, reset,temp_lt_B,
    input [1:0] opcode,
    output reg load,
    output reg enable,
    output reg subtract
);

    reg [1:0] state;

    // Define states
    localparam IDLE = 2'b00;
    localparam LOAD_A = 2'b01;
    localparam SUBTRACT = 2'b10;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            load <= 0;
            enable <= 0;
            subtract <= 0;
        end else begin
            case (state)
                IDLE: begin
                    load <= 1;
                    enable <= 0;
                    subtract <= 0;

                    if (opcode == 2'b00) begin
                        state <= LOAD_A;
                    end
                end

                LOAD_A: begin
                    load <= 0;
                    enable <= 0;
                    subtract <= 0;

                    if (!temp_lt_B) begin
                        state <= SUBTRACT;
                    end
                end

                SUBTRACT: begin
                    load <= 0;
                    enable <= 1;
                    subtract <= 1;
                end
            endcase
        end
    end
endmodule