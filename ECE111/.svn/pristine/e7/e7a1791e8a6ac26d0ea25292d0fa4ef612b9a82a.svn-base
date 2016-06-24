/** 
 * @file
 * @author Joey Tomlinson
 * @version 1.0
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
 * Library for interfacing to a quadrature encoder.  
 * An interrupt is used to read the encoder increments.
 * The interrupt declaration is #defined as ROTARY_ENCODER_ISR.
 * To use this library, you need to include ROTARY_ENCODER_ISR in the
 * main file of your orogram.
 * 
 * @section HARDWARE
 * 
 * Target Device: ATTINY26L
 * 
 * Hardware Description:
 * 
 */

#include <avr/io.h>
#include <stdlib.h>
#include "delay.h"
#include "rotaryEncoder.h"

// Macros to get the encoder reading MSB and LSB
// The pins which the encoder are connected to are defined here.
#define ENC_MSB() bit_is_set(PINB, 0)
#define ENC_LSB() bit_is_set(PINB, 1)

// Global variables
unsigned int curPos; // stores the change in position since initRotary was run
unsigned char prev, cur; // stores the previous and current encoder readings

/**
 * Initialization function for rotary encoder. Sets the previous encoder
 * value to be whatever the pins are initially at.  Also sets the
 * current position of the rotary encoder to zero.
 * 
 * @param 1st bit of the rotary encoders output.
 * @param 2nd bit of the rotary encoders output.
 * 
 */
void initRotary(char lsb, char msb)
{
	prev = grayToDec(bit_is_set(PINB, msb) , bit_is_set(PINB, lsb));
	curPos = 0;
}

/**
 * Gets the change in position since initRotary was called.
 * 
 * @return current position of the rotary encoder.
 * 
 */
int getCurPos()
{
	return curPos;
}

/**
 * Takes two msb and lsb, and converts the 2 bit greycode to it's corresponding decimal value.
 * @param 1st bit of the rotary encoders output.
 * @param 2nd bit of the rotary encoders output.
 * 
*/
int grayToDec(char msb, char lsb)
{
	if(msb)
		cur = 3 - lsb;
	else
		cur = lsb;
	return cur;
}

/**
 * Pin change interrupt handler which runs when the encoder increments.
 * ROTARY_ENCODER_ISR is defined in the header file as an ISR macro (interrupt handler)
 * To use this library in your program you need to include ROTARY_ENCODER_ISR
 * in your source file
 * 
 */
void ISR_IO_PINS_vect() {
	
	//convert a and b into a decimal number
	cur = grayToDec(ENC_MSB, ENC_LSB);
	
	//comparasion on the decimal values of the inputs, determines if we need to add or subtract to current position.
	if ( (prev == 0) && (cur == 3) )
		curPos--;
	if ( (prev == 3) && (cur == 0) )
		curPos++;
	else if (prev > cur)
		curPos--;
	else
		curPos++;
		
	//checks to see if the current value of the rotary encorder is in bounds,  if not, adjusts value.
	if (curPos == 30)
		curPos = 0;
	else if (curPos == -1)
		curPos = 29;

	prev = cur;
}
