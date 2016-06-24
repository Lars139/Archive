`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:27:56 05/09/2013
// Design Name:   verilog_module_lab5
// Module Name:   Z:/Windows.Documents/My Documents/Sophomore/section5_v3/VerilogTest.v
// Project Name:  section5_v3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: verilog_module_lab5
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module VerilogTest;

	// Inputs
	reg A;
	reg B;
	reg C;
	reg Al;
	reg Ar;

	// Outputs
	wire Le;
	wire Ld;
	wire Re;
	wire Rd;

	// Instantiate the Unit Under Test (UUT)
	verilog_module_lab5 uut (
		.A(A), 
		.B(B), 
		.C(C), 
		.Al(Al), 
		.Ar(Ar), 
		.Le(Le), 
		.Ld(Ld), 
		.Re(Re), 
		.Rd(Rd)
	);

	initial begin
		// Initialize Inputs
		A = 0; B = 0; C = 0; Al = 1; Ar = 1;
#10   A = 0; B = 0; C = 0; Al = 1; Ar = 1;
#10   A = 0; B = 0; C = 1; Al = 1; Ar = 1;
#10   A = 0; B = 1; C = 0; Al = 1; Ar = 1;
#10   A = 0; B = 1; C = 1; Al = 1; Ar = 1;
#10   A = 1; B = 0; C = 0; Al = 1; Ar = 1;
#10   A = 1; B = 0; C = 1; Al = 1; Ar = 1;
#10   A = 1; B = 1; C = 0; Al = 1; Ar = 1;
#10   A = 1; B = 1; C = 1; Al = 1; Ar = 1;


		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

