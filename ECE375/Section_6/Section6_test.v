`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:29:39 05/22/2013
// Design Name:   section_6_source
// Module Name:   Z:/Windows.Documents/My Documents/Sophomore/Section_6/Section6_test.v
// Project Name:  Section_6
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: section_6_source
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Section6_test;

	// Inputs
	reg reset;
	reg clk;
	reg l_bumper;
	reg r_bumper;

	// Outputs
	wire len;
	wire ldir;
	wire ren;
	wire rdir;
	wire [2:0] state;

	// Instantiate the Unit Under Test (UUT)
	section_6_source uut (
		.reset(reset), 
		.clk(clk), 
		.l_bumper(l_bumper), 
		.r_bumper(r_bumper), 
		.len(len), 
		.ldir(ldir), 
		.ren(ren), 
		.rdir(rdir),
		.state(state)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		forever #5 clk = ~clk;
		end
	initial begin
	reset = 1;	l_bumper = 1;	r_bumper = 1;
#10	reset = 0;	l_bumper = 1;	r_bumper = 1;
#50	reset = 0;  l_bumper = 1;  r_bumper = 0;
#10	reset = 0;	l_bumper = 1;	r_bumper = 1;



		// Wait 100 ns for global reset to finish
		#180;
        
		// Add stimulus here

	end
      
endmodule

