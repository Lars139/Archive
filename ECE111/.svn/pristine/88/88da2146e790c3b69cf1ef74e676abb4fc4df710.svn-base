/** 
 * @file
 * @author Scott Rosenbalm
 * @author Joey Tomlinson
 * @author David Overgaard
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * @section DESCRIPTION
 * 
 * This library provides functionality for generating sound with the ATTINY26 microcontroller
 * 
 * Target Device: ATTINY26L
 * 
 * Hardware Description:
 * Small speaker connected between PB6 and GND (speaker pin configurable with #defines below)
 * 
 */

#include <avr/io.h>
#include <stdlib.h>
#include "sound.h"

/* #define statements are sometimes used to define macros.
 * On the surface, macros function similary to functions.  However, instead of being processed as functions by the compiler,
 * They are inserted into the code before the compiler runs.  The discussion of when to use macros vs functions vs inline functions
 * is beyond the scope of this document.  In this case, a macro is used so the port which the speaker is connected to can be
 * conveniently modified
 */

// This macro sets the speaker line low
// & is the bitwise and opperator.  This works because 1&x=x and 0&x=0
#define SPKR_LOW() *speakerPort &= ~(1 << speakerPin)

unsigned char* speakerPort;
unsigned char speakerPin;

/**
 * Sets up TIMER1 and SIG_OUTPUT_COMPARE1A interrupt to use for speaker functionality.
 * 
 */
void setupSpeaker(unsigned char* spkrPort, unsigned char spkrPin) {
	// One of the ATTINY26 built in hardware timers is used to generate the square wave that is sent to the speaker
	// Here we set up TIMER1 to serve this function.  See the about_timers.txt file in this directory for more information about how this works.
	TCCR0B = 0b00000100; //set TIMER0 clock to clk/256 = 3906.25Hz
	TCCR1A = 0b00000000; //Disconnect timer/counter1 from output pins and disable PWM mode
	TCCR1B = 0b00000101; // set TIMER1 clock to clk/16 = 1mhz/16 = 62.5kHz
	TCNT0L = 0x00; //initalize TIMER0 to 0
	TCNT1 = 0x00; //initialize TIMER1 to 0
	TIMSK |= (1 << OCIE1A) | (1 << TOIE0); //Enable Timer/Counter, and compare interrupts
	OCR1A = 80; // sets initial TIMER1 COMPARE A to 80.  This causes the SIG_OUTPUT_COMPARE1A interupt to fire every time TCNT1=80
	speakerPort = spkrPort;
	speakerPin = spkrPin;
}

/**
 * @brief Sets the value to compare with timer/counter1.  This sets the frequency generated on the square wave output for the speaker.
 * 
 */
void setFrequency(unsigned char frequency) {
	OCR1A = frequency;
}

/**
 * @brief Enables speaker output by enabling the compare match interrupt.
 * 
 */
void speakerOn() {
	TIMSK |= (1 << OCIE1A); // enable OCIE1A interupt
}

/**
 * @brief Disables speaker output by disabling the compare match interrupt for timer/counter1.
 * 
 */
void disableSpeaker() {
	TIMSK &= ~(1 << OCIE1A); // disable OCIE1A interupt
	SPKR_LOW(); // make sure the speaker isn't left in the on state to avoid dc current flowing through the speaker
}

/* 	Since the Tiny26/l has limited memory space (2kB) each measure of Mario has been defined as a function.
	Since many measures of the Mario main theme are the same, code size can be reduced by storing the code for
	each measure in one location and then telling the program to jump to that location in memory whenever that
	measure appears in the song.  This is what is happening each time a measure function is called.
	
	Half notes and whole notes/rest were also intentionally left out to conserve code space.  To implement
	these notes, simply use repeaded QuarterNote or QuarterRest functions.
*/
//It's always a good idea to specify the parameter as void to ensure no complications during compling.
void MeasureOne(void)
{
	EighthNote(FREQ_E_H);
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_E_H);
	EighthRest();
}

void MeasureTwo(void)
{
	EighthNote(FREQ_G_H);
	EighthRest();
	QuarterRest();
	EighthNote(FREQ_G);
	EighthRest();
	QuarterRest();
}

void MeasureThree(void)
{
	EighthNote(FREQ_C_H);
	QuarterRest();				
	EighthNote(FREQ_G);
	QuarterRest();
	EighthNote(FREQ_E);
	EighthRest();
}
			
void MeasureFour(void)
{
	EighthNote(FREQ_A);
	EighthRest();
	EighthNote(FREQ_B);
	EighthRest();
	EighthNote(FREQ_AS);
	EighthNote(FREQ_A);
	EighthRest();
}

void MeasureFive(void)
{
	EighthNote(FREQ_G);
	EighthRest();
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_G_H);
	EighthRest();
	EighthNote(FREQ_A_H);
	EighthRest();
	EighthNote(FREQ_F_H);
	EighthNote(FREQ_G_H);
}

void MeasureSix(void)
{
	EighthRest();
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_D_H);
	EighthNote(FREQ_B);
	QuarterRest();
}

void MeasureSeven(void)
{
	QuarterRest();
	EighthNote(FREQ_G_H);
	EighthNote(FREQ_FS_H);
	EighthNote(FREQ_F_H);
	EighthNote(FREQ_DS_H);
	EighthRest();
	EighthNote(FREQ_E_H);
}

void MeasureEight(void)
{
	EighthRest();
	EighthNote(FREQ_GS);
	EighthNote(FREQ_A);
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_A);
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_D_H);
}

void MeasureNine(void)
{	
	QuarterRest();
	EighthNote(FREQ_G_H);
	EighthNote(FREQ_FS_H);
	EighthNote(FREQ_F_H);
	EighthNote(FREQ_DS_H);
	EighthRest();
	EighthNote(FREQ_E_H);
}

void MeasureTen(void)
{	
	EighthRest();
	EighthNote(FREQ_C_HH);
	EighthRest();
	EighthNote(FREQ_C_HH);
	EighthNote(FREQ_C_HH);
	EighthRest();
	QuarterRest();
}

void MeasureEleven(void)
{
	QuarterRest();
	EighthNote(FREQ_G_H);
	EighthNote(FREQ_FS_H);
	EighthNote(FREQ_F_H);
	EighthNote(FREQ_DS_H);
	EighthRest();
	EighthNote(FREQ_E_H);
}

void MeasureTwelve(void)
{	
	EighthRest();
	EighthNote(FREQ_GS);
	EighthNote(FREQ_A);
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_A);
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_D_H);
}

void MeasureThirteen(void)
{	
	QuarterRest();
	EighthNote(FREQ_DS_H);
	QuarterRest();
	EighthNote(FREQ_D_H);
	QuarterRest();
}

void MeasureFourteen(void)
{	
	EighthNote(FREQ_C_H);
	EighthRest();
	QuarterRest();
	QuarterRest();
	QuarterRest();
}

void MeasureFifteen(void)
{
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_D_H);
	EighthRest();
}

void MeasureSixteen(void)
{	
	EighthNote(FREQ_E_H);
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_A);
	EighthNote(FREQ_G);
	EighthRest();
	QuarterRest();
}

void MeasureSeventeen(void)
{	
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_D_H);
	EighthNote(FREQ_E_H);
}

void MeasureEighteen(void)
{	
	QuarterRest();
	QuarterRest();
	QuarterRest();
	QuarterRest();
}

void MeasureNineteen(void)
{
	EighthNote(FREQ_E_H);
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_C_H);
	EighthNote(FREQ_E_H);
	EighthRest();
}

void MeasureTwenty(void)
{	
	EighthNote(FREQ_G_H);
	EighthRest();
	QuarterRest();
	EighthNote(FREQ_G);
	EighthRest();
	QuarterRest();
}

void MeasureTwentyOne(void)
{
	EighthRest();
	EighthNote(FREQ_D_H);
	EighthRest();
	EighthNote(FREQ_D_H);
	EighthNote(FREQ_D_H);
	QuarterRest();
	EighthNote(FREQ_DS_H);
	EighthRest();
	EighthNote(FREQ_DS_H);
	EighthNote(FREQ_DS_H);
	QuarterRest();
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_E_H);
	EighthNote(FREQ_E_H);
	EighthRest();
	EighthNote(FREQ_F_H);
	EighthRest();
	QuarterNote(FREQ_F_H);
	QuarterNote(FREQ_F_H);
	QuarterNote(FREQ_F_H);
	QuarterNote(FREQ_F_H);
	QuarterRest();
}