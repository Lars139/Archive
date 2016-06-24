`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:49:41 05/29/2013 
// Design Name: 
// Module Name:    sevenSeg 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sevenSeg(
    input Le,
    input Ld,
    input Re,
    input Rd,
    output reg A,
    output reg B,
    output reg C,
    output reg D,
    output reg E,
    output reg F,
    output reg G,
    input reset,
    input clock
    );
	 wire I[3:0];
	 
	 always @ (posedge clock) //assign each input for each array
	 begin
	 I[0] <= Rd;
	 I[1] <= Re;
	 I[2]	<= Ld;
	 I[3] <= Le;
	 end
	 
	 always @ (*)
	 begin
		case(I)
		4'b0000: begin A<=1 ;B<=0 ;C<=0 ;D<=0 ;E<=1 ;F<=1 ;G<=1 ;end //forward display F
		4'b0101: begin A<=0 ;B<=0 ;C<=1 ;D<=1 ;E<=1 ;F<=1 ;G<=1 ;end //backward display b
		
		4'b0110: begin A<=0 ;B<=0 ;C<=0 ;D<=0 ;E<=1 ;F<=0 ;G<=1 ;end //swing right display r
		4'b0111: begin A<=0 ;B<=0 ;C<=0 ;D<=0 ;E<=1 ;F<=0 ;G<=1 ;end //swing right display r (last bit doesn't care)
		
		4'b1001: begin A<=0 ;B<=0 ;C<=0 ;D<=1 ;E<=1 ;F<=1 ;G<=0 ;end //swing left display L
		4'b1101: begin A<=0 ;B<=0 ;C<=0 ;D<=1 ;E<=1 ;F<=1 ;G<=0 ;end //swing left display L (last bit doesn't care)		
		
		endcase
	 end
	 
	 
	 
	 
	 
	 


endmodule
