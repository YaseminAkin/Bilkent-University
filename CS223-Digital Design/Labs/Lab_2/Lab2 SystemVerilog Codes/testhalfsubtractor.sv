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
