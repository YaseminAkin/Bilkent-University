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