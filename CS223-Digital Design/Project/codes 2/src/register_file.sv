`timescale 1ns / 1ps

module register_file(RF_d1,RF_d2,RF_ad1,RF_ad2,RF_wa,RF_we,RF_wd,clk,rst);
input logic RF_we,clk,rst;
input logic [2:0] RF_ad1,RF_ad2,RF_wa;
input logic [3:0] RF_wd;
output logic [3:0] RF_d1,RF_d2;

logic [3:0] registers [7:0];

always_ff@(posedge clk or posedge rst)
begin
    if(rst==1)
    begin
        registers[0] <= 2;
        registers[1] <= -3;
        registers[2] <= 0;
        registers[3] <= 0;
        registers[4] <= 0;
        registers[5] <= 0;
        registers[6] <= 0;
        registers[7] <= 0;
        
        RF_d1 <= 0;
        RF_d2 <= 0;
    end
    else begin
        if(RF_we==1) // write RF_wd to RF_wa
        begin
            registers[RF_wa] <= RF_wd;
        end
        else // read from RF_ad1 and RF_ad2, to RF_d1 and RF_d2
        begin
            RF_d1 <= registers[RF_ad1];
            RF_d2 <= registers[RF_ad2];
        end
    
    end

end


endmodule
