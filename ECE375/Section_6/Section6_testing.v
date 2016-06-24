`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:20:28 05/22/2013
// Design Name:   section_6_source
// Module Name:   Z:/Windows.Documents/My Documents/Sophomore/Section_6/Section6_testing.v
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

module Section6_testing;

	// Inputs
	reg reset;
	reg clk;
	reg l_bumper;
	reg b_bumper;

	// Outputs
	wire len;
	wire ldir;
	wire ren;
	wire rdir;

	// Instantiate the Unit Under Test (UUT)
	section_6_source uut (
		.reset(reset), 
		.clk(clk), 
		.l_bumper(l_bumper), 
		.b_bumper(b_bumper), 
		.len(len), 
		.ldir(ldir), 
		.ren(ren), 
		.rdir(rdir)
	);

	initial begin
		// Initialize Inputs
		reset = 1;	clk = 0;	l_bumper = 0;	b_bumper = 0;
#10	reset = 1;	clk = 0;	l_bumper = 0;	b_bumper = 1;
#10	reset = 1;	clk = 0;	l_bumper = 1;	b_bumper = 0;
#10	reset = 1;	clk = 0;	l_bumper = 1;	b_bumper = 1;
#10	reset = 1;	clk = 1;	l_bumper = 0;	b_bumper = 0;
#10	reset = 1;	clk = 1;	l_bumper = 0;	b_bumper = 1;
#10	reset = 1;	clk = 1;	l_bumper = 1;	b_bumper = 0;
#10	reset = 1;	clk = 1;	l_bumper = 1;	b_bumper = 1;

#10	reset = 0;	clk = 0;	l_bumper = 0;	b_bumper = 0;
#10	reset = 0;	clk = 0;	l_bumper = 0;	b_bumper = 1;
#10	reset = 0;	clk = 0;	l_bumper = 1;	b_bumper = 0;
#10	reset = 0;	clk = 0;	l_bumper = 1;	b_bumper = 1;
#10	reset = 0;	clk = 1;	l_bumper = 0;	b_bumper = 0;
#10	reset = 0;	clk = 1;	l_bumper = 0;	b_bumper = 1;
#10	reset = 0;	clk = 1;	l_bumper = 1;	b_bumper = 0;
#10	reset = 0;	clk = 1;	l_bumper = 1;	b_bumper = 1;

#10	reset = 0;	clk = 0;	l_bumper = 0;	b_bumper = 0;


		// Wait 100 ns for global reset to finish
		#180;
        
		// Add stimulus here

	end
      
endmodule

