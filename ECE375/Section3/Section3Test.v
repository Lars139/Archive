// Verilog test fixture created from schematic Z:\Section3\Section3_Schematic.sch - Wed Apr 17 09:13:52 2013

`timescale 1ns / 1ps

module Section3_Schematic_Section3_Schematic_sch_tb();

// Inputs

// Output

// Bidirs

// Instantiate the UUT
   Section3_Schematic UUT (
		
   );
// Initialize Inputs
 
       initial begin
		 A = 0; B = 0; C = 0;
	#10 A = 0; B = 0; C = 1;
	#10 A = 0; B = 1; C = 0;
	#10 A = 0; B = 1; C = 1;
	#10 A = 1; B = 0; C = 0;
	#10 A = 1; B = 0; C = 1;
	#10 A = 1; B = 1; C = 0;
	#10 A = 1; B = 1; C = 1;
		 
   end
endmodule
