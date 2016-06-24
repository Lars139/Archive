/**
 * @file
 * @author Scott Rosenbalm
 * @author Joey Tomlinson
 * @author David Overgaard
 * @version 2.0
 * @brief This is file is the the main for section 3, the pencil resistor lab.
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
 * @section HARDWARE
 * 
 * Target Device: ATTINY26L
 * 
 * Small speaker connected between PB6 and GND
 * Graphite strip voltage devider connected to PB4
 * Active low switch input on PB5 used to play the Mario theme song
 * 
 * @section DETAILS
  * This program reads the resistance across a strip of graphite, and
 * plays a tone on a speaker which depends on the resistance of the
 * graphite.  By moving a probe along the graphite strip, the resistance
 * changes, which in turn changes the tone.
 *
 * <a href="http://www.mariopiano.com/mario-sheet-music-overworld-main-theme.html">Mario main theme sheet music</a>
 */

// #include <file_name> inserts the contents of <file_name>.  It is useful for including header files which are used to describe external files
// Includes local header file used for music generation.  When "" are used, compiler looks in the local directory.
// See headersAndLinking.txt for more information about using multiple source files in a project
#define F_CPU 1000000UL

#include "sound.h" //A local header file that defines note frequencies and function prototypes for speaker functionality
#include "adc.h" //A local header file that defines constants and function prototypes to simplify the use of the ADC (analog digital converter).

// The following 3 lines include some useful libraries which are supplied with avr-libc
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

// The #define NAME <value> syntax instructs the compiler to replace all occurances of NAME in this file with <value>
/**
@brief The system clock frequency is defined as specified in the tiny26 datasheet.
@details The default clock frequency for the tiny26 is 1MHz.  This define is used by the _ms_delay() function in delay.h to introduce accurate delays. 
*/
#define MICRO_DELAY 5

/**
@brief This is the number of clock cycles required to equal one whole note/rest for a given tempo
@details The number is defined by calculating the number of cycles per second of TIMER/COUNTER0 and then multiplying by the number of seconds per beat. <br> </br>
(60/(tempo/4))*(1000000/1024)
*/
#define WHOLE (11719/tempo) 

/**
@brief This is the number of clock cycles required to equal one half note/rest for a given tempo
@details The number is defined by calculating the number of cycles per second of TIMER/COUNTER0 and then multiplying by the number of seconds per beat. <br> </br>
(60/(tempo/2))*(1000000/1024)
*/
#define HALF (23438/tempo) 

/**
@brief This is the number of clock cycles required to equal one quarter note/rest for a given tempo
@details The number is defined by calculating the number of cycles per second of TIMER/COUNTER0 and then multiplying by the number of seconds per beat. <br> </br>
(60/tempo)*(1000000/1024)
*/
#define QUARTER (11719/tempo)

/**
@brief This is the number of clock cycles required to equal one eighth note/rest for a given tempo
@details The number is defined by calculating the number of cycles per second of TIMER/COUNTER0 and then multiplying by the number of seconds per beat. <br> </br>
(60/(tempo*2))*(1000000/1024)
*/
#define EIGHTH (5859/tempo)

/* 	
	This macro uses an assigment by XOR opperator
	PORTA ^= 0b11111111; is equivilent to PORTA = PORTA ^ 0b11111111;
	The ^ character is a bitwise XOR.  In this case it toggles all pins on PORTA
	This #define toggles the speaker output pin 
*/
#define TOGGLE_SPKR() PORTB ^= 0b01000000

/*
	Function Prototypes
	These describe the parameters and return values of functions which are defined below main.  Because the compiler processes functions in order
	from the top of the page down, prototypes is sometimes necessary to allow functions to be used before the compiler knows their full definition.
	It is recommended to always use prototypes to avoid compilation issues.
*/
void setupIO (void);
unsigned char chooseFrequency (unsigned char);
void playSequence (unsigned char *, unsigned char);
void timingDelay(unsigned char iterate);

/**
@brief This variable sets the tempo for the Mario theme song in beats per minute.
*/
unsigned int tempo;

/**
@brief This variable is used when calculating the timing for the Mario theme song
*/
volatile unsigned int timerCount = 0;

/**
@brief This function controls what happens eacht time the timer/counter0 overflow vector is called.
@details This vector is used to control the timing of the notes and rests used in the Mario song demo.
*/
ISR(TIMER0_OVF_vect)
{
	TCNT0L = 236;
	timerCount = timerCount + 1;	
}

/**
@brief This function controls what happens each time timer/counter1 has a compare match with OCR1A vector is called.
@details How often this vector is called is set by OCR1A, which is defined each time a new note is selected
*/
ISR(SIG_OUTPUT_COMPARE1A)
{
	TOGGLE_SPKR();
	TCNT1 = 0;
}

/**
@brief  Sets the data direction registers for the IO ports with an inital value.
@details This function runs once at the start of the program.
 */
void setupIO (void)
{
	// First the data direction of the IO ports are set
	DDRA = 0b11111100;	// Sets pins 0, 1 to input and pins 2-7 to output
	DDRB = 0b01001000;	// Sets pins 0-2, 4, 5, 7 to input and pins 3, 6 to output
	
	// Then the pins are set to an inital value.  Pins not being used are also pulled high to enable the internal pull-up resistor.
	PORTA = 0b11111111;
	PORTB = 0b11111111;
}

/**
 @brief Chooses a note in the c major scale based on ADC readings from the graphite strip on our piano.
 @param unsigned char: A value between 0 and 255
 @return unsigned char: The number of clock cycles before the speaker toggles to generate the corresponding wave freqeuncy
 @details A small input value will output a higher note (smaller timer ticks, creating a higher frequency) when compared to a larger input value.
 */
unsigned char chooseFrequency (unsigned char adcValue) {
	if ((adcValue >= 0) && (adcValue < 50)) // If adc reading is between 5 and 18, choose high c
	{
		return FREQ_C_H;
	}
	else if ((adcValue >= 50) && (adcValue < 95)) // etc ...
	{
		return FREQ_B;
	}
	else if ((adcValue >= 95) && (adcValue < 125))
	{
		return FREQ_A;	
	}
	else if ((adcValue >= 125) && (adcValue < 155))
	{
		return FREQ_G;
	}
	else if ((adcValue >= 155) && (adcValue < 180))
	{
		return FREQ_F;
	}
	else if ((adcValue >= 180) && (adcValue < 200))
	{
		return FREQ_E;
	}
	else if ((adcValue >= 200) && (adcValue < 222))
	{
		return FREQ_D;
	}
	else
	{
		return FREQ_C;
	}
}

/**
@brief For the set tempo, this function plays a specified note for the duration of a quarter beat.
@param unsigned char : Typically this parameter is one of the pre-defined notes found in sound.h
*/
void QuarterNote(unsigned char note)
{
	timerCount = 0;
	setFrequency(note);
	while(timerCount < QUARTER)
	{
	speakerOn();
	}
	disableSpeaker();
}

/**
@brief For the set tempo, this function turns the speaker off for the duration of a quarter beat.
@param unsigned char : Typically this parameter is one of the pre-defined notes found in sound.h
*/
void QuarterRest(void)
{
timerCount = 0;
	while(timerCount < QUARTER)
	{
	disableSpeaker();
	}
}

/**
@brief For the set tempo, this function plays a specified note for the duration of an eighth beat.
@param unsigned char : Typically this parameter is one of the pre-defined notes found in sound.h
*/
void EighthNote(unsigned char note)
{
	timerCount = 0;
	setFrequency(note);
	while(timerCount < EIGHTH)
	{
		speakerOn();
	}
	disableSpeaker();
}

/**
@brief For the set tempo, this function turns the speaker off for the duration of a eighth beat.
@param unsigned char : Typically this parameter is one of the pre-defined notes found in sound.h
*/
void EighthRest(void)
{
timerCount = 0;
	while(timerCount < EIGHTH)
	{
	disableSpeaker();
	}
}

/**
@brief This controls which functions are executed and in what order.
*/
int main (void) 
{
	// First the setup functions which are defined above main() are called
	setupIO(); // configures IO
	setupSpeaker(&PORTB, PB6);
	
	ADMUX = 0b00100111; //Use VCC as ADC reference, Left-adjust result, select PB4 for ADC
	ADCSRA = 0b11100010; //Enable ADC, start ADC, enable "Free-Running" mode, Divide clock by 4
	
	sei(); // Function defined in interrupt.h which enables interrupts globally.  Before calling this, all interrupts are disabled.
	
	while(1)	// Main program loop. In c, 1=true. Passing 1 as the condition causes it to loop infinitely.
	{
		// Checking to see if the "Mario switch" has been selected
		if (!(PINB & 0b00100000))
		{
			tempo = 200;
			
			//The following is an approximate replica of the Mario theme song.  The song is broken down into measures which are defined in sound.c  Comments including which line is currently being played are also included which correspond to the sheet music .pdf included in the lab documentation
			//Intro
			//Line 1
			MeasureOne();
			MeasureTwo();
			
			//Variables used for loop controls
			unsigned char j;
			unsigned char loopCount = 1;
			
			//This loop will play the mario main theme, and then replay song at a faster tempo after the "running out of time" line has execued.  It also checks to ensure that the "Mario switch" is still selected before it repeats
			while(!(PINB & 0b00100000) && (loopCount < 3))
			{
				//Line 2 / Line 3 is the same as line 2, so this sequence repeats once.
				for(j = 0; j <= 1; j++)
				{
					MeasureThree();					
					MeasureFour();
					MeasureFive();									
					MeasureSix();
				}
				
				//Lines 4-5 repeat for lines 6-7
				for(j = 0; j <= 1; j++)
				{
					//Line 4
					MeasureSeven();
					MeasureEight();
					MeasureNine();
					MeasureTen();
					
					//Line 5
					MeasureEleven();
					MeasureTwelve();
					MeasureThirteen();
					MeasureFourteen();
				}
				
				//Line 8
				MeasureFifteen();
				MeasureSixteen();
				MeasureSeventeen();
				MeasureEighteen();

				//Line 9
				MeasureFifteen();
				MeasureSixteen();
				MeasureNineteen();
				MeasureTwenty();
				
				if(!(PINB & 0b00100000) && (loopCount == 1))
				{
					tempo = 300;
					MeasureTwentyOne(); //Running out of time line		
					loopCount++;
				}
			}
		}
		else // If the button is not pressed, go into normal piano mode
		{
			// The following code measures the voltage from the probe using the ADC (which is automatically stored in ADCH after each reading) and then tells the speaker to generate the corresponding frequency between middle and high c.  If the probe is not measuring anything or a very low voltage, the speaker will turn off.
			if (ADCH < 250) 
			{
				//setFrequency is defined in sound.h; chooseFrequency is defined below
				setFrequency(chooseFrequency(ADCH));
				speakerOn();
			} 
			else 
			{
				disableSpeaker();
			}
		}
	}
}