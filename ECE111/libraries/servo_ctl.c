/** 
 * @file
 * @author Robert L. Phillips III
 * @author Scott Rosenbalm
 * @author Joey Tomlinson
 * @author Dan Albert
 * @date Last updated 8/24/12
 * @version 1.2
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
 * Includes functions for sending and receiving data to and from the computer
 * and moving the motor accordingly
 * 
 * @section HARDWARE
 * Target Device: ATTINY261
 */

/** 
 * The Tiny261 CPU speed
 */
#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>

#include "adc.h"
#include "motor_ctl.h"
#include "servo_ctl.h"

void SetMotorDirection(int dir)
{
	if (dir == CCW)
	{
		PWMB = SERVO_SPEED;
		motorB_Forward();
	}
	else if (dir == CW)
	{
		PWMB = SERVO_SPEED;
		motorB_Reverse();
	}
	else 
	{
		PWMB = 0;
		motorB_Stop();
	}
}


int ServoError(uint8_t destination)
{
	uint8_t position;
	
	ADCSetReference(ADC_REF_VCC);
	position = ReadADC(POT_ADC);
	
	if (destination > UPPER_BOUND)
	{
		destination = UPPER_BOUND;	// Set it to the upper bound
	}
	else if (destination < LOWER_BOUND)
	{
		destination = LOWER_BOUND;	// Set it to the lower bound
	}
		
	return position - destination;
}


void UpdateServo(uint8_t destination)
{
	int error = ServoError(destination);
	
	if (ABS(error) < DEADBAND)	// If the error is less than the deadband, just turn off the motor.
	{
		SetMotorDirection(STOP);
	}
	else if (error > 0)	// If the error is negativ, turn the servo clockwise.
	{
		SetMotorDirection(CW);
	}
	else	// Otherwise turn the servo counter-clockwise.
	{
		SetMotorDirection(CCW);
	}
}


void setServoPosition(uint8_t destination, uint16_t seekTime)
{	
	uint16_t i;
	for (i = 0; i < seekTime; i++)
	{
		UpdateServo(destination);
		_delay_ms(1);
	}
}