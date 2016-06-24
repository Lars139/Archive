/**
 * @file wunder.c
 * @author Dan Albert, Marhshal Horn (Wunderboard Loader) 
 * @author Rattanai Sawaspanich (SPI setup, and Digital Potentiometer ctrl)
 * @date Created 12/15/2010
 * @date Last updated 1/26/2015
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
 * This program will test the various components of the Wunderboard when used
 * with the corresponding host test script.
 * 
 */

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "adc.h"
#include "diskio.h"
#include "types.h"
#include "usart.h"
#include "leds.h"

// 9600 baud
#define BAUD_RATE 51

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

#define SS PB0
#define SCK PB1
#define MOSI PB2

void initialize( void )
{
	CPU_PRESCALE(0);

	USART_init(BAUD_RATE);
	USART_transmit('\f');	// Send form feed to clear the terminal.
	USART_send_string("WunderBoard initializing...\r\n");

	USART_send_string("\tSetting ADC prescaler and disabling free running mode...\r\n");
	setup_ADC(ADC_PRESCALER_32, FALSE);

	USART_send_string("\tEnabling ADC...\r\n");
	ADC_enable();

	USART_send_string("\tSetting ADC reference to Vcc...\r\n");
	ADC_set_reference(ADC_REF_VCC);

	// Configure IO //
	USART_send_string("\tConfiguring IO...\r\n");
	//DDRx corresponds to PORTx/PINx, dependng on direction of data flow -- PORT for output, PIN for input
	DDRA = 0x00;	// Buttons and switches
	DDRB = 0xE7;	// Red enable, green enable and audio out
	DDRC = 0xff;	// Discrete LEDs
	DDRE = 0x47;	// LED Column
	DDRF = 0x00;	// Accelerometer

	// Disable pullups and set outputs low //
	PORTA = 0x00;
	PORTB = 0x01;
	PORTC = 0x81;
	PORTE = 0x00;
	PORTF = 0x00;

	//Set OC1A to toggle
	TCCR1A = 0b01000000;
	// Clk/64 and CTC mode
	TCCR1B = 0b00001011;

	OCR1A = 24;

	USART_send_string("\tSetting SPI\r\n");

	//Set the SPI bus appropriately to use the LED array
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	sei();
}

/************************************************************
 *******************		MAIN		*********************
 ***********************************************************/

unsigned char Get_Byte_USART()
{
	if(UCSR1A & (1<<RXC1))
		return (UDR1);
	else
		return (unsigned char) 0;
}


ISR(USART1_RX_vect)
{
	//Thy shall do nothing	
}

ISR(BADISR_vect){
	//DO NOTHING
}

unsigned char initialize_TIMER0()
{
	//clean up a bit
	TCCR0A &= ~0b11;
	TCCR0B &= ~0b111;

	/* Set the CTC mode */
	TCCR0A |= 0b00000010;//(1<<WGMO1);  

	/* Set the Clock Frequency */
	TCCR0B |= 0b00000101;//(101<<CS00);

	/* Set initial count value */
	OCR0A = 0;

	return 0;
}


// This function checks if TIMER0 has elapsed. 
unsigned char check_TIMER0()
{
	if(TIFR0 & (1<<OCF0A) != 0){
		TIFR0 = (1<<OCF0A);
		return 1;
	}else{
		return 0;
	}
}

////////////////////////////////// SPI //////////////////////////////////

/* Function: spi_init_master
 * Initialize Wuderboard as a Master in SPI
 * SPI Output: PortB
 * Pin0 -- Do nothing 
 * Pin1 -- SCK 
 * Pin2 -- MOSI (square)
 * Pin3 -- small detail MOSI 
 * Pin4 -- Do nothing (MOSI really really small)
 * Pin5 -- Wunderboard clk 
 * Pin6 -- Do nothing
 * Pin7 -- Do nothing
 */
void spi_init_master(){
	/*Look at these bits to set the SPI config
	 * SPDR -- SPI Data Register
	 */

	//Setting the PORTA to be the output (PIN1,2,3,5)
	//NOTE: Write an (int) 1 to a DDRx sets it on the output mode
	//	DDRB |= (3<<1)|(1<<5);
	DDRB |= (1<<PB1) | (1<<PB2) | (1<<5) | (1<<7);
	//Look at the datasheet.(P.174, AT90USB64/128)  
	/*Setting SPCR
	 * SPE -- SPI_en -- (1:Enable, 0:Nope)
	 * DORD -- Data order -- (1:LSB first, 0:MSB first)
	 * MSTR -- Master/Slave? -- (1:Master, 0:Slave)
	 * CPOL -- Clock polarity -- (1:Rising, 0:Falling comparing to clk)
	 * CPHA -- Clock phase -- (Sampling at 0:Leading 1:Trailing)
	 * SPR1/0 -- Clock scaling
	 */

	//Setting SPCR s.t. 
	//SPCR = Enable SPI | LSB leads| Master Mode| 
	//Rising edge sck| lead edge sampling | (Freq = clk/4)
	//NOTE: The actual Freq = clk/2 (b/c doubling the trans rate)
	SPCR = 1<<SPE | 0<<DORD | 1<<MSTR |
		0<<CPOL | 0<<CPHA | (0<<SPR1 | 0<<SPR0);

	//Enable the double the transmittion rate in SPSR (write 1 to it)
	SPSR = (1<<SPI2X);

	return ;
}

void spi_send_ss(int bit_num){
	//Toggle SPI PortC to flash the digital pot
	PORTC |= (1<<bit_num);
	PORTC &= ~(1<<bit_num);
	return; 
}

void spi_trans_master(char *data){

	while(!(SPSR & (1<<SPIF)));
	//Write a message to SPDR, ready to be sent
	SPDR = data[0];

	//Wait until the SPSR is empty, then send the data
	//Check SPIF bit in SPSR
	while(!(SPSR & (1<<SPIF)));

	SPDR = data[1];
	//	while(!(SPSR & (1<<SPIF)));
	spi_send_ss(7);

}

//////////////////////////////// SPI ENDS HERE /////////////////////////

///////////////////////////////  LED CONTROL ///////////////////////////
void init_portB_led(){
	DDRB = 0xE7;	// Red enable, green enable and audio out
	DDRC = 0x00;	//Disable SS
	PORTB = 0x01;   //Setting PORTB pin 1 to be an output
}


/////////////////////////////////  RED /////////////////////////////////
//Displaying '0'
void disp_g0(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,3);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '1'
void disp_g1(){
	init_portB_led();

	for(int i = 1; i<6;++i){
		led_green(i,4);
		led_off();
	}

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '2'
void disp_g2(){
	init_portB_led();

	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,3);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '3'
void disp_g3(){
	init_portB_led();

	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '4'
void disp_g4(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '5'
void disp_g5(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '6'
void disp_g6(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '7'
void disp_g7(){
	init_portB_led();

	for(int i = 3; i<6; ++i){
		led_green(1,i);
		led_off();
	}
	for(int i = 1; i<6; ++i){
		led_green(i,5);
		led_off();
	}
	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '8'
void disp_g8(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,3);
	led_off();
	led_green(5,4);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying '9'
void disp_g9(){
	init_portB_led();
	led_green(1,3);
	led_off();
	led_green(1,4);
	led_off();
	led_green(1,5);
	led_off();
	led_green(2,3);
	led_off();
	led_green(2,5);
	led_off();
	led_green(3,5);
	led_off();
	led_green(3,4);
	led_off();
	led_green(3,3);
	led_off();
	led_green(4,5);
	led_off();
	led_green(5,5);
	led_off();

	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}


//Displaying 'XP'
void disp_xP(){
	init_portB_led();
	led_red(2,1);
	led_off();
	led_red(2,2);
	led_off();
	led_red(2,5);
	led_off();
	led_red(2,6);
	led_off();
	led_red(3,1);
	led_off();
	led_red(3,2);
	led_off();
	led_red(3,5);
	led_off();
	led_red(3,6);
	led_off();
	for(int i = 2; i<6;++i){
		led_red(5,i);
		led_off();
	}
	led_red(6,1);
	led_off();
	led_red(6,6);
	led_off();
	led_blue(4,6);
	led_off();
	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//Displaying 'X'
void disp_x(){
	init_portB_led();
	for(int i = 0; i<8;++i){
		led_red(i,i);
		led_red(7-i,7-i);
		led_off();
	}


	//ReInite the PortC to SPI mode
	DDRC = 0xFF;
}

//////////////////////////////// The Main ///////////////////////////

int main(int argc, char **argv)
{
	initialize();
	spi_init_master();
	clear_array();
	//	INFO info = {0b0001, 0b0001, 0b11000010 };

	/*Defined variables: 
	 *  SS --> PB0
	 *  SCK --> PB1
	 *  MOSI --> PB2
	 */

	srand(17);
	char misc = 0b00010001;
	char r_val = 125;
	char arr[2] = { misc, r_val};
	int N =5;
	//R_spi change the resistor value to behave in log scale
	char r_spi[10] = {255,254,253,251,248,245,238,211,155,0};

	while(1){
		//Use buttons to adjust the resistor
		//Change PORTC to be active low 
		//(Idle = low;  done = high)

		//Starting PORTC Pin7 as a high (For active high)
		//	PORTC = 0x80; 

		//Second try, PORTC Pin7 start as a low (Active Low)
		PORTC = 0x00;


		//FIXME: Create an array of fix values dep on N to determine the increment/decrement each of the step for the log
		r_val = r_spi[9-N];
		arr[1] = r_val;
		/*
		   if(PINA & 0b00000010 ){
		   if(r_val <= 247)
		   r_val += 2;
		   else
		   r_val = 255;

		   PORTC |= (1<<0);
		   _delay_ms(5);
		   ++N;
		   }
		//ACTIVE LOW!! PRESSING UP mean goin down in POT
		else if(PINA & 0b00000100){
		if(r_val >= 8)
		r_val -= 2;
		else
		r_val = 0;

		PORTC |= (1<<1);
		_delay_ms(5);
		--N;
		}
		*/

		//ACTIVE LOW!! PRESSING UP mean goin down in POT
		if(PINA & 0b00000100 ){
			if(N < 9)
				++N;
			else{
				N = 9;
				disp_xP();
			}
			PORTC |= (1<<0);
			_delay_ms(5);
		}
		else if(PINA & 0b00000010){
			if(N > 0)
				--N;
			else{
				N = 0;
				disp_x();
			}

			PORTC |= (1<<0);
			_delay_ms(5);
		}

		if(N==0)
			disp_g0();
		else if (N==1)
			disp_g1();
		else if (N==2)
			disp_g2();
		else if (N==3)
			disp_g3();
		else if (N==4)
			disp_g4();
		else if (N==5)
			disp_g5();
		else if (N==6)
			disp_g6();
		else if (N==7)
			disp_g7();
		else if (N==8)
			disp_g8();
		else if (N==9)
			disp_g9();
		else if (N < 0)
			disp_x();
		else
			disp_xP();

		//Reinitiateion PORTB to be on the SPI transmittion mode
		//DDRB |= (1<<PB1) | (1<<PB2) | (1<<5) | (1<<7);
		DDRB |= (1<<PB1) | (1<<PB2) | (1<<5) | (0<<7);

		//Reinite PORTC to be the SPI out
		DDRC = 0xFF;

		//Send the signal 
		//The first part, 8bits, is the command code
		//The second part, 8bits, is the resistor value
		spi_trans_master(arr);
	}
}
