// LCD.h
// Kevin Kemper

/*
 * This header contains all of the functions necessary to display strings or characters to the
 * LCD module on the Mega128 board.
 */



#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#define delay_count 4000  //uP clock in MHz divided by 4000

void cursor_home(void);
void home_line2(void);      
void fill_spaces(void);
void string2lcd(char *lcd_str);
void char2lcd(char a_char);
void int2lcd(int an_int);


//delays by 1ms increments
void delay_ms1(uint8_t ms)
{
  uint16_t cnt;
    asm volatile (
      "\n"
      "L_dl1%=:"       "\n\t"
      "mov %A0, %A2"   "\n\t"
      "mov %B0, %B2"   "\n"
      "L_dl2%=:"       "\n\t"
      "sbiw %A0, 1"    "\n\t"
      "brne L_dl2%="   "\n\t"
      "dec %1"         "\n\t"
      "brne L_dl1%="    "\n\t"
       : "=&w" (cnt)
       : "r" (ms), "r" (delay_count)
    );
}

//twiddles bit 3, PORTF creating the enable signal for the LCD
void strobe_lcd(void){
	PORTF |= 0x08;
	PORTF &= 0xF7;
  }          
 

void clear_display(void){
	SPDR = 0x00;    //command, not data
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x01;    //clear display command
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();   //strobe the LCD enable pin
	delay_ms1(2);   //obligatory waiting for slow LCD
}         


/*
 * Moves the cursor to the specified location. If row is 0, the text will appear on the first line
 * else is will appear on the second line. Col is a number between 0 and 15 and represents where
 * the text will begin along the line.
 */
void move_cursor(uint8_t row , uint8_t col){
	
	uint8_t loc = col | (row << 6) | (1 << 7);

	SPDR = 0x00;    //command, not data
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = loc;   // cursor go to location
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd(); 
	delay_ms1(2);  
}

void cursor_home(void){
	move_cursor(0,0);
}


void fill_spaces(void){
	int count;
	for (count=0; count<=15; count++){
		SPDR = 0x01; //set SR for data
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		SPDR = 0x20; 
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		strobe_lcd();
		delay_ms1(1);
	}
}  


//sends a char to the LCD
//usage: char2lcd('H');  // send an H to the LCD
void char2lcd(char a_char){  
	SPDR = 0x01;   //set SR for data xfer with LSB=1
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = a_char; //send the char to the SPI port
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();  //toggle the enable bit
	delay_ms1(1); //wait the prescribed time for the LCD to process
 }
  
//sends an int to the LCD
//usage: int2lcd(Integer);  // send an Integer, up to 9999 to the LCD
void int2lcd(int an_int){  
	char2lcd((an_int/1000)+48); //send the 1000's digit to the SPI port
	char2lcd(((an_int/100)%10)+48); //send the 1000's digit to the SPI port
	char2lcd(((an_int/10)%10)+48); //send the 1000's digit to the SPI port
	char2lcd((an_int%10)+48); //send the 1000's digit to the SPI port
 }  
  
  
//sends a string to LCD
void string2lcd(char *lcd_str){
	int count;
	for (count=0; count<=(strlen(lcd_str)-1); count++){
		SPDR = 0x01; //set SR for data
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		SPDR = lcd_str[count]; 
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		strobe_lcd();
		delay_ms1(1);
	}                  
} 


/* Run this code before attempting to write to the LCD.*/

// This will enable the SPI correctly for talking to the LCD
void spi_init(void){ 
	DDRF |= 0b00001000;	//port F bit 3 is enable for LCD
	PORTB = 0x00;		//port B initalization for SPI
	DDRB |= 0b00000111;	//Turn on SS, MOSI, SCLK 
 
	 //Master mode, Clock=clk/2, Cycle half phase, Low polarity, MSB first  
	SPCR=0x50;
	SPSR=0x01;
 }


/* Run this code before attempting to write to the LCD.*/

//initalize the LCD to receive data
void lcd_init(void){
	int i;

	delay_ms1(15);   
	for(i=0; i<=2; i++){ //do funky initalize sequence 3 times
		SPDR = 0x00;
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		SPDR = 0x30;
		_delay_loop_1(9); //wait 2us  for data to leave SPI port
		strobe_lcd();
		delay_ms1(7);
	}
    
	SPDR = 0x00;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x38;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();
	delay_ms1(5);   
   
	SPDR = 0x00;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x08;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();
	delay_ms1(5);
   
	SPDR = 0x00;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x01;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();
	delay_ms1(5);   
   
	SPDR = 0x00;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x06;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();
	delay_ms1(5);
   
	SPDR = 0x00;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	SPDR = 0x0E;
	_delay_loop_1(9); //wait 2us  for data to leave SPI port
	strobe_lcd();
	delay_ms1(5);
} 



