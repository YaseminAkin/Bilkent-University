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
