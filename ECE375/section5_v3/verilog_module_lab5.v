`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:35:00 05/09/2013 
// Design Name: 
// Module Name:    verilog_module_lab5 
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
module verilog_module_lab5(
    input A,
    input B,
    input C,
    input Al,
    input Ar,
    output Le,
    output Ld,
    output Re,
    output Rd
    );
	 
	 wire s1;
	 wire len;
	 wire ldir;
	 wire ren;
	 wire rdir;
	 supply0 GND;
	 
	/* Section3_Schematic UUT (
	 .A (A),
	.B (B),
	.C (C),
	.Re (ren),
	.Rd (rdir),
	.Le (len),
	.Ld (ldir)
	);*/
	
   section3_schematic UUT (
		.Re(ren), 
		.Ld(ldir), 
		.Rd(rdir), 
		.Le(len), 
		.B(B), 
		.C(C), 
		.A(A)
   );
	
// Bus1
Sc5 mux1(
    .Bi1(GND), 
    .Bi2(len), 
    .C(s1), 
    .Q(Le)
    );



// Bus2
Sc5 mux2 (
    .Bi1(Al), 
    .Bi2(ldir), 
    .C(s1), 
    .Q(Ld)
    );



// Bus3
Sc5 mux3 (
    .Bi1(GND), 
    .Bi2(ren), 
    .C(s1), 
    .Q(Re)
    );



// Bus0
Sc5 mux0(
    .Bi1(Ar), 
    .Bi2(rdir), 
    .C(s1), 
    .Q(Rd)
    );




assign s1 = Al & Ar;
endmodule

module Sc5(
	input [0:3] Bi1, Bi2,
	input C,
	output [0:3] Q
);
assign Q = C ? Bi1:Bi2;

endmodule


