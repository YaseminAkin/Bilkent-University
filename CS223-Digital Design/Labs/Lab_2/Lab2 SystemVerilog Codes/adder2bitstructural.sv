`timescale 1ns / 1ps

module adder2bitstructural( input logic a0,
    input logic b0,
    input logic cin,
    input logic a1,
    input logic b1,
    output logic s0,
    output logic s1,
    output logic cout
    );
    
    logic w1;
    
    fulladderstructural fulladder1(a0, b0, cin, s0, w1);
    fulladderstructural fulladder2(a1, b1, w1, s1, cout);
    
endmodule