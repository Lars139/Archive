`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:12:31 05/22/2013
// Design Name:   ClockDivider
// Module Name:   Z:/Windows.Documents/My Documents/Sophomore/Section_6/Section_test.v
// Project Name:  Section_6
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ClockDivider
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Section_test;

	// Inputs
	reg Clock;
	reg Reset;

	// Outputs
	wire Clock_2;
	wire Clock_4;
	wire Clock_8;
	wire Clock_16;
	wire Clock_32;
	wire Clock_64;
	wire Clock_128;
	wire Clock_256;
	wire Clock_512;
	wire Clock_1024;

	// Instantiate the Unit Under Test (UUT)
	ClockDivider uut (
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

	initial begin
		// Initialize Inputs
		Clock = 0;
		Reset = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

