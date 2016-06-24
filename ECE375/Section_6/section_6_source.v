`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:38:11 05/21/2013 
// Design Name: 
// Module Name:    section_6_source 
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
module section_6_source(
    input reset,
	 input clk,
	 input l_bumper,
    input r_bumper,
    output reg len,
    output reg ldir,
    output reg ren,
    output reg rdir,
	 output reg [2:0]state,
	 output reg [4:0]state_out
    );
	 
	 
	 
	 ClockDivider instance_name (
    .Clock(Clock), 
    .Reset(Reset), 
    .Clock_2(Clock_2), 
    .Clock_4(Clock_4), 
    .Clock_8(Clock_8), 
    .Clock_16(Clock_16), 
    .Clock_32(Clock_32), 
    .Clock_64(Clock_64), 
    .Clock_128(Clock_128), 
    .Clock_256(Clock_256), 
    .Clock_512(Clock_512), 
    .Clock_1024(Clock_1024)
    );
	 
	 //state logic
	 stateswitch stateblock(
			.clk_s (Clock_2),
			.reset_s (reset),
			.l_bump (l_bumper),
			.r_bump (r_bumper),
			.switchedstate (state_out)
			);
	
	//output logic	
	decoder outputblock(
		.state (state),
		.state_out (state_out)
		);
always @ (*)		
if (state_out == 	5'b00001)
		begin len = 0; ldir = 1; ren = 0; rdir = 1; end
else if (state_out == 	5'b00010)
		begin len = 0; ldir = 0; ren = 0; rdir = 0; end	
else if (state_out == 	5'b00100)
		begin len = 1; ldir = 0; ren = 0; rdir = 1; end	
else if (state_out == 	5'b01000)
		begin len = 0; ldir = 0; ren = 0; rdir = 0; end	 
else if (state_out == 	5'b10000)
		begin len = 0; ldir = 1; ren = 0; rdir = 0; end

	

endmodule
	 




module stateswitch (input clk_s,
							input reset_s,
							input l_bump,
							input r_bump,
							output reg [2:0] switchedstate);
							
		reg [2:0] state = 0;
		reg [2:0] nextstate;
		
		
		parameter S0 = 3'b000;
		parameter S1 = 3'b001;
		parameter S2 = 3'b010;
		parameter S3 = 3'b011;				
		parameter S4 = 3'b100;

	 //state register
	 always@(posedge clk_s, posedge reset_s)
	 	if (reset_s) state <= S0;
	 	else state <= nextstate;
	 
	 //next state logic
	 always @ (*)
	 begin
		case(state)
			S0: if (~l_bump) nextstate = S3;
				 else if (~r_bump) nextstate = S1;
				 else nextstate = S0;
			S1: nextstate = S2;
			S2: nextstate = S0;
			S3: nextstate = S4;
			S4: nextstate = S0;
		endcase
		
		//output logic
		switchedstate = nextstate;
		end
		

	
		
endmodule




module decoder (input [2:0] state,
						output reg [4:0] state_out
					);
	always @ (*)
		case (state)
			3'b000: begin state_out = 5'b00001;	end
			3'b001: begin state_out = 5'b00010;	end
			3'b010: begin state_out = 5'b00100;	end
			3'b011: begin state_out = 5'b01000;	end
			3'b100: begin state_out = 5'b10000;	end
		endcase
endmodule

