//full-adder
`timescale 1ns/1ps
module fullAdder(input logic a , b , cin , output logic sum , cout );
    assign sum = a ^ b ^ cin;
    assign cout = (a & cin)|(b & cin)|(a & b) ;
endmodule

//2:1 mux
`timescale 1ns/1ps
module mux2to1(input logic S0, input logic [3:0] in0, in1, output logic [3:0] out);
    assign  out = S0 ? in0 : in1;
endmodule

//Program Counter Program_Counter
`timescale 1ns/1ps
module Program_Counter(input logic clk , load , reset, output logic [2:0] out);
    always_ff @(posedge clk, posedge reset)
    if (reset) begin
        out <= 0;
    end      
    else if (load) begin
        out <= out + 1;
    end
endmodule

//Instruction Register
`timescale 1ns/1ps
module Instruction_Register(input logic clk, ld, reset, enable, input logic [11:0] in0, in1,  output logic [11:0] result);
    always_ff @(posedge clk or posedge reset)
      if (reset) begin
        result <= 0;
        end
      else begin
         if (ld) begin
         case (enable)
         0: result <= in1;
         1: result <=  in0;
         endcase
         end
      end
endmodule

//Instruction Memory
`timescale 1ns/1ps
module Instruction_Memory( input logic [2:0] rda, output logic [11:0] rdd);
        always_comb
        case (rda)
        0: rdd = 12'b000_00_001_0011; //load rf[1} =  3
        1: rdd = 12'b000_00_000_0111; //load rf[0] = 7
        2: rdd = 12'b101_011_000_001; //rf[0] + rf[1] -> rf[3] = 10
        3: rdd = 12'b101_111_001_011; //rf[3] + rf[1] -> rf[7] = 13
        4: rdd = 12'b110_100_000_011; // rf[3] - rf[0] -> rf[4] = 3
        5: rdd = 12'b001_00_100_0101; //store d[5] = 3
        6: rdd = 12'b000_00_000_0101; //load rf[0] as d[5](3)
        7: rdd = 12'b101_111_001_000; //rf[7] = rf[0] + rf[1] = 6
        endcase      
endmodule 

//Controller
`timescale 1ns/1ps
module ControllerSP(input logic enable, clk, reset, debouncerLeft, debouncerRight, input logic [11:0] instructions,
output logic D_rd, D_wr, isExternal,
output logic [1:0] ALUSel, 
output logic wr_en, 
output logic [3:0] D_addr, 
output logic [2:0] RF_addr1, RF_addr2, RF_waddr);

    logic cntr_load;

    always_ff @(posedge clk, posedge reset)
    if (reset) begin
        ALUSel <= 0;
        D_rd <= 0;
        D_wr <= 0;
        isExternal <= 0; 
        wr_en <= 0; 
        D_addr <= 0;
        RF_addr1 <= 0;
        RF_addr2 <= 0;
        RF_waddr <= 0;
        cntr_load <= 0;   
    end
    
    else begin
        if((debouncerRight & enable) | (debouncerLeft & ~enable))
        begin           
            case( instructions[11:9] )
            
            3'b000:
            begin           
                isExternal <= 1;
                D_rd <=  1;
                D_wr <=  0;
                wr_en <=  1;
                ALUSel <= 0;
                RF_waddr <= instructions[6:4];
                D_addr <=  instructions[3:0];
                
                case ( cntr_load )
                0:
                begin
                cntr_load <= 1;
                RF_addr1  <= instructions[6:4];
                end
                1:
                begin
                cntr_load <= 0;
                RF_addr2  <= instructions[6:4];
                end
                endcase                 
            end
            
            3'b001:
            begin       
                cntr_load <= 1;      
                isExternal <= 0;   
                D_rd <= 0;
                D_wr <= 1;
                ALUSel <= 0;
                wr_en <= 0; 
                D_addr <= instructions[3:0];
                RF_addr1 <= instructions[6:4];
                case ( cntr_load )
                0:
                begin
                cntr_load <= 1;
                RF_addr1 <= instructions[6:4];
                end
                1:
                begin
                cntr_load <= 0;
                RF_addr2 <= instructions[6:4];
                end
                endcase 
            end
            
            3'b101:
            begin
                isExternal <= 0;
                D_rd <= 0;
                D_wr <= 0;
                ALUSel <= 2'b01;
                wr_en <= 1;
                RF_waddr <= instructions[8:6];
                RF_addr1 <= instructions[2:0];
                RF_addr2 <= instructions[5:3];
            end    
            
            3'b110:
            begin
                isExternal <= 0; 
                D_rd <= 0;
                D_wr <= 0;
                ALUSel <= 2'b10;
                wr_en <= 1;
                RF_waddr <= instructions[8:6];
                RF_addr1 <= instructions[2:0];
                RF_addr2 <= instructions[5:3];     
            end
            endcase 
         end   
    end          
endmodule 

//Control Unit
`timescale 1ns/1ps
module Control_Unit(input logic clk, reset, debouncerLeft, debouncerRight, enable, input logic[11:0] switches,
output logic [3:0] D_addr, 
output logic D_rd, D_wr, 
output logic [2:0] RF_addr1, RF_addr2, RF_waddr, 
output logic [1:0] ALUSel,
output logic isExternal, wr_en);
    
    logic cntr_load, IR_ld;
    logic [2:0] PC_out;
    logic [2:0] PC_index;
    logic [11:0] instructions;
    logic [11:0] IM_ins;
    logic [11:0] IR_ins;
    assign IR_ld = 1;
    
    Program_Counter p_c(clk, debouncerLeft, reset, PC_index);        
    Instruction_Memory instruction_memory(PC_index, IM_ins);
    Instruction_Register i_r(clk, IR_ld, reset, enable, switches, IM_ins, instructions);

    ControllerSP  controller1(enable, clk, reset, debouncerLeft, debouncerRight, instructions, D_rd, D_wr, isExternal, ALUSel, wr_en,
    D_addr, RF_addr1, RF_addr2, RF_waddr);
endmodule

//Data Memory
`timescale 1ns/1ps
module Data_Memory(input logic D_rd, D_wr, clk, reset, input logic [3:0] D_addr, W_data, output logic [3:0] R_data); 
   
    logic [3:0] data_mem [15:0];
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
          R_data <= 0;
          data_mem[0]  <=  4'h0;
          data_mem[1]  <=  4'h1;
          data_mem[2]  <=  4'h2;
          data_mem[3]  <=  4'h3;
          data_mem[4]  <=  4'h4;
          data_mem[5]  <=  4'h5;
          data_mem[6]  <=  4'h6;
          data_mem[7]  <=  4'h7;
          data_mem[8]  <=  4'h8;
          data_mem[9]  <=  4'h9;
          data_mem[10] <=  4'hA;
          data_mem[11] <=  4'hB;
          data_mem[12] <=  4'hC;
          data_mem[13] <=  4'hD;
          data_mem[14] <=  4'hE;
          data_mem[15] <=  4'hF;
        end
        
        else begin
           if (D_rd)
                R_data  <=  data_mem[D_addr];
                
           else if (D_wr)
                data_mem [D_addr]  <=  W_data;
                
        end
    end
endmodule

//Register File
`timescale 1ns/1ps
module Register_File(input logic  clk, wr_en, reset, input logic [2:0] rda1, rda2, wra, input logic [3:0] wrd, output logic [3:0] rdd1, rdd2);
    logic cntr_load;
    logic [3:0] data [7:0];

    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
          data[0]  <= 0;
          data[1]  <= 0;
          data[2]  <= 0;
          data[3]  <= 0;
          data[4]  <= 0;
          data[5]  <= 0;
          data[6]  <= 0;
          data[7]  <= 0;
          cntr_load <= 0;
        end
        
        else
        begin
            if (wr_en)
                data[wra]  <=  wrd;  
            rdd1  <=  data[rda1];
            rdd2  <=  data[rda2]; 
        end
    end  
endmodule

//ALU
`timescale 1ns/1ps
module ALU(input logic [3:0] in1, in2, input logic [1:0] Sel, output logic [3:0] Rel);
     
    logic [3:0] sum;
    logic [3:0] sum2;
    logic [3:0] cout;
    logic [3:0] cout2;
    
    fullAdder add0(in1[0], in2[0], 0, sum[0], cout[0]);
    fullAdder add1(in1[1], in2[1], cout[0], sum[1], cout[1]);
    fullAdder add2(in1[2], in2[2], cout[1], sum[2], cout[2]);
    fullAdder add3(in1[3], in2[3], cout[2], sum[3], cout[3]);
        
    fullAdder subtract0(in1[0], ~in2[0], 1, sum2[0], cout2[0]);
    fullAdder subtract1(in1[1], ~in2[1], cout2[0], sum2[1], cout2[1]);
    fullAdder subtract2(in1[2], ~in2[2], cout2[1], sum2[2], cout2[2]);
    fullAdder subtract3(in1[3], ~in2[3], cout2[2], sum2[3], cout2[3]);
    
    always_comb begin
            case(Sel)
            0: Rel = 0;
            1: Rel = sum;
            2: Rel = sum2;
            3: Rel = 0;
            endcase
        end
endmodule

//Debouncer
`timescale 1ns/1ps
module debouncer(input logic clk, input logic button, output logic pulse);
    logic [24:0] timer;
    typedef enum logic [1:0]{S0,S1,S2,S3} states;
    states state, nextState;
    logic gotInput;
    
    always_ff@(posedge clk) begin    
            state <= nextState;
            if(gotInput)
                timer <= 25000000;
            else
                timer <= timer - 1;
        end
    always_comb
        case(state)
            S0: if(button) begin 
                    //startTimer
                    nextState = S1;    
                    gotInput = 1;
                end
                else begin nextState = S0; gotInput = 0; end
            S1: begin nextState = S2; gotInput = 0; end
            S2: begin nextState = S3; gotInput = 0; end
            S3: begin if(timer == 0) nextState = S0; else nextState = S3; gotInput = 0; end
            default: begin nextState = S0; gotInput = 0; end
            endcase
    assign pulse = ( state == S1 );
endmodule

//Datapath
`timescale 1ns/1ps
module Datapath (input logic [3:0] Ext_Data, input logic [2:0] Addr_Src1, Addr_Src2, Addr_Dest, input logic isExternal, clk, push_Button, reset,
input logic [1:0] ALUSel, output [6:0]seg, logic dp ,  output  [3:0] an ,   output logic  [3:0] rdd1);
    
    logic buttonPulse;
    logic [3:0] data;
    logic [3:0] Rel;
    logic [3:0] rdd2;

    mux2to1 mux1(isExternal, Ext_Data, Rel, data);
    debouncer debouncer1(clk, push_Button, buttonPulse);
    Register_File register_file1 (clk, buttonPulse, reset, Addr_Src1, Addr_Src2, Addr_Dest, data, rdd1, rdd2);
    ALU alu1 (rdd1, rdd2, ALUSel, Rel); 
    SevenSegmentDisplay sevenSegment1(clk, rdd1, rdd2, 0, Rel, seg, dp, an); 
endmodule

//Seven Segment Display
`timescale 1ns/1ps
module SevenSegmentDisplay(input clk, input [3:0] in3, in2, in1, in0, output [6:0]seg, logic dp, output [3:0] an);
    
    localparam N = 18;
    logic [N-1:0] count = {N{1'b0}};
    always@ (posedge clk)
        count <= count + 1;
    
    logic [4:0]digit_val;
    logic [3:0]digit_en;
     
    always@ (*) begin
    digit_en = 4'b1111;
    digit_val = in0;
     
      case(count[N-1:N-2])
        
       2'b00 :  //select first 7Seg.
        begin
         digit_val = {1'b0, in0};
         digit_en = 4'b1110;
        end
        
       2'b01:  //select second 7Seg.
        begin
         digit_val = {1'b0, in1};
         digit_en = 4'b1101;
        end
        
       2'b10:  //select third 7Seg.
        begin
         digit_val = {1'b0, in2};
         digit_en = 4'b1011;
        end
         
       2'b11:  //select forth 7Seg.
        begin
         digit_val = {1'b0, in3};
         digit_en = 4'b0111;
        end
      endcase
     end
     
    
    //Convert digit number to LED vector. LEDs are active low.
    logic [6:0] sseg_LEDs; 
    always @(*)
     begin 
      sseg_LEDs = 7'b1111111; //default
      case( digit_val)
       5'd0 : sseg_LEDs = 7'b1000000; //to display 0
       5'd1 : sseg_LEDs = 7'b1111001; //to display 1
       5'd2 : sseg_LEDs = 7'b0100100; //to display 2
       5'd3 : sseg_LEDs = 7'b0110000; //to display 3
       5'd4 : sseg_LEDs = 7'b0011001; //to display 4
       5'd5 : sseg_LEDs = 7'b0010010; //to display 5
       5'd6 : sseg_LEDs = 7'b0000010; //to display 6
       5'd7 : sseg_LEDs = 7'b1111000; //to display 7
       5'd8 : sseg_LEDs = 7'b0000000; //to display 8
       5'd9 : sseg_LEDs = 7'b0010000; //to display 9
       5'd10: sseg_LEDs = 7'b0001000; //to display a
       5'd11: sseg_LEDs = 7'b0000011; //to display b
       5'd12: sseg_LEDs = 7'b1000110; //to display c
       5'd13: sseg_LEDs = 7'b0100001; //to display d
       5'd14: sseg_LEDs = 7'b0000110; //to display e
       5'd15: sseg_LEDs = 7'b0001110; //to display f   
       5'd16: sseg_LEDs = 7'b0110111; //to display "="
       default : sseg_LEDs = 7'b0111111; //dash
      endcase
    end
     
    assign an = digit_en;
    assign seg = sseg_LEDs; 
    assign dp = 1'b1; //turn dp off
    
endmodule

//Basys Test Simple Processor
`timescale 1ns/1ps
module SPTestBasys(input logic clk, reset, leftBtn, rightBtn, switchEn, [11:0] switches, output [6:0] seg, logic dp, output [3:0] an);
    
    logic D_wr;
    logic D_rd;
    logic isExternal;
    logic wr_en;
    logic debouncerLeft;
    logic debouncerRight;
    logic [1:0] ALUSel;
    logic [3:0] D_addr;
    logic [3:0] Data_mem_read;
    logic [3:0] rdd1;
    logic [2:0] RF_waddr;
    logic [2:0] RF_addr1;
    logic [2:0] RF_addr2;
    
    debouncer debbouncer_i_m(clk , leftBtn , debouncerLeft);
    debouncer debouncer_switch2(clk , rightBtn , debouncerRight);
    Control_Unit control_unit2(clk , reset , debouncerLeft , debouncerRight , switchEn , switches , D_addr , D_rd , D_wr , RF_addr1 , RF_addr2 , RF_waddr , ALUSel , isExternal , wr_en);    
    Data_Memory data_memory2(D_rd , D_wr , clk , reset , D_addr , rdd1 , Data_mem_read);                                                                                            
    Datapath datapath2(Data_mem_read , RF_addr1 , RF_addr2 , RF_waddr , isExternal , clk ,  wr_en , reset , ALUSel , seg , dp , an , rdd1);
endmodule

//Testbenches
//control unit testbench:
`timescale 1ns/1ps
module control_Unit_Test();

    logic clk, reset, leftBt, rightBt, switchEn; logic [11:0] switch;
    logic [3:0] D_addr;
    logic D_rd, D_wr;
    logic [2:0] RF_addr1;
    logic [2:0] RF_addr2;
    logic [2:0] RF_waddr;
    logic [1:0]ALUSel;
    logic isExternal, wr_en;
    logic[11:0] IM_ins ;
    Control_Unit dut(clk, reset, leftBtn, rightBtn, switchEn, switch, D_addr,
    D_rd, D_wr, RF_addr1, RF_addr2, RF_waddr, ALUSel, isExternal, wr_en, IM_ins);
    initial
    clk = 1;
    always begin 
    #15; clk = ~clk; 
    end
    initial begin 
        #10; reset = 1; 
        #10; reset = 0; 
        #20; leftBtn = 1; 
        #30; leftBtn = 0; 
        #20; leftBtn = 1; 
        #50; leftBtn = 0; 
        #20; leftBtn = 1; 
        #30; leftBtn= 0; 
        #20; leftBtn = 1; 
    end
endmodule

//simple processor testbench:
`timescale 1ns/1ps
module processor_Test();
    logic clk, rightBtn, switchEn, leftBtn, reset; logic [11:0] switch;
    logic [11:0]IM; logic [6:0] seg; logic [3:0] an;
    logic [3:0] Rel; logic dp;
    Simple_Processor dut_sp ( clk, reset, leftBtn, rightBtn, switchEn, switch,seg, dp, an, Rel, IM );
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
endmodule