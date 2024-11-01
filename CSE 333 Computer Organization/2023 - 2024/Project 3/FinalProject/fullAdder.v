module fullAdder(
    input a, b, cin,
    output sum 
    );

    wire x1, x2, x3, a1, a2, a3, o1;
    
    xor(x1, a, b);
    xor(sum, x1, cin);
    xor(x2, a, cin);
    xor(x3, b, cin);
    
endmodule