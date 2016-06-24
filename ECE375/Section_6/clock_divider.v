`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    12:08:19 05/05/2010
// Design Name:
// Module Name:    ClockDividerStage
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
module ClockDivider(
	input Clock,
	input Reset,
	output Clock_2,
	output Clock_4,
	output Clock_8,
	output Clock_16,
	output Clock_32,
	output Clock_64,
	output Clock_128,
	output Clock_256,
	output Clock_512,
	output Clock_1024);

	ClockDividerStage Divider_1 (
    .Clock(Clock),
    .Reset(Reset),
    .HalvedClock(Clock_2)
    );

	ClockDividerStage Divider_2 (
    .Clock(Clock_2),
    .Reset(Reset),
    .HalvedClock(Clock_4)
    );

	ClockDividerStage Divider_3 (
    .Clock(Clock_4),
    .Reset(Reset),
    .HalvedClock(Clock_8)
    );

	ClockDividerStage Divider_4 (
    .Clock(Clock_8),
    .Reset(Reset),
    .HalvedClock(Clock_16)
    );

	ClockDividerStage Divider_5 (
    .Clock(Clock_16),
    .Reset(Reset),
    .HalvedClock(Clock_32)
    );

	ClockDividerStage Divider_6 (
    .Clock(Clock_32),
    .Reset(Reset),
    .HalvedClock(Clock_64)
    );

	ClockDividerStage Divider_7 (
    .Clock(Clock_64),
    .Reset(Reset),
    .HalvedClock(Clock_128)
    );

	ClockDividerStage Divider_8 (
    .Clock(Clock_128),
    .Reset(Reset),
    .HalvedClock(Clock_256)
    );

	ClockDividerStage Divider_9 (
    .Clock(Clock_256),
    .Reset(Reset),
    .HalvedClock(Clock_512)
    );

	ClockDividerStage Divider_A (
    .Clock(Clock_512),
    .Reset(Reset),
    .HalvedClock(Clock_1024)
    );


endmodule

module ClockDividerStage(
    input Clock,
    input Reset,
	 output reg HalvedClock
    );

	always @ (posedge Clock, negedge Reset)
		if(!Reset) HalvedClock <= 0;
		else HalvedClock <= ~HalvedClock;
endmodule



