`timescale 1ns / 1ps

module testfulladderstructural();
    logic a, b, cin;
    logic s, cout;
    fulladder adder(a, b, cin, s, cout);
    initial begin
        a = 0; b = 0; cin = 0; #10;
        if (s !== 0 & cout !== 0) $display("000 failed");
        cin = 1; #10;
        if (s !== 1 & cout !== 0) $display("001 failed");
        b = 1; #10;
        if (s !== 0 & cout !== 1) $display("011 failed");
        cin = 0; #10;
        if (s !== 1 & cout !== 0) $display("010 failed");
        a = 1; #10;
        if (s !== 0 & cout !== 1) $display("110 failed");
        b = 0; #10;
        if (s !== 1 & cout !== 0) $display("100 failed");
        cin = 1; #10;
        if (s !== 0 & cout !== 1) $display("101 failed");
        b = 1; #10;
        if (s !== 1 & cout !== 1) $display("111 failed");
    end
endmodule