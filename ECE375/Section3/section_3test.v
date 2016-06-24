// Verilog test fixture created from schematic F:\Section3\Section3_Schematic.sch - Tue May 14 13:22:50 2013

`timescale 1ns / 1ps

module Section3_Schematic_Section3_Schematic_sch_tb();

// Inputs
   reg A;
   reg B;
   reg C;

// Output
   wire Le;
   wire Ld;
   wire Re;
   wire Rd;

// Bidirs

// Instantiate the UUT
   Section3_Schematic UUT (
		.A(A), 
		.B(B), 
		.C(C), 
		.Le(Le), 
		.Ld(Ld), 
		.Re(Re), 
		.Rd(Rd)
   );
// Initialize Inputs

   initial begin
 A = 0; B= 0; C= 0;
#10 A = 0; B= 0; C= 1;
#10 A = 0; B= 1; C= 0;
#10 A = 0; B= 1; C= 1;
#10 A = 1; B= 0; C= 0;
#10 A = 1; B= 0; C= 1;
#10 A = 1; B= 1; C= 0;
#10 A = 1; B= 1; C= 1;

end
endmodule

