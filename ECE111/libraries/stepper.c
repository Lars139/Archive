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
 * Hardware Description: By default a stepper motor is connected to PORTA pins 4-7 as follows:
 * PA4: Disable2; PA5: Phase2; PA6: Disable1; PA7: Phase1
 * This can be changed using the #defines below
 * 
 */

#include <avr/io.h>
#include <stdlib.h>

/* This is the step pattern for the stepper motor.  By default, the 4 phases of the motor
 * are connected to PORTA pins 4-7.  These #defines can be changed to use different pins
 */
#define step1 (PORTA = 0b10010000)
#define step2 (PORTA = 0b01100000)
#define step3 (PORTA = 0b10000000)
#define step4 (PORTA = 0b00100000)

// Global variable, used to keep track of which step (defined above) is to be executed next.
char currStep = 0;

/**
	Turns the strepper motor in a specified direction, at a specificed speed, for a specificed
	number of steps.
	
	@Param direction to turn. 1 is forward, 0 is reverse
	@Param time time between steps in milliseconds
	@Param stepNumber number of steps to take
*/
void runStepperMotor( unsigned short int direction,  int time, int stepNumber) 
{
	int i;
	if (direction == 1)
	{
		for(i = 0; i < stepNumber; i++)
		{
			currStep++;
			if(currStep == 4)
				currStep = 0;
			takeStep();
			delay(time);
		}
	}
	if(direction == 0)
	{
		for(i = 0; i < stepNumber; i++)
		{
			currStep--;
			if (currStep <0)
				currStep = 3;
			takeStep();
			delay(time);
		}
	}
}

/**
 * Function used to execute the cycle needed to have the motor take a single step.
 * 
 */
void takeStep(void)
{
	if (currStep == 0) 
		step1;
	else if (currStep == 1) 
		step2;
	else if (currStep == 2) 
		step3;
	else if (currStep == 3) 
		step4;
}
