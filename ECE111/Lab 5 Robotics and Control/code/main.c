/** 
 * @file
 * @author Scott Rosenbalm
 * @author Joey Tomlinson
 * @author David Overgaard
 * @version 2.0
 *
 * @note Edited by Robert L. Phillips III
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
 * This program implements a servo motor controller.  It detects a motor's
 * position using a potentiometer and uses a proportional-derivative control
 * system to control the motor's speed in order to move the motor to its target
 * position.
 * 
 * @section HARDWARE
 * 
 * Target Device: ATTINY26L
 * 
 */

 /**
@brief The system clock frequency is defined as specified in the tiny26 datasheet.
@details The default clock frequency for the tiny26 is 1MHz.  This define is used by the _ms_delay() function in delay.h to introduce accurate delays. 
*/
#define F_CPU 1000000UL

#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "motor_ctl.h"
#include "adc.h"
 
// Motor states

/**
@brief Stopped motor state
*/
#define STOP 0

/**
@brief Left turn motor state
*/
#define LEFT 1

/**
@brief Right turn motor state
*/
#define RIGHT 2

// ADC channels

/**
@brief ADC channel 0 (PA0)
*/
#define DESTINATION_ADC 0

/**
@brief ADC channel 5 (PA6)
*/
#define FEEDBACK_ADC 5

// Global Variables

/**
@brief Proportional gain constant
*/
unsigned char KP;

/**
@brief Derivitive gain constant
*/
unsigned int KD;

/**
@brief This determines how close to the desired location is 'close enough'
*/
unsigned char DEADBAND;


/**
@brief This variable is changed depending on the voltage read at a potentiometer and tells the program to adjust KP, KD, and DEADBAND parameters.
*/
unsigned char parameters;

/**
@brief Stores the current position of the motor shaft.
*/
unsigned char position;

/**
@brief Stores the target position of the motor shaft (set by user.)
*/
unsigned char destination;

/**
@brief Stores the error between the current position and the destination.
*/
int error;

/**
@brief Stores the motor speed setting.
*/
unsigned char speed;

int previousError = 0;
int deltaError;

/**
 * @brief Changes pins A2 and A3 to outputs to control the direction
 * of the motor rotation
 * 
 * @param dir Direction of motor motion
 */
void setDir (unsigned char dir)
{
	if (dir == LEFT)
	{
		motorB_Reverse();
	}
	else if (dir == RIGHT)
	{
		motorB_Forward();
	}
	else
	{
		motorB_Stop(); /*enable both directions causes a stop*/
	}
}

/**
 * @brief Checks the ADC to determine the current position of the motor.
 * @details Checks the input from the binary switch to determine the requested destination
 */
void calculateError(void)
{	
    position = ReadADC(FEEDBACK_ADC);
    destination = ReadADC(DESTINATION_ADC);
	
	//position = readAdc(0); // get current postion from ADC0 (PA0)
	//destination = readAdc(7); //get destination from ADC7 (PB4). 
	if (destination > 255) //if for some reason the destination is greater than 255
	{
		destination = 255; //set it to 255 max.
	}
	error = position - destination;
	if (error < 0) //if error is less than zero
	{
		error = -error;	//take absolute value of error
	}
	deltaError = error - previousError;	
	previousError = error;
}


/**
 * @brief Checks the ADC to determine the current position of the motor.
 * @details Checks the input from the binary switch to determine the requested destination
 */
void updateMotors(void)
{
	if (error < DEADBAND)	//if the error is less than the pre-defined DEADBAND turn off the motor.
	{
		setDir(STOP);
	}
	else if (position > destination) //if position is greater than destination, set motors RIGHT
	{
		setDir(RIGHT);
	}
	else //otherwise set motors LEFT
	{
		setDir(LEFT);
	}
	
	speed = (KP * error) - (KD * deltaError);
	
	if (speed > 255)
	{
		PWMB = 255; //max speed
	}
	if (speed < 70)  //minimum speed that will spin the motor
	{
		PWMB = 70;
	}	
	else
	{
		PWMB = speed; //This sets the speed of the motor. The greater the error, the faster the motor will run
	}
}

/**
 * @brief Sets up data direction registers, ADC and Timers
 */
void setup (void)
{
	DDRA = 0b10111110;	/* PA0-6 are inputs from the position and destination potentiometer.  PA2, PA3 are direction outputs */
	DDRB = 0b01101000;	/* PB3 is PWM output to motor enable*/
	
	PORTA = 0b00000000;	/* initialize port a, enable pull-up resisters on the inputs 0-3 */
	PORTB = 0b00000000; /* initialize port b*/

	//Select PB4 to measure, use Clock/4 for the prescaler, Don't use free running mode, use left adjusted ADCH
	SetupADC(ADC_PRESCALER_2, FALSE);
	ADCEnable();
	
	setupPWM(0b00000101, PWM_CHANNEL_B);
	
	motorB(&PORTA, PA1, &PORTA, PA2);
}

/**
@brief This function changes the control loop parameters based on the voltage of PA4. (This voltage is typically controlled by a potentiometer)
@details The values range from a high KP with low deadband, to a low KP with high deadband.
*/
void AdjustParameters(void)
{
	parameters = ReadADC(0b00000011);
	
	if(parameters <= 50)
	{
	KP = 10;
	KD = 0;
	DEADBAND = 11;
	}
	
	if((parameters > 50) && (parameters <= 100))
	{
	KP = 7;
	KD = 0;
	DEADBAND = 12;
	}
	
	if((parameters > 100) && (parameters <= 150))
	{
	KP = 5;
	KD = 0;
	DEADBAND = 13;
	}

	if((parameters > 150) && (parameters <= 200))
	{
	KP = 3;
	KD = 0;
	DEADBAND = 14;
	}

	if(parameters > 200)
	{
	KP = 1;
	KD = 0;
	DEADBAND = 15;
	}
}

/**
 * @brief Main function.  Program execution starts here.
 * 
 * @param void
 * @return int
 */
int main (void) 
{
	setup();	//initialize the ports, ADC registers, Timer Registers
	
	while(1)	//loop infinitely
	{
		//PWMB = 128;
		AdjustParameters();
		calculateError();	
		updateMotors();		
	}
}
