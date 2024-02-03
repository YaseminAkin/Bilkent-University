//halfadder behavioral and testbench for it.
`timescale 1ps/1ps

module halfadder (
    input a,
    input b,
    output reg s,
    output reg c
);
        always @(a, b) begin
            s <= a^b;
            c <= a&b;
        end   
endmodule

//testbench
`timescale 1ps/1ps

module testhalfadder ();

        logic a, b;
        logic s,c;

        halfadder uut (a, b, s, c);

        initial begin
            
            #20;

            #10 a=0; b=0;
            #10 a=1; b=0;
            #10 a=0; b=1;
            #10 a=1; b=1;
        end
        initial $display($time,,“a=%d, b=%d,
                s=%d,c=%d“,a,b,s,c);
endmodule

//halfsubtractor behavioral and testbench for it.
`timescale 1ps/1ps

module halfsubtractor (
    input logic a, b,
    output logic d, c
);
        always @(a, b) begin
            d <= a^b;
            c <= ~a&b;
        end   
endmodule

//testbench
`timescale 1ps/1ps

module testhalfsubtractor ();

        logic a, b;
        logic d,c;

        halfadder uut (a, b, d, c);

        initial begin
            
            #20;

            #10 a=0; b=0;
            #10 a=1; b=0;
            #10 a=0; b=1;
            #10 a=1; b=1;
        end
        initial $display($time,,“a=%d, b=%d,
                d=%d,c=%d“,a,b,d,c);
endmodule

//fulladder structural and testbench for it.
`timescale 1ps/1ps

module fulladderstructural(input logic a,
    input logic b,
    input  logic cin,
    output logic sum,
    output logic cout
    );
    logic w1, w2, w3;
    halfadder halfadder0(a, b, w1, w2);
    halfadder halfadder1(w1, cin, sum, w3);
    or or0(w3, w2, cout);
endmodule

//testbench
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

//2-bitadder structural and testbench for it.
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

//testbench
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

//labcalculator and testbench for it.
`timescale 1ns / 1ps

module labcalculator(
    input logic a,
    input logic b,
    input logic c,
    input logic d,
    output logic y,
    output logic z
    );
    logic w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15, w16, w17, w18, 
    w19, w20, w21, w22, w23, w24, w25, w26, w27;
    
    nor NOR0(c,c, w1);
    nor NOR1(d,d, w2);
    and AND0(w1, w2, w3);
    and AND1(w3, a, w4);
    and AND2(w3, b, w5);
    and AND3(w4, w5, w6);
    and AND4(w1, d, w7);
    and AND5(w7, a, w8);
    and AND6(w7, b, w9);
    nor NOR2(w8, w9, w10);
    and AND7(w7, w10, w11);
    nor NOR3(w6, w11, w12);
    nor NOR4(w12, w12, w18);
    and AND8(w2, c, w13);
    and AND9(w13, a, w14);
    and AND10(w13, b, w15);
    halfadder halfadder1(w14, w15, w16, w17);
    nor NOR5(w16, w18, w19);
    nor NOR6(w19, w19, w20);
    and AND11(c, d, w21);
    and AND12(w21, a, w22);
    and AND13(w21, b, w23);
    halfsubtractor halfsubtractor1(w22, w23, w24, w25);
    nor NOR7(w20, w24, w26);
    nor NOR8(w26, w26, y);
    nor NOR9(w17, w25, w27);
    nor NOR10(w27, w27, z);
        
endmodule

//tetsbench
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