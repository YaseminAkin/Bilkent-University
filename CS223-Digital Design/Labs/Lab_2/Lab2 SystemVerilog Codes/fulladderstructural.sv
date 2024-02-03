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