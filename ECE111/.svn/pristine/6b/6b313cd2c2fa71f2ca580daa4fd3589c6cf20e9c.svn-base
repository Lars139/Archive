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
 * @section TARGET_DEVICE
 * ATTINY26L
 * 
 * Hardware Description:
 * 
 */
#include "speedometer.h"

unsigned char* led0_Port;
unsigned char* led1_Port;
unsigned char* led2_Port;
unsigned char* led3_Port;
unsigned char led0_Pin;
unsigned char led1_Pin;
unsigned char led2_Pin;
unsigned char led3_Pin;

void speedometer(unsigned char* led0Port, unsigned char led0Pin,
	unsigned char* led1Port, unsigned char led1Pin,
	unsigned char* led2Port, unsigned char led2Pin,
	unsigned char* led3Port, unsigned char led3Pin)
{
	led0_Port = led0Port;
	led1_Port = led1Port;
	led2_Port = led2Port;
	led3_Port = led3Port;
	led0_Pin = led0Pin;
	led1_Pin = led1Pin;
	led2_Pin = led2Pin;
	led3_Pin = led3Pin;
}

void updateSpeedometer(unsigned char value, unsigned char direction)
{
	if (direction == SPEEDO_DIR_LTR)
	{
		if (value >= 204)
		{
			*led0_Port |= (1 << led0_Pin);
		}
		else
		{
			*led0_Port &= ~(1 << led0_Pin);
		}
		
		if (value >= 153)
		{
			*led1_Port |= (1 << led1_Pin);
		}
		else
		{
			*led1_Port &= ~(1 << led1_Pin);
		}
		
		if (value >= 102)
		{
			*led2_Port |= (1 << led2_Pin);
		}
		else
		{
			*led2_Port &= ~(1 << led2_Pin);
		}
		
		if (value >= 51)
		{
			*led3_Port |= (1 << led3_Pin);
		}
		else
		{
			*led3_Port &= ~(1 << led3_Pin);
		}
	}
	else
	{
		if (value >= 204)
		{
			*led3_Port |= (1 << led3_Pin);
		}
		else
		{
			*led3_Port &= ~(1 << led3_Pin);
		}
		
		if (value >= 153)
		{
			*led2_Port |= (1 << led2_Pin);
		}
		else
		{
			*led2_Port &= ~(1 << led2_Pin);
		}
		
		if (value >= 102)
		{
			*led1_Port |= (1 << led1_Pin);
		}
		else
		{
			*led1_Port &= ~(1 << led1_Pin);
		}
		
		if (value >= 51)
		{
			*led0_Port |= (1 << led0_Pin);
		}
		else
		{
			*led0_Port &= ~(1 << led0_Pin);
		}
	}
}
