/******************************************************************************
 * Project:	 ECE111 2010 Research
 * Author:	 Matthew Shuman
 * Date:  	 8/25/2009
 * Sources:	 None
 * Description:  This program will allow the Mega128 board to be controlled through Matlab or Labview
 * 
 *****************************************************************************/ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <avr/delay.h>
#include "ADC.h"
#include "LCD.h"
#include "DAC.h"
#include "com.h"

#include <avr/interrupt.h>
#include <avr/signal.h>

unsigned int NormalizedIR[8];


ISR( __vector_default ){
    clear_display();
    cursor_home();
    string2lcd("BAD ISR FOUND!");
}

USART_ISR

int main (void) {
    unsigned char i;
    unsigned char mode=0;
    unsigned int Number=100;
    
    //Setting Input or Output Direction
    //0 = Input
    //1 = Output
    DDRD = 0x00;
    
    //Setting initial value for PORTS
    PORTD = 0x00;

    ADCInit();
    com_init(BR_19200);
    com_reset_receiver();
    spi_init();
    lcd_init();
    DAC_init();
	
    clear_display();
    cursor_home();
    
    sei();
    
    while(1)
    {   
	///////////////////////// Mode Selection //////////////////
	if(((PIND&(1<<PIND7)))==0){     
            mode = 8;
            clear_display();
            cursor_home();
            string2lcd("Mode: 8");
            move_cursor(1,0);
            string2lcd("S8 PuShEd");
        }
        if(((PIND&(1<<PIND6)))==0){     
            mode = 7;
            clear_display();
            cursor_home();
            string2lcd("Mode: 7");
            move_cursor(1,0);
            string2lcd("s7");        
        }
        if(((PIND&(1<<PIND1)))==0){     
            mode = 2;
            clear_display();
            cursor_home();
            string2lcd("Mode: 2");
            move_cursor(1,0);
            string2lcd("S2 was pushed");        
        }
        if(((PIND&(1<<PIND0)))==0){     
            mode = 1;
            clear_display();
            cursor_home();
            string2lcd("Mode 1");
            move_cursor(1,0);
            string2lcd("s1 was pushed");        
        }
        
        /////////////////////// Mode Actions /////////////////////
		if(mode ==1){
			if(com_get_number_of_received_bytes() != 0){
				cursor_home();
				////////////////////// This section is a switch for sending in commands through the USART
				
				//sets a custom static voltage, d(high byte)(low byte)
				if((com_get_number_of_received_bytes() == 2) && (com_get_received_data()[0]=='d')){ 
			//		clear_display();
					cursor_home();
			//		string2lcd("Mode: 3, custom");
					move_cursor(1,0);
					string2lcd("Read ");
					char2lcd(com_get_received_data()[0]);
					char2lcd(com_get_received_data()[1]);
				}
				//requests an ADC measurement, a(ADC Channel)
				if((com_get_number_of_received_bytes() == 2) && (com_get_received_data()[0]=='a')){
			//		clear_display();
					cursor_home();
					string2lcd("ADC (");
					char2lcd(com_get_received_data()[1]);
					string2lcd(") = ");
			//		move_cursor(1,0);
			//		string2lcd("Result is ");
					Number = ADCRead(com_get_received_data()[1]); 
					int2lcd(Number);
					TxD8(Number / 256);
					TxD8(Number % 256);
//				debug_print_char(Number / 256);
//				debug_print_char(Number % 256);
				}		  
				com_reset_receiver();
			}
		} //end of mode 1
		 /////////////////////// Mode Actions /////////////////////
		if(mode ==2){
			if(com_get_number_of_received_bytes() != 0){
				cursor_home();
				////////////////////// This section is a switch for sending in commands through the USART
				string2lcd("Something");
					  
				com_reset_receiver();
			}
		} //end of mode 1
		
		
    } //end of while(1)
} //end of main()
