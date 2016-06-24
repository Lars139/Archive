// DAC.h
// Matthew Shuman

/*
 * This header contains all of the functions necessary to set voltages
 * on a MAX 5453 DAC through SPI.
 */



#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#define delay_count 4000  //uP clock in MHz divided by 4000

void set_DAC(void);
  

// Run this code before attempting to use the DAC

// This will enable the SPI correctly for talking to the DAC
void DAC_init(void){ 
	DDRB |= 0b00000111;	//Turn on CS, MOSI, SCLK 
 
	 //Master mode, Clock=clk/2, Cycle half phase, Low polarity, MSB first  
	SPCR=0x50;
	SPSR=0x01;
}


// This code writes to the DAC
void DAC_set(int DAC_Value){ 
	if(DAC_Value <= 1023){
	
		PORTB &= 0xFE;	  //lower CS
	 
	 	SPDR = 0x00 | (DAC_Value>>5);
	 	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	 	SPDR = 0x00 | (DAC_Value & 0x1f)<<3;
	 	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	 	
	 	PORTB |= 0x01;    //raise CS
	 }
}

