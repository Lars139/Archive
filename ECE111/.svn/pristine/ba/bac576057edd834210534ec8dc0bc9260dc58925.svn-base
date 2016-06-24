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
 * This library uses for loops to create long, blocking delays using _delay_us and _delay_us.
 * This blocks all processor cycles during the delay.  Consider using hardware timers
 * for applications which need to use the processor during delays. 
 * 
 * @section HARDWARE
 * 
 * Target Device: All Atmel AVR devices
 * 
 */

#include <util/delay.h>

/**
 * Blocking delay.  Works for simple applications but blocks all processor cycles during delay.
 * Consider using hardware timers for more complex applications.
 * 
 * The time argument of _delay_ms() is limited to 255, so a for loop is used to repeat this 
 * delay function.
 *
 * @param ms number of milliseconds to delay
*/
void delay_ms (long ms) {
	int j;
	int interations = ms/250;
	for (j=0;j<ms;j++)
		_delay_ms(250);
	_delay_ms(ms%250);
}

/**
 * Blocking delay.  Works for simple applications but blocks all processor cycles during delay.
 * Consider using hardware timers for more complex applications.
 * 
 * The time argument of _delay_us() is limited to 255, so a for loop is used to repeat this 
 * delay function.
 *
 * @param us number of microseconds to delay
*/
void delay_us (long us) {
	int j;
	int interations = us/250;
	for (j=0;j<us;j++)
		_delay_us(250);
	_delay_us(us%250);
}
