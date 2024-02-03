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