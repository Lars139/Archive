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
 * For Example: #define F_CPU 1000000UL should be used if the system clock is set to 1000000UL
 * 
 * @section HARDWARE
 * 
 * Target Device: All Atmel AVR devices
 * 
 */

#include <util/delay.h>

void delay(int ms);
void delay_us (long us);
