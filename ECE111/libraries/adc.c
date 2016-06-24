/** 
 * @file
 * @author Matthew Shuman
 * @author Joey Tomlinson
 * @author Dan Albert
 * @date Created 8/5/09
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
 * Includes functions for setting up and reading the hardware ADC on the attiny26.
 * 
 * @section HARDWARE
 * Target Device: ATTINY261
 * 
 */
 
#include <avr/io.h>

#include "adc.h"
#include "pins.h"

void ADCSetChannel(uint8_t channel)
{
	CLEARPINS(ADMUX, ADC_MUX_MASK);
	SETPINS(ADMUX, (channel & ADC_MUX_MASK));
}

void ADCSetAdjust(BOOL leftAdjust)
{
	if (leftAdjust == 1)
	{
		SETPIN(ADMUX, ADLAR);
	}
	else
	{
		CLEARPIN(ADMUX, ADLAR);	// See pins.h
	}
}

void ADCSetPrescaler(uint8_t prescale)
{
	CLEARPINS(ADCSRA, ADC_PRESCALER_MASK);
	SETPINS(ADCSRA, (prescale & ADC_PRESCALER_MASK));
}

void ADCSetFreeRunning(BOOL freeRun)
{
	if (freeRun)
	{
		SETPIN(ADCSRA, ADATE);
		ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0);
	}
	else
	{
		CLEARPIN(ADCSRA, ADATE);
	}
}

void ADCSetReference(uint8_t reference)
{
	CLEARPINS(ADMUX, ADC_REF_MASK);
	SETPINS(ADMUX, (reference & ADC_REF_MASK));
	
	// First read after changing reference is probably garbage
	ADCStart();
	// Wait for the AD conversion to complete
	while (!ADCDone());
	
	ADCFinish();
}

void ADCEnableInterrupt(void)
{
	SETPIN(ADCSRA, ADIE);
}

void ADCDisableInterrupt(void)
{
	CLEARPIN(ADCSRA, ADIE);
}

void ADCEnable(void)
{
	SETPIN(ADCSRA, ADEN);
}

void ADCDisable(void)
{
	CLEARPIN(ADCSRA, ADEN);
}

void ADCStart(void)
{
	SETPIN(ADCSRA, ADSC);
}

void ADCFinish(void)
{
	SETPIN(ADCSRA, ADIF);
}

BOOL ADCDone(void)
{
	return BOOL(GETPIN(ADCSRA, ADIF));
}

void SetupADC(uint8_t prescale, BOOL freeRun)
{
	ADCSetPrescaler(prescale);	// Set prescaler bits
	ADCSetFreeRunning(freeRun);		// Set free run bit
}

uint8_t ReadADC(uint8_t channel)
{	
	ADCSetChannel(channel);	// Set ADC channel select bits
	ADCSetAdjust(ADC_LEFTADJUST);	// Set left/right adjust bit
	
	ADCStart();
	// Wait for the AD conversion to complete
	while (!ADCDone());
	
	ADCFinish();
	
	return ADCH;
}

uint8_t ReadADCAveraged(uint8_t channel, uint8_t samples)
{
	uint8_t i;
	uint16_t accumulator = 0;
	
	for(i = 0; i < samples; i++)
	{
		accumulator += ReadADC(channel);
	}
	
	return accumulator / samples;
}

uint16_t ReadPreciseADC(uint8_t channel)
{	
	ADCSetChannel(channel);	// Set ADC channel select bits
	ADCSetAdjust(ADC_RIGHTADJUST);	// Set left/right adjust bit
	
	ADCStart();
	// Wait for the AD conversion to complete
	while (!ADCDone())
	{
	}
	ADCFinish();
	
	return ADCW;
}

uint16_t ReadPreciseADCAveraged(uint8_t channel, uint8_t samples)
{
	uint8_t i;
	uint16_t total = 0;
	uint16_t value;
	
	for (i = 0; i < samples; i++)
	{
		total += ReadPreciseADC(channel);
	}
	
	value = total / samples;
	
	return value;
}
