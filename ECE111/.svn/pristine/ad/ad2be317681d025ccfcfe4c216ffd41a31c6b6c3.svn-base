/** 
 * @file
 * @author Joey Tomlinson
 * @author Dan Albert
 * @date Last updated 8/24/12
 * @version 1.1
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
 * Includes functions for interfacing to the tekbots motor controller board
 * and for generating PWM signals for controlling motor speed.
 * 
 * @section HARDWARE
 * Target Device: ATTINY261 
 */
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "motor_ctl.h"
#include "util.h"

#define MOTOR_ENABLE(port, enablePin) port |= (1 << enablePin)
#define MOTOR_DISABLE(port, enablePin) port &= ~(1 << enablePin)

#define MOTOR_FORWARD(forPort, forPin, revPort, revPin) forPort |= (1<<forPin); revPort &= ~(1<<revPin);	// Set forwardPin = 1; Set reversePin = 0
#define MOTOR_REVERSE(forPort, forPin, revPort, revPin) forPort &= ~(1<<forPin); revPort |= (1<<revPin);	// Set forwardPin = 0; Set reversePin = 1
#define MOTOR_STOP(forPort, forPin, revPort, revPin) forPort &= ~(1<<forPin); revPort &= ~(1<<revPin);		// Set forwardPin = 0; Set reversePin = 0

unsigned char* motorA_forwardPort;
unsigned char* motorA_reversePort;
unsigned char motorA_forwardPin;
unsigned char motorA_reversePin;

unsigned char* motorB_forwardPort;
unsigned char* motorB_reversePort;
unsigned char motorB_forwardPin;
unsigned char motorB_reversePin;

void setupPWM(unsigned char frequencyDivider, unsigned char channel) 
{
	OCR1C = 0xff;
	
	// We need to set the TIMER1 clock devider by setting bits 0-3 of TCCR1B to bits 0-3 of freqDevide
	maskedCopy(frequencyDivider, &TCCR1B, 0b00001111);
	
	TCNT1 = 0x00; // Initialize TIMER1 to 0
	
	// Channel specific stuff
	if (channel & PWM_CHANNEL_A)
	{
		TCCR1A = 0b10000010;	// Set PWM1A, and COM1A1 for PWM on PB1
		PWMA = 0; // Initialize duty cycle to 0
	}
	
	if (channel & PWM_CHANNEL_B)
	{
		TCCR1C = 0b00001001;	// Set PWM1D, and COM1D1 for PWM on PB5
		PWMB = 0; // Initialize duty cycle to 0
	}
}

void motorA(unsigned char* forwardPort, unsigned char forwardPin, unsigned char* reversePort, unsigned char reversePin)
{
	motorA_forwardPort = forwardPort;
	motorA_reversePort = reversePort;
	motorA_forwardPin = forwardPin;
	motorA_reversePin = reversePin;
}

void motorB(unsigned char* forwardPort, unsigned char forwardPin, unsigned char* reversePort, unsigned char reversePin)
{
	motorB_forwardPort = forwardPort;
	motorB_reversePort = reversePort;
	motorB_forwardPin = forwardPin;
	motorB_reversePin = reversePin;
}

void setDutyCycleA(unsigned char value) 
{
	PWMA = value;
}

void setDutyCycleB(unsigned char value) 
{
	PWMB = value;
}

void motorA_Forward(void)
{
	MOTOR_FORWARD(*motorA_forwardPort, motorA_forwardPin, *motorA_reversePort, motorA_reversePin);
}

void motorA_Reverse(void)
{
	MOTOR_REVERSE(*motorA_forwardPort, motorA_forwardPin, *motorA_reversePort, motorA_reversePin);
}

void motorA_Stop(void)
{
	MOTOR_STOP(*motorA_forwardPort, motorA_forwardPin, *motorA_reversePort, motorA_reversePin);
}

void motorB_Forward(void)
{
	MOTOR_FORWARD(*motorB_forwardPort, motorB_forwardPin, *motorB_reversePort, motorB_reversePin);
}

void motorB_Reverse(void)
{
	MOTOR_REVERSE(*motorB_forwardPort, motorB_forwardPin, *motorB_reversePort, motorB_reversePin);
}

void motorB_Stop(void)
{
	MOTOR_STOP(*motorB_forwardPort, motorB_forwardPin, *motorB_reversePort, motorB_reversePin);
}