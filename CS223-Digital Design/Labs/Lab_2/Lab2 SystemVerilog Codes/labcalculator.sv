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