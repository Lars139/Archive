////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//   ____  ____ 
//  /   /\/   / 
// /___/  \  /    Vendor: Xilinx 
// \   \   \/     Version : 14.1
//  \   \         Application : sch2hdl
//  /   /         Filename : Section3_Schematic.vf
// /___/   /\     Timestamp : 04/17/2013 09:19:14
// \   \  /  \ 
//  \___\/\___\ 
//
//Command: sch2hdl -intstyle ise -family xc9500xl -verilog Z:/Section3/Section3_Schematic.vf -w Z:/Section3/Section3_Schematic.sch
//Design Name: Section3_Schematic
//Device: xc9500xl
//Purpose:
//    This verilog netlist is translated from an ECS schematic.It can be 
//    synthesized and simulated, but it should not be modified. 
//
`timescale 1ns / 1ps

module Section3_Schematic(A, 
                          B, 
                          C, 
                          Ld, 
                          Le, 
                          Rd, 
                          Re);

    input A;
    input B;
    input C;
   output Ld;
   output Le;
   output Rd;
   output Re;
   
   wire XLXN_3;
   wire XLXN_4;
   wire XLXN_5;
   wire XLXN_6;
   wire XLXN_7;
   wire XLXN_8;
   wire XLXN_9;
   wire XLXN_10;
   wire XLXN_11;
   wire XLXN_12;
   wire XLXN_13;
   wire XLXN_14;
   wire XLXN_15;
   wire XLXN_16;
   wire XLXN_17;
   wire XLXN_20;
   wire XLXN_24;
   
   AND2  XLXI_2 (.I0(XLXN_12), 
                .I1(XLXN_11), 
                .O(XLXN_3));
   AND2  XLXI_3 (.I0(XLXN_13), 
                .I1(XLXN_17), 
                .O(XLXN_4));
   AND2  XLXI_6 (.I0(XLXN_15), 
                .I1(XLXN_14), 
                .O(XLXN_7));
   AND2  XLXI_7 (.I0(XLXN_24), 
                .I1(XLXN_16), 
                .O(XLXN_8));
   INV  XLXI_8 (.I(XLXN_17), 
               .O(XLXN_6));
   INV  XLXI_9 (.I(XLXN_24), 
               .O(XLXN_10));
   OR2  XLXI_10 (.I0(XLXN_4), 
                .I1(XLXN_3), 
                .O(XLXN_5));
   OR2  XLXI_11 (.I0(XLXN_8), 
                .I1(XLXN_7), 
                .O(XLXN_9));
   IBUF  XLXI_15 (.I(A), 
                 .O(XLXN_17));
   IBUF  XLXI_16 (.I(B), 
                 .O(XLXN_20));
   IBUF  XLXI_17 (.I(C), 
                 .O(XLXN_24));
   (* SLEW = "SLOW" *) 
   OBUF  XLXI_18 (.I(XLXN_5), 
                 .O(Le));
   (* SLEW = "SLOW" *) 
   OBUF  XLXI_19 (.I(XLXN_6), 
                 .O(Ld));
   (* SLEW = "SLOW" *) 
   OBUF  XLXI_20 (.I(XLXN_9), 
                 .O(Re));
   (* SLEW = "SLOW" *) 
   OBUF  XLXI_21 (.I(XLXN_10), 
                 .O(Rd));
   INV  XLXI_22 (.I(XLXN_20), 
                .O(XLXN_11));
   INV  XLXI_23 (.I(XLXN_24), 
                .O(XLXN_12));
   INV  XLXI_24 (.I(XLXN_20), 
                .O(XLXN_13));
   INV  XLXI_25 (.I(XLXN_17), 
                .O(XLXN_14));
   INV  XLXI_26 (.I(XLXN_20), 
                .O(XLXN_15));
   INV  XLXI_27 (.I(XLXN_20), 
                .O(XLXN_16));
endmodule
