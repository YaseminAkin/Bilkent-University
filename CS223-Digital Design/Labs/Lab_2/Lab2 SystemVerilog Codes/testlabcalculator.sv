`timescale 1ns / 1ps

module testlabcalculator();
    logic a, b, c, d;
    logic y, z;
    labcalculator calculator(a, b, c, d, y, z);
    initial begin
        a = 0; b = 0; c = 0; d = 0; #10;
        d = 1; #10;
        c = 1; #10;
        d = 0; #10;
        b = 1; c = 0; #10;
        d = 1; #10;
        c = 1; #10;
        d = 0; #10;
        a = 1; c = 0; #10;
        d = 1; #10
        c = 1; #10
        d = 0; #10
        b = 0; c = 0; #10;
        d = 1; #10
        c = 1; #10
        d = 0; #10
    end
endmodule