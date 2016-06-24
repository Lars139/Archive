
#ifndef COM_H
#define COM_H
/*============================ INCLDUE =======================================*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>

/*============================ MACROS ========================================*/
#define ENABLE_RECEIVER  ( UCSR0B |= ( 1 << RXEN0 ) ) /*!< Enables receiver. */
#define DISABLE_RECEIVER ( UCSR0B &= ~( 1 << RXEN0 ) ) /*!< Disables receiver. */

#define ENABLE_TRANSMITTER  ( UCSR0B |= ( 1 << TXEN0 ) ) /*!< Enables transmitter. */
#define DISABLE_TRANSMITTER ( UCSR0B &= ~( 1 << TXEN0 ) ) /*!< Disables transmitter. */

#define ENABLE_RECEIVE_COMPLETE_INTERRUPT  ( UCSR0B |= ( 1 << RXCIE0 ) ) /*!< Enables an interrupt each time the receiver completes a symbol. */
#define DISABLE_RECEIVE_COMPLETE_INTERRUPT ( UCSR0B &= ~( 1 << RXCIE0 ) ) /*!< Disables an interrupt each time the receiver completes a symbol. */

#define TRANSMITTER_READY ( UCSR0A & (1 << UDRE0) )
#define TRANSMITTER_DATA UDR0

#define LOW ( 0x00 )
#define XRAM_ENABLE( )     XMCRA |= ( 1 << SRE ); XMCRB |= ( 1 << XMBK )
#define XRAM_DISABLE( )    XMCRA &= ~( 1 << SRE )

#define TERM_BUFFER_LENGTH 128

#define BAUD 19200
#define FOSC 16000000
#define MYUBBR FOSC/(8*BAUD) -1

#define USART_ISR ISR( USART0_RX_vect ){\
    usart_interrupt_function();\
}

/*============================ TYPEDEFS ======================================*/
/*! \brief  Enumeration that defines the available baud rates for\n
 *          the serial interface. The values cana be found in the
 *          datasheet on page 233.
 *  
 *  \note The members should not be altered. This is possibly harmful for\n
 *        setting of the baud rate registers in serialInterfaceInitialization.
 */
typedef enum{
  
  BR_19200  = 0x33, /*!< Sets the baud rate to 9600. */
  BR_38400 = 0x19, /*!< Sets the baud rate to 19200. */

}baud_rate_t;
/*============================ VARIABLES =====================================*/
/*============================ PROTOTYPES ====================================*/

void com_init( baud_rate_t rate );
void com_send_string( uint8_t *data, uint8_t data_length );
void com_send_hex( uint8_t nmbr );
uint8_t * com_get_received_data( void );
uint8_t com_get_number_of_received_bytes( void );
char* com_receive_line( uint8_t* length );
char com_receive_char(void);
void com_reset_receiver( void );
uint8_t com_is_receive_complete( void );
void com_clear_rx_complete_flag(void);
uint8_t terminal_read_line ( char* );

void debug_print_hex( uint8_t bSentData );
void debug_print_str_len( char* ,  uint8_t );
void debug_print_str( char* );
void debug_print_new_line( void );
void debug_print_char( char* );

void TxD32Dec( long lLong );

void TxD8( uint8_t bTxdData );

void usart_interrupt_function( void );

#endif

