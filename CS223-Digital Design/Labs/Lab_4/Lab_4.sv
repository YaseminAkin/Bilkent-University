//design code
`timescale 1ns/1ps
module FSM_TL (input logic clk, reset, SA, SB, output logic [2:0] LA, LB);

typedef enum logic [2:0] {S0,S1,S2,S3,S4,S5,S6,S7} statetype;
statetype [2:0] state, nextstate;
logic clkDiv;

//clockDivider div (clk, clkDiv); //other
assign clkDiv = clk; //simulation

//state register
always_ff@(posedge clkDiv, posedge reset)
    if(reset) state <= S0;
    else      state <= nextstate;

//next state logic
always_comb
    case(state)
        S0: if(SA) nextstate <= S0;
            else nextstate <= S1;
        S1: nextstate <= S2;
        S2: nextstate <= S3;
        S3: nextstate <= S4;
        S4: if(SB) nextstate <= S4;
            else nextstate <= S5;
        S5: nextstate <= S6;
        S6: nextstate <= S7;
        S7: nextstate <= S0;     
    endcase

//output logic
always_comb
    case(state)
        S0: begin
            LA <= 3'b011; //green 011 red 111 yellow 001
            LB <= 3'b111;
        end
        S1: begin
            LA <= 3'b001;
            LB <= 3'b111;
        end
        S2: begin
            LA <= 3'b111;
            LB <= 3'b111;
        end
        S3: begin
            LA <= 3'b111;
            LB <= 3'b001;
        end
        S4: begin
            LA <= 3'b111;
            LB <= 3'b011;
        end
        S5: begin
            LA <= 3'b111;
            LB <= 3'b001;
        end
        S6: begin
            LA <= 3'b111;
            LB <= 3'b111;
        end
        S7: begin
            LA <= 3'b001;
            LB <= 3'b111;
        end
    endcase
endmodule

`timescale 1ns/1ps
module clockDivider (input logic clk, output logic clkDivider);

    logic [31:0] count;
    always @(posedge clk) 
    begin
        if(count == 149999999)
            count <= 32'b0;
        else
            count <= count+1;
    end
    always @(posedge clk) 
    begin
        if(count == 149999999)
            clkDivider <= ~clkDivider;
        else
            clkDivider <= clkDivider;
    end
endmodule

//testbench for simulation part
`timescale 1ns/1ps
module FSM_TestBench();
    logic clk, reset, SA, SB;
    logic [2:0] LA, LB;
    FSM_TL testFSM(clk, reset, SA, SB, LA, LB);
    initial 
        begin
            clk <= 0;
            reset = 1; SA = 1; SB = 1; #4;
            //reset active
            reset = 1; #4;
            for(int i = 0; i < 4; i++) 
            begin
                SB = 0; #4;
                SB = 1; SA = 0; #4;
                SA = i; SB = i; #8; //to prove that transitions are input independent
                SB = 1; #4;
                SA = ~SA; #4;
                SB = 0; #4;
                SA = i; SB = i; #8;
                SA = 1; SB = 1; #4;
            end
            //reset inactive
            reset = 0; #4;
            for(int i = 0; i < 4; i++) 
            begin
                SB = 0; #4;
                SB = 1; SA = 0; #4;
                SA = i; SB = i; #8; //to prove that transitions are input independent
                SB = 1; #4;
                SA = ~SA; #4;
                SB = 0; #4;
                SA = i; SB = i; #8;
                SA = 1; SB = 1; #4;
            end
        end
    always #2 clk <= ~clk;
endmodule

module basys3Test (input logic clk, reset, SA, SB, output logic [1:0] LA, LB);
    FSM_TL testFSM(clk, reset, SA, SB, LA, LB);
endmodule