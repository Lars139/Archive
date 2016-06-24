/** 
 * @file
 * @author Scott Rosenbalm
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
 * This program reads the resistance across a strip of graphite, and
 * plays a tone on a speaker which depends on the resistance of the
 * graphite.  By moving a probe along the graphite strip, the resistance
 * changes, which in turn changes the tone.
 * 
 * Target Device: ATTINY26L
 * 
 * Hardware:
 * Small speaker connected between any pin on PORTA and GND
 * Graphite strip voltage devider connected to PB4
 * Switch on PB1 plays zelda TODO: active high/low?
 * 
 */


include "Lab_3.h"

/**
 * SIGNAL is a special function which runs every time the specified
 * hardware interrupt is triggered. TODO - specifics, link to avr-gcc doc
 * 
 * @param SIG_OUTPUT_COMPARE1A specifies that we are handling the
 * COMPARE1A interupt
 * 
 */
SIGNAL(SIG_OUTPUT_COMPARE1A)
{
	PORTA ^= 0b11111111;
	TCNT1 = 0;
}

int main (void) 
{
	setup(); //initialize all ports, registers, etc.
	
	//this is the song data for playing zelda
	const char zelda[49] = {Asp, F, F, F, Asp, Asp, Ch, Dh, Dhsp, Fh, Fh, Fh, Fh, Fhsp, Ghsp, Ahsp, Ahsp, Ahsp, Ahsp, Ahsp, Ghsp, Fhsp, Ghsp, Fhsp, Ghsp, Ghsp, Fhsp, Fh, Fh, Fh, Dhsp, Dhsp, Fh, Fhsp, Fhsp, Fh, Dhsp, Chsp, Chsp, Dhsp, Fh, Fh, Dhsp, Chsp, Ch, Ch, Dh, Eh, Eh};
	
	int i = 0;
	while(TRUE)		// loops program infinitely 
	{
		if (bit_is_clear(PINB, 1)) //if special button is pushed, enter "zelda mode"
		{
			playSequence (zelda); // zelda (by itself without [index] is a pointer to the first memory address of the sequence array
		}
		else //normal mode
		{
			if (ADCH < 5) 
				cli(); // turn off the interrupts if the piano is not really being pushed
			else 
				sei(); // turn on interrupts if piano is being pushed
			
			//This section splits up the range of the piano into eight notes, a C-major scale
			
			if ((ADCH >= 5) && (ADCH <= 16))
				OCR1A = Ch;
			else if ((ADCH >= 18) && (ADCH <= 38))
				OCR1A = B;
			else if ((ADCH >= 40) && (ADCH <= 60))
				OCR1A = A;
			else if ((ADCH >= 62) && (ADCH <= 120))
				OCR1A = G;
			else if ((ADCH >= 122) && (ADCH <= 165))
				OCR1A = F;
			else if ((ADCH >= 167) && (ADCH <= 191))
				OCR1A = E;
			else if ((ADCH >= 193) && (ADCH <= 222))
				OCR1A = D;			
			else if (ADCH >222)
				OCR1A = C;
		}
	}
}

/**
 * Sets up Data Direction Registers, ADC and timers
 * 
 */
void setup (void)
{
	DDRA = 0b11111111;	// all port a are outputs 
	DDRB = 0b01101101;	// PORTB has inputs for resistor devider and switch (defined above)
	
	PORTA = 0b00000000;	// initialize port a 
	PORTB = 0b00000010; // initialize port b
	
	//Configure Analog to Digital Converter (ADC)
	ADMUX = 0b00100111; // Use VCC as ADC reference, Left-adjust result, select PB4 for ADC
	ADCSR = 0b11100010; // Enable ADC, start ADC, enable "Free-Running" mode, Divide clock by 4
	
	//Configure timers
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000101; // timer clock set to clk/16 (clk refers to system clock)
	TCNT1 = 0x00; //initialize timer 1 to 0
	OCR1A = 80; // sets initial compare value so interupt fires when TCNT1=80
	TIMSK = 0b01000000; // enable OCR1A interrupt 
	sei(); // enable interrupts globally
}

/**
 * Plays a sequence of notes when the user taps the piano.
 * 
 * @param sequence pointer to the start of a char array which represents
 * the sequence of a song.
 * @param length length of the sequence
 * 
 */
void playSequence (char * sequence, length) {
	
	while (bit_is_clear(PINB, 1)) //while the button is pushed, remain in "zelda mode"
	{
		cli(); // disable interrupts
		while(ADCH < 10) // while the piano is not touched, dont play anything
			_delay_ms(20);
		sei(); //turn interrupts back on once the piano is pushed again
		OCR1A = sequence[i]; //cycle to next note in the song
		while(ADCH >= 10) // while piano is pushed, keep playing the current note
			_delay_ms(20);
		i++; //move index to next note
		i = i % length; //keep index value in the bounds of our song array
	}
	i = 0; //reset index after "zelda mode" button is released
}
