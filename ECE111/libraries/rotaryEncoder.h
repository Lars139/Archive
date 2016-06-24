#ifndef INCLUDED_ROTARY_ENCODER_H
#define INCLUDED_ROTARY_ENCODER_H

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

void initRotary (int lsb, int msb);
int getCurPos ();
int grayToDec (int msb, int lsb);

#define ROTARY_ENCODER_ISR ISR_IO_PINS_vect () { ISR_IO_PINS_vect(); }

#endif // INCLUDED_ROTARY_ENCODER_H
