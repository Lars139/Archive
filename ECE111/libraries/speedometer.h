/** 
 * @file
 * @author Dan Albert
 * @date Created 7/15/2010
 * @date Last updated 7/15/10
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
 * Includes functions for using a row of four LEDs as a display.
 * 
 * @section HARDWARE
 * Target Device: ATTINY26L
 * Pin definitions are set up to use with the Tekbots tiny_mb.0 motor controller
 * Documentation for the tiny_mb.0 can be found here:
 * http://eecs.oregonstate.edu/education/products/tiny_mb.0/
 * 
 */
#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

/**
 * Fills the LEDs beginning with the led0.
 */
#define SPEEDO_DIR_LTR	0x00

/**
 * Fills the LEDs beginning with the led3.
 */ 
#define SPEEDO_DIR_RTL	0x01

/**
 * @brief	Stores register addresses for later by the display.
 * 
 * @param led0Port	The port that the first LED is connected to.
 * @param led0Pin	The pin that the first LED is connected to.
 * @param led1Port	The port that the second LED is connected to.
 * @param led1Pin	The pin that the second LED is connected to.
 * @param led2Port	The port that the third LED is connected to.
 * @param led2Pin	The pin that the third LED is connected to.
 * @param led3Port	The port that the last LED is connected to.
 * @param led3Pin	The pin that the last LED is connected to.
 */
void speedometer(unsigned char* led0Port, unsigned char led0Pin,
	unsigned char* led1Port, unsigned char led1Pin,
	unsigned char* led2Port, unsigned char led2Pin,
	unsigned char* led3Port, unsigned char led3Pin);

/**
 * @brief	Updates the LEDs defined by speedometer() with a new
 *			value. The direction in which the LEDs light up is
 *			defined by <i>direction</i>.
 * 
 * @param value		The value to display.
 * @param direction	Determines which direction to fill the LEDs. @see SPEEDO_DIR_LTR
 *					@see SPEEDO_DIR_RTL
 */
void updateSpeedometer(unsigned char value, unsigned char direction);

#endif // SPEEDOMETER_H