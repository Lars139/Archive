/*
 * Lab2_C.c
 *
 * Created: 10/6/2014 12:12:40 PM
 *  Author: sawaspar
 */ 

#define F_CPU 16000000
#define forever for(;;)
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>





int main(void)
{
	DDRB = 0xF0;
	PORTB = PORTB | (0xF0);
	DDRD = 0x00;
	PORTD = 0xFF;
	
    forever
    {
        //TODO:: Please write your application code 
		if(!(PIND & 1)){ //Right hit!
		//if(PIND == 0b11111110) {
		//PORTB = PORTB & (3<<5); //Back up
		//PORTB = PORTB & (0b01100000); //forward
		//PORTB = PORTB & (0b00000000); //backing
			PORTB = PORTB & (0x00); //forward
			_delay_ms(1000);
			PORTB = (1<<5); //Turn left
			_delay_ms(1000);
		}
		if(!(PIND & 2)){ //Left hit!
		//if(PIND == 0b11111101){
			PORTB = PORTB & (0x00);
			_delay_ms(1000);
			PORTB = (1<<6); //Turn right
			_delay_ms(1000);
		}
		PORTB = (3<<5);
		
    }
}