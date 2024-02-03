`timescale 1ns / 1ps

module test2bitadder();
    logic a0, b0, cin, a1, b1;
    logic s0, s1, cout;
    
    adder2bitstructural adder(a0, b0, cin, a1, b1, s0, s1, cout);
    initial begin
        a0 = 0; a1 = 0; b0 = 0; b1 = 0; cin = 0; #10;
        cin = 1; #10;
        b1 = 1; #10;
        cin = 0; #10;
        b0 = 1; #10;
        cin = 1; #10;
        b1 = 0; #10;
        cin = 0; #10;
        a1 = 1; b0 = 0; #10;
        cin = 1; #10;
        b1 = 1; #10;
        cin = 0; #10;
        b0 = 1; #10;
        cin = 1; #10;
        b1 = 0; #10;
        cin = 0; #10;
        a0 = 1; b0 = 0; #10;
        cin = 1; #10;
        b1 = 1; #10;
        cin = 0; #10;
        b0 = 1; #10;
        cin = 1; #10;
        b1 = 0; #10;
        cin = 0; #10;
        a1 = 0; b0 = 0; #10;
        cin = 1; #10;
        b1 = 1; #10;
        cin = 0; #10;
        b0 = 1; #10;
        cin = 1; #10;
        b1 = 0; #10;
        cin = 0; #10;
    end
endmodule