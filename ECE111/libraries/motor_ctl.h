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
#ifndef INCLUDED_MOTOR_CTL_H
#define INCLUDED_MOTOR_CTL_H

/**
* Identifier flag for PWM channel A.
*/
#define PWM_CHANNEL_A 0x01

/**
 * Identifier flag for PWM channel B.
 */ 
#define PWM_CHANNEL_B 0x02

/**
 * Alias for the output compare register used by PWM channel A.
 */
#define PWMA	OCR1A

/**
 * Alias for the output compare register used by PWM channel B.
 */ 
#define PWMB	OCR1D

/**
 * @brief	Sets up Timer/Counter1 for PWM.
 *
 * @param frequencyDivider Prescaling factor for the timer clock. Refer to table 34 of the tiny26 data sheet for more information.
 * @param channel	Channel selector for PWM. To enable more than one channel, PWM channel flags may be combined using a bitwise OR. 
 *
 * @see PWM_CHANNEL_A 
 * @see PWM_CHANNEL_B
 *
 * Enables Timer/Counter1 compare A and overflow interrupts.
 */
void setupPWM(unsigned char frequencyDivider, unsigned char channel);

/**
 * @brief	Sets the duty cycle for PWM channel A.
 *
 * @param value The length of the duty cycle. 0 is off, 255 is full time.
 * An alias for PWMA = value
 */
void setDutyCycleA(unsigned char value);

/**
 * @brief	Sets the duty cycle for PWM channel B.
 *
 * @param value The length of the duty cycle. 0 is off, 255 is full time.
 * An alias for PWMB = value
 */
void setDutyCycleB(unsigned char value);

/**
 * @brief	Sets up a motor for PWM channel A.
 * 
 * @param forwardPort	Pointer to the register of the port motor A's forward pin is connected to.
 * @param forwardPin	Output pin that motor A's forward pin is connected to.
 * @param reversePort	Pointer to the register of the port motor A's reverse pin is connected to.
 * @param reversePin	Output pin that motor A's reverse pin is connected to.
 */
void motorA(unsigned char* forwardPort, unsigned char forwardPin, unsigned char* reversePort, unsigned char reversePin);

/**
 * @brief	Sets up a motor for PWM channel B.
 * 
 * @param forwardPort	Pointer to the register of the port motor B's forward pin is connected to.
 * @param forwardPin	Output pin that motor B's forward pin is connected to.
 * @param reversePort	Pointer to the register of the port motor B's reverse pin is connected to.
 * @param reversePin	Output pin that motor B's reverse pin is connected to.
 */
void motorB(unsigned char* forwardPort, unsigned char forwardPin, unsigned char* reversePort, unsigned char reversePin);

/**
 * @brief	Set's motor A's direction to forward.
 * 
 * Sets motor A's forward pin high, and its reverse pin low.
 */
void motorA_Forward(void);

/**
 * @brief	Set's motor A's direction to reverse.
 * 
 * Sets motor A's forward pin low, and its reverse pin high.
 */
void motorA_Reverse(void);

/**
 * @brief	Set's motor A's direction to none.
 * 
 * Sets motor A's forward and reverse pins low.
 */
void motorA_Stop(void);

/**
 * @brief	Set's motor B's direction to forward.
 * 
 * Sets motor B's forward pin high, and its reverse pin low.
 */
void motorB_Forward(void);

/**
 * @brief	Set's motor B's direction to reverse.
 * 
 * Sets motor B's forward pin low, and its reverse pin high.
 */
void motorB_Reverse(void);

/**
 * @brief	Set's motor B's direction to none.
 * 
 * Sets motor B's forward and reverse pins low.
 */
void motorB_Stop(void);

#endif // INCLUDED_MOTOR_CTL_H
