//2:1 mux behavioral
`timescale 1ns/1ps
module mux2to1 (input logic S, input logic [3:0] d0,d1, output logic [3:0] Q);
assign Q = S ? d1 : d0;
endmodule

//Instruction Register (IR)
`timescale 1ns/1ps
module instructionRegister (input logic clk, clear, input logic [11:0] in, output logic [11:0] out);

always_ff @ (posedge clk or posedge clear) begin
    if(~clear) {
        out <= in;
    }
    else {
        out <= 0;
    }
end
endmodule

//Program Counter (PC)
`timescale 1ns/1ps
module programCounter (input logic clk, clear, enable, output logic [2:0] outAdrs);

always_ff @(posedge clk or posedge clear) begin

    if(clear!=1) begin
        if(enable==1) {
            outAdrs <= outAdrs+1;
        }
    end
    else begin
        outAdrs <= -1;
    end
end
endmodule

//Instruction Memory 
`timescale 1ns/1ps
module instructionMemory (input logic clk, clear, isExternal, rcrd, input logic [2:0] adrs, input logic [11:0] sws, 
output logic [11:0] out);

logic [7:0] Mem;

always_ff @ (posedge clk or posedge clear) begin

    if(clear!=1) begin
        if(rcrd==0) begin
            if(isExternal!=1) {
                out <= Mem[adrs];
            }
            else {
                out <= sws;
            }
        end
        else {
            Mem[adrs] = sws;
        }
    end
    else begin //testing left button for first 4 operations
        Mem[0] <= 12'b000_00_001_0011; //load rf[1] =  3
        Mem[1] <= 12'b000_00_000_0111; //load rf[0] = 7
        Mem[2] <= 12'b101_011_000_001; //rf[0] + rf[1] -> rf[3] = 10
        Mem[3] <= 12'b101_111_001_011; //rf[3] + rf[1] -> rf[7] = 13
        Mem[4] <= 12'b110_100_000_011; // rf[3] - rf[0] -> rf[4] = 3
        Mem[5] <= 12'b001_00_100_0101; //store dDone[5] = 3
        Mem[6] <= 12'b000_00_000_0101; //load rf[0] as dDone[5](3)
        Mem[7] <= 12'b101_111_001_000; //rf[7] = rf[0] + rf[1] = 6    
    end
end
endmodule

//SystemVerilog module for synchronously resettable D flip-flop.
`timescale 1ns/1ps
module resettableDFlipFlop (input logic d, reset, clk, output logic q);

    always_ff @(posedge clk) begin
        if(reset) q <= 1'b0;
        else q <= d;
    end

endmodule

//behavioral halfadder module to use in structural fulladder module
`timescale 1ns/1ps
module halfadder(
    input a,
    input b,
    output reg s,
    output reg c );
        always @(a, b) begin
            s <= a^b;
            c <= a&b;
        end   
endmodule

//structural fulladder module to use in serial adder module
`timescale 1ns/1ps
module fulladder(input logic a,
    input logic b,
    input  logic cin,
    output logic sum,
    output logic cout
    );
    logic w1, w2, w3;
    halfadder halfadder0(a, b, w1, w2);
    halfadder halfadder1(w1, cin, sum, w3);
    or or0(cout, w2, w3);
endmodule

//Structural SystemVerilog module for shift register using the D flip-flop module along
//with the testbench.
`timescale 1ns/1ps
module register8bit(input logic [7:0] in,
                    input logic clk, load, rightshift, reset,
                    output logic [7:0] out);
    logic [7:0] tempOutput;

    resettableDFlipFlop ff0 (in[7], reset, load, tempOutput[7]);
    resettableDFlipFlop ff1 (in[6], reset, load, tempOutput[6]);
    resettableDFlipFlop ff2 (in[5], reset, load, tempOutput[5]);
    resettableDFlipFlop ff3 (in[4], reset, load, tempOutput[4]);
    resettableDFlipFlop ff4 (in[3], reset, load, tempOutput[3]);
    resettableDFlipFlop ff5 (in[2], reset, load, tempOutput[2]);
    resettableDFlipFlop ff6 (in[1], reset, load, tempOutput[1]);
    resettableDFlipFlop ff7 (in[0], reset, load, tempOutput[0]);

    always@(posedge clk)
        begin
            if(reset)
                out = 0;
            else if(load)
                out = tempOutput;
            else if(rightshift)
                out = out >> 1;
            else
                out = out;
        end
endmodule

//testbench
`timescale 1ns/1ps
module register8bitTest();
    logic [7:0] in;
    logic clk, load, rightshift, reset;
    logic [7:0] out;

    register8bit uut(input, clk, load, rightshift, reset, out);

    initial begin
        clk <= 0;
        
        reset = 1; #10;
        in = 8'b10110101; load = 1; #10;
        load = 0; rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
    end
    always #2 clk <= ~clk;
endmodule

//Structural SystemVerilog module for serial adder using the shift register, full adder,
//and D flip-flop modules along with the testbench.
`timescale 1ns/1ps
module serial8bitadder(input logic shiftSignal, loadSignal, reset, clk,
                        input logic [7:0] in1, in2,
                        output logic [7:0] out);
    logic outa, outb, sum, cin, cout;

    register8bit rega(in1, clk, loadSignal, rightshift, reset, outa);
    register8bit regb(in2, clk, loadSignal, rightshift, reset, outb);

    fulladder adder1(outa, outb, cin, sum, cout);
    resettableDFlipFlop ff1(cout, reset, clk, cin);
    register8bit regc(sum, clk, loadSignal, rightshift, reset, out);

endmodule

//testbench
`timescale 1ns/1ps
module serialAdderTest();
    logic shiftSignal, loadSignal, reset, clk;
    logic [7:0] in1, in2, out;

    serial8bitadder uut(shiftSignal, loadSignal, reset, clk, in1, in2, out);

    initial begin
        clk <= 0;

        reset = 1; #10;
        in1 = 8'b10110101;
        in2 = 8'b00110011;

        loadSignal = 1; reset = 0; #10;
        loadSignal = 0; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
        rightshift = 1; #10;
    end
    always #2 clk <= ~clk;

endmodule

//RF
`timescale 1ns/1ps
module registerFile (input logic we, clk, clear, rcrd, input logic [2:0] ad1, ad2, wa,
input logic [3:0] wd, input logic [6:0] sws, output logic [3:0] s0ALU,s1Control);

logic [7:0] RF;

always_ff @ (posedge clk or posedge clear) begin
    if(clear==1) begin
        s0ALU <= 0;
        s1Control <= 0;
        RF[0] <= 0;
        RF[1] <= 0;
        RF[2] <= 0;
        RF[3] <= 0;
        RF[4] <= 0;
        RF[5] <= 0;
        RF[6] <= 0;
        RF[7] <= 0;   
    end
    else begin
        if(rcrd!=0) begin
            RF[sws[2:0]] = sws[6:3];
        end
        else begin
            if(we!=1) begin
                s0ALU <= RF[ad1];
                s1Control <= RF[ad2];
            end
            else begin
                RF[wa] <= wd;
            end
        end
    end
end
endmodule

//ALU
`timescale 1ns/1ps
module ALU_Unit(input logic [2:0] op, input logic [3:0] x, y, output logic [3:0] z);

//operation codes
logic op1 = 3'b000;
logic op2 = 3'b001;
logic op3 = 3'b010;
logic op4 = 3'b011;
logic op5 = 3'b100;
logic op6 = 3'b101;
logic op7 = 3'b110;
logic op8 = 3'b111;

always_comb begin
    case(op)
        default: z = 0;
        op8 : begin
            if(x < y) {
                z = y;
            }
            else {
                z = x;
            }
        end
        op7 : begin
            if(x >= y) {
                z = y;
            }
            else {
                z = x;
            }
        end
        op1 : z = x&y;
        op2 : z = x|y;
        op3 : z = x+y;
        op4 : z = x&~y;
        op5 : z = x;
        op6 : z = x-y;
    endcase
end
endmodule

//Data Memory
`timescale 1ns/1ps
module dataMemory (input logic we, re, clk, clear, input logic [3:0] add, input logic [3:0] wd, output logic [3:0] rd);

logic [15:0] Mem;

always_ff @ (posedge clk or posedge clear) begin
    if(clear) begin 
        rd <= 0;
        Mem[0] <= 0;
        Mem[1] <= 0;
        Mem[2] <= 0;
        Mem[3] <= 0;
        Mem[4] <= 0;
        Mem[5] <= 0;
        Mem[6] <= 0;
        Mem[7] <= 0;
        Mem[8] <= 0;
        Mem[9] <= 0;
        Mem[10] <= 0;
        Mem[11] <= 0;
        Mem[12] <= 0;
        Mem[13] <= 0;
        Mem[14] <= 0;
        Mem[15] <= 0;    
    end
    else begin
        if(we && re) begin
            rd <= wd;
            Mem[add] <= wd;
        end
        else if(re) {
            rd <= Mem[add];
        }
        else if(we) {
            Mem[add] <= wd;
        }
    end
end
endmodule

//Debouncer
`timescale 1ns/1ps
module debouncer(input logic btn, clk, clear, output logic outBtn);

parameter limCntr = 200000;
state_type state;
typedef enum s0 state_type;
typedef enum s1 state_type;
integer cnter;
logic finalResult, out1, out2, out3, out4;
out3 <= out1^out2;

always_ff @ (posedge clk or posedge clear) begin

    if(!clear) begin 
        out1 <= btn;
        out2 <= out1;
        if (out4 == 1) {
            finalResult <= out2;
        }
        if (!out3 && out4==0 ) begin
            if (cnter >= limCntr) {
                out4 <= 1; 
            }
            else {
                cnter <= cnter + 1;
            }
        end
        else begin
            out4 <= 0;
            cnter <= 0;
        end
    end
    else begin //all 0
        cnter <= 0;
        out1 <= 0;
        out2 <= 0;
        out4 <= 0;
        finalResult <= 0;
    end
end

always_ff @ (posedge clk or posedge clear) begin 
    if(!clear) begin
        case(state)
            s0: begin
                if(finalResult!=1) begin
                    outBtn <= 0;
                    state <= s0;
                end
                else begin
                    outBtn <= 1;
                    state <= s1;
                end
            end
            s1: begin
                outBtn <= 0;
                if(finalResult!=0) {
                    state <= s1;
                }
                else {
                    state <= s0;
                }
            end
        endcase
    end
    else begin
        outBtn <= 0;
        state <= s0;
    end
end
endmodule

//Seven Segment Display Helper to use in original module
`timescale 1ns/1ps
module sevenSegmentHelper (input logic [3:0] num, output logic [6:0] out);

always_comb begin
    case(num) //taken from some source
        4'b0000: out = 7'b1000000;  
        4'b0001: out = 7'b1111001; 
        4'b0010: out = 7'b0100100;  
        4'b0011: out = 7'b0110000;  
        4'b0100: out = 7'b0011001; 
        4'b0101: out = 7'b0010010;  
        4'b0110: out = 7'b0000010; 
        4'b0111: out = 7'b1111000; 
        4'b1000: out = 7'b0000000; 
        4'b1001: out = 7'b0010000; 
        4'b1010: out = 7'b0001000; 
        4'b1011: out = 7'b0000011; 
        4'b1100: out = 7'b1000110; 
        4'b1101: out = 7'b0100001; 
        4'b1110: out = 7'b0000110; 
        4'b1111: out = 7'b1111111; 
        default: out = 7'b1000000; 
    endcase
end
endmodule

//Seven Segment Display
`timescale 1ns/1ps
module sevenSegmentFinal (input logic clk, clear, input logic [3:0] d0, d1, d2, d3, output logic [6:0] out,
output logic [3:0] en);

logic [3:0] num;

state_type state;
typedef enum {s0ALU, s1Control, s2Control, s3Control} state_type;

integer cnter;
parameter limCntr = 200000;

sevenSegmentHelper sevenSegment1(num,out);

//NEXT STATE
always_ff @ (posedge clk or posedge clear) begin
    if(!clear)begin
        if(limCntr > cnter) begin
            cnter <= cnter+1;
        end
        else begin
            cnter <= 0;
            case(state)                 
                s0ALU: begin
                    state <= s1Control;
                end
                s1Control: begin
                    state <= s2Control;
                end
                s2Control: begin
                    state <= s3Control;
                end
                s3Control: begin
                    state <= s0ALU;
                end
                default: begin
                    state <= s0ALU;
                end 
            endcase
        end
    end
    else begin
        state <= s0ALU;
        cnter <= 0;
    end
end

//STATE
always_comb begin
    case(state)
        s0ALU: begin
            en = 4'b1110; 
            num = d1;           
        end
        s1Control: begin
            en = 4'b1101; 
            num = d2;                   
        end
        s2Control: begin
            en = 4'b1011; 
            num = d1;                   
        end
        s3Control: begin
            num = d0;
            en = 4'b0111;                    
        end
        default: begin
            num = 0;
            en = 0;         
        end
    endcase
end
endmodule

//Test Module Final
`timescale 1ns/1ps
module basysTest (input logic center, up, left, right, down, clk, input logic [15:0] sws, output logic [6:0] disp, output logic [3:0] ans);

//all signals
logic rcrd1, rcrd2, clear, isExternal, enPc, we, weReg, re, muxSel;
clear <= dDone;
logic [2:0] op, wa, ad1, ad2, outPC;
logic [3:0] add, s4Control, s3Control, s2Control, s1Control, outMux, outALU, s0ALU, s1ALU;
logic [11:0] outMem, outInstruction;
logic cDone, lDone, rDone, uDone, dDone;

//module instantiations
debouncer debouncer0(center, clk, 0, cDone);
debouncer debouncer1(right, clk, 0, rDone);
debouncer debouncer2(left, clk, 0, lDone);
debouncer debouncer3( up, clk, 0, uDone);
debouncer debouncer4(down, clk, 0, dDone);

sevenSegmentFinal sevenSegment2 (clk, clear, s4Control, s3Control, s2Control, s1Control, disp,ans);
programCounter  programCounterT (clk, clear, enPc, outPC);
instructionMemory  instructionMemoryT (clk, clear, isExternal, rcrd1, outPC, sws[11:0], outMem);
instructionRegister instructionRegisterT (clk, clear, outMem, outInstruction);
dataMemory dataMemoryT (we, re, clk, clear, add, s0ALU, rd);
mux2to1 mux2to1T (muxSel, outALU, rd, outMux);
ALU_Unit ALU_UnitT (op, s0ALU, s1ALU, outALU);
registerFile registerFileT (weReg, clk, clear, rcrd2, ad1, ad2, wa,  outMux,  sws[15:9], s0ALU, s1Control);
controlUnit controllerT (cDone,uDone, lDone, rDone, op, re, ad1, ad2, wa, we, add, weReg, muxSel, enPc, outInstruction, isExternal, rcrd1, rcrd2, clk, clear, s0ALU, s1Control, outALU, s4Control, s3Control, s2Control, s1Control);

endmodule

//Test Module Final
`timescale 1ns/1ps
module basysTest (input logic center, up, left, right, down, clk, input logic [15:0] sws, output logic [6:0] disp, output logic [3:0] ans);

//all signals
logic rcrd1, rcrd2, clear, isExternal, enPc, we, weReg, re, muxSel;
clear <= dDone;
logic [2:0] op, wa, ad1, ad2, outPC;
logic [3:0] add, s4Control, s3Control, s2Control, s1Control, outMux, outALU, s0ALU, s1ALU;
logic [11:0] outMem, outInstruction;
logic cDone, lDone, rDone, uDone, dDone;

//module instantiations
debouncer debouncer0(center, clk, 0, cDone);
debouncer debouncer1(right, clk, 0, rDone);
debouncer debouncer2(left, clk, 0, lDone);
debouncer debouncer3( up, clk, 0, uDone);
debouncer debouncer4(down, clk, 0, dDone);

controlUnit controllerT (cDone,uDone, lDone, rDone, op, re, ad1, ad2, wa, we, add, weReg, muxSel, enPc, outInstruction, isExternal, rcrd1, rcrd2, clk, clear, s0ALU, s1Control, outALU, s4Control, s3Control, s2Control, s1Control);
programCounter  programCounterT (clk, clear, enPc, outPC);
instructionMemory  instructionMemoryT (clk, clear, isExternal, rcrd1, outPC, sws[11:0], outMem);
instructionRegister instructionRegisterT (clk, clear, outMem, outInstruction);
dataMemory dataMemoryT (we, re, clk, clear, add, s0ALU, rd);
registerFile registerFileT (weReg, clk, clear, rcrd2, ad1, ad2, wa,  outMux,  sws[15:9], s0ALU, s1Control);
ALU_Unit ALU_UnitT (op, s0ALU, s1ALU, outALU);
mux2to1 mux2to1T (muxSel, outALU, rd, outMux);
sevenSegmentFinal sevenSegment2 (clk, clear, s4Control, s3Control, s2Control, s1Control, disp,ans);

endmodule

//old and wrong
/*//simple processor testbench:
`timescale 1ns/1ps
module processor_Test();
reset, leftBtn, rightBtn, switchEn, switch, RF_addr2, RF_waddr, ALUSel, isExternal, wr_en,
7
logic clk, rightBtn, switchEn, leftBtn, reset; logic [11:0] switch; logic [11:0]IM; logic [6:0] seg; logic [3:0] an;
logic [3:0] Rel; logic dp;
Simple_Processor dut_sp ( clk, reset, leftBtn, rightBtn, switchEn,
switch,seg, dp, an, Rel, IM );
initial
    clk = 1;
    always begin
    #1; clk = ~clk;
    end
    initial begin
        #10; reset = 1;
        #15; reset = 0;
        #20; leftBtn = 1;
        #25; leftBtn = 0;
        #20; leftBtn = 1;
        #30; leftBtn = 0;
        #30; leftBtn = 1;
        #40; leftBtn = 0;
        #35; leftBtn = 1;
    end
endmodule*/