/*============================ INCLUDE =======================================*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include "com.h"

/*============================ DEFINES ========================================*/
#define COM_RX_BUFFER_SIZE 128  //Added by Matt
/*============================ MACROS ========================================*/
#define COM_RX_MAX_BYTES (COM_RX_BUFFER_SIZE - 2) //!< Maximal number of bytes that one message can contain (PSDU_LENGTH - CRC_LENGTH).
/*============================ TYPEDEFS ======================================*/
/*============================ VARIABLES =====================================*/
static uint8_t com_buffer[ COM_RX_BUFFER_SIZE ]; //!< Array storing rx data.
static uint8_t com_number_of_received_bytes; //!< Number of bytes in com_buffer.
static bool com_data_reception_finished; //!< Flag indicating EOT (That "\r\n is received.")
/*============================ PROTOTYPES ====================================*/

void com_init( baud_rate_t rate ){
   
    //Initialize USART module.
    UBRR0H = 0x00;
    UBRR0L = rate;
  
    //Enable USART transmitter module. Always on.
    ENABLE_RECEIVER;
    ENABLE_TRANSMITTER;
	
    //8-N-1.
    UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 );
  
    com_number_of_received_bytes = 0;
    com_data_reception_finished = false;
    ENABLE_RECEIVE_COMPLETE_INTERRUPT;

}

void TxD8(uint8_t bTxdData){
	while(!TRANSMITTER_READY);
	TRANSMITTER_DATA = bTxdData;
}

void debug_print_new_line( void ) {
	debug_print_str("\n\r");
}

void debug_print_hex(uint8_t bSentData){

	uint8_t bTmp;
	bTmp =((uint8_t)(bSentData>>4)&0x0f) + (uint8_t)'0';
	
	if(bTmp > '9') bTmp += 7;
	
	TxD8(bTmp);
	
	bTmp =(uint8_t)(bSentData & 0x0f) + (uint8_t)'0';
	
	if(bTmp > '9') bTmp += 7;
	
	TxD8(bTmp);
}

void debug_print_char(char *bSentData){

	TxD8(*bSentData);

}

void debug_print_str_len(char *bData, uint8_t length){

	int count = 0;

	while(count < length){
		TxD8(bData[count++]);
	}
}

void debug_print_str(char *bData){

	while(*bData){
		TxD8(*bData++);
	}

}

char com_receive_char(void) {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void TxD32Dec(long lLong){
	uint8_t bCount, bPrinted;
	long lTmp,lDigit;
	bPrinted = 0;
	
	if(lLong < 0){
		lLong = -lLong;
		TxD8('-');
	}
	
	lDigit = 1000000000L;
	
	for(bCount = 0; bCount < 9; bCount++){
	
		lTmp = (uint8_t)(lLong/lDigit);
		
		if(lTmp){
			TxD8(((uint8_t)lTmp)+'0');
			bPrinted = 1;
		}
		
		else if(bPrinted) 
		TxD8(((uint8_t)lTmp)+'0');
		
		lLong -= ((long)lTmp)*lDigit;
		lDigit = lDigit/10;
	}
	
	lTmp = (uint8_t)(lLong/lDigit);
	
	TxD8(((uint8_t)lTmp)+'0');
}

/*! \brief This function retruns the address to the first byte in the buffer where received data is stored3.
 *  
 *  \note This function should only be called after it has been verified that the 
 *        data reception is done (com_get_number_of_received_bytes() != 0).
 *  \return Pointer to the first byte in the array of received data.
 */

uint8_t* com_get_received_data( void ){
    return com_buffer;
}

uint8_t com_is_receive_complete( void ){
    return com_data_reception_finished;
}

void com_clear_rx_complete_flag( void ){
    com_data_reception_finished = false;
}


/*! \brief This function returns number of bytes received during last data reception.
 *  
 *  \retval 0 No data is available. Data reception is not done.
 *  \retval 1 Error: Typed Frame Too Long.
 *  \return Any non zero value returned indicatest that data is available and should be read.
 */
uint8_t com_get_number_of_received_bytes( void ){
    
    if (com_data_reception_finished == true) {
        return com_number_of_received_bytes; 
    } else { return 0; }
}

/*! \brief This function is used to reset the commuincation interface after each 
 *         data reception is done, and the end-user has read data.
 *  
 */
void com_reset_receiver( void ){
       
    DISABLE_RECEIVE_COMPLETE_INTERRUPT;
    
    com_number_of_received_bytes = 0;
    com_data_reception_finished = false;
    
    uint8_t dummy = 0;
    //Following loop is used to ensure that the rx FIFO is flushed.
	//Sometimes it gets cloged up with old data.
	for( ;  UCSR0A & ( 1 << RXC0 ); ){
		dummy = UDR0;  
	}
    
    ENABLE_RECEIVE_COMPLETE_INTERRUPT;

}

//ISR( USART0_RX_vect ){

void usart_interrupt_function( void ){	
  	uint8_t receivedData;
	
	receivedData = ( uint8_t )UDR0;	//Collect data.
	
    if (com_number_of_received_bytes < COM_RX_MAX_BYTES) {
        
	//	debug_print_char((char*)&receivedData);
		
        //End of data stream.
        if (receivedData == 10 || receivedData == 13) {
            DISABLE_RECEIVE_COMPLETE_INTERRUPT;
			
        //    com_buffer[com_number_of_received_bytes++] = receivedData;  //ignore the newline character
		com_buffer[com_number_of_received_bytes++] = 0x00;  	//adds a terminating null character
		com_buffer[com_number_of_received_bytes++] = 0x00;  	//adds a terminating null character
		com_number_of_received_bytes -= 2;			//compensates for the extra nulls
		
		            			
		/*	debug_print_new_line();
			debug_print_str("Length: ");
	                debug_print_hex(com_number_of_received_bytes);
			debug_print_new_line();
			debug_print_new_line();
		*/	
			
            com_data_reception_finished = true;
        } else {
            com_buffer[com_number_of_received_bytes++] = receivedData;
        }
    }
    else{  
        DISABLE_RECEIVE_COMPLETE_INTERRUPT;                  
        com_number_of_received_bytes = 1;
        com_data_reception_finished = true;
    }
}
