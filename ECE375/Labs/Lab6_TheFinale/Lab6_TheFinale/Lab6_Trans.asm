;***********************************************************
;*
;*  
;*  IR USART (Transmitter and Reciever)
;*	for a transmit, get rid of the init for moving and sei moving stuff
;*  for a reciever, need to set up the inite stuff 
;*
;***********************************************************
;*
;*	 Author: Bear
;*	   Date: 11/3/2014
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
; Constants for interrupts (Already defined in .inc)
;.equ	INT3 = 3
;.equ	INT7 = 7
;.equ	ISC31 = 7
;.equ	ISC30 = 6
;.equ	ISC71 = 7
;.equ	ISC70 = 6

; Using the constants from above, create the movement 
; commands, Forwards, Backwards, Stop, Turn Left, and Turn Right

;************************************************************
;* Variable and Constant Declarations
;************************************************************
.def	mpr = r16				; Multi-Purpose Register
.def	temp = r20				; temp
.def	tmp = r21				; another temp

.equ	WTime = 100				; Time to wait in wait loop

.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit

.equ	Dv_ID = $09 				; Setting my device ID to be sent (Device ID is 0xBE [for BEAR])

;/////////////////////////////////////////////////////////////
;These macros are the values to make the TekBot Move.
;/////////////////////////////////////////////////////////////

;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

.org	$0040
		rjmp	MAIN

.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
INIT:	; The initialization routine
; Initilize the Stack Pointer 
		ldi		mpr, low(RAMEND)
		out		SPL, mpr		; Load SPL with low byte of RAMEND
		ldi		mpr, high(RAMEND)
		out		SPH, mpr		; Load SPH with high byte of RAMEND

; Initialize the I/O ports
		; Initialize Port B for output
		ldi		mpr, $00		; Initialize Port B for outputs
		out		PORTB, mpr		; Port B outputs low
		ldi		mpr, $FF		; Set Port B Directional Register
		out		DDRB, mpr		; for output

		; Initialize Port D for inputs
		ldi		mpr, $FF		; Initialize Port D for inputs
		out		PORTD, mpr		; with Tri-State
		ldi		mpr, $00		; Set Port D Directional Register
		out		DDRD, mpr		; for inputs

; Initializeing the USART1
		
		;Set rate double
		ldi mpr, (1<<u2x1)
		sts UCSR1A, mpr

		ldi  r16, low(832)
		ldi  r17, high(832)

		sts UBRR1H, r17 ;Set baudrate at 2400bps
		sts UBRR1L, r16


		;Set frame format: 8data, 2 stop bit
		;ldi r16, (3<<UCSZ11|0<<UCSZ12|1<<USBS1|0<<UMSEL1|1<<UPM11)
		ldi r16, (0<<UMSEL1 | 1<<USBS1 | 1<<UCSZ11 | 1<<UCSZ10 | 0<<UCSZ12 | 1<<UPM11)
		sts UCSR1C, r16

		;Enable transmitter (and receiver : RXEN1)
		ldi r16, (1<<TXEN1)
		sts UCSR1B, r16

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:	; The Main program

		;bunch of if-else to check the pressed button
		;make sure to put the stuff in R16 to be sent via USART
		
		
		in temp, PIND		;polling

		;sbrs mpr, 7			;if PIND bit 7 is set then....
		;out PORTB, mpr
		
		;switch case once get the input
		sbrs temp, 7			;if PIND bit 7 is set then....
		rcall FF_Trans		;then do this
		sbrs temp, 6			;if PIND bit 6
		rcall RW_Trans		;send backward command
		sbrs temp, 5			;if PIND bit 5
		rcall FR_Trans		;send backward command
		sbrs temp, 1			;if PIND bit 1
		rcall TR_Trans		;send left command
		sbrs temp, 0			;if PIND bit 0
		rcall TL_Trans		;send right command

		
		
		rjmp	MAIN			; Create an infinite while loop to signify the 
								; end of the program.

;----------------------------------------------------------------
; Sub:	USART_Trans
; Desc:	Use USART to transmit the data in the buffer.
;	The function will wait until the transmit buffer is empty 
;	then proceed to transmit the data info.
; Input: The subroutine will take whatever stored in R16 (length: 8 bits)
; Output: The USART will output via UDR (I)
;----------------------------------------------------------------
USART_Trans:
	;wait for empty transmit buffer
	
	lds tmp, UCSR1A
	sbrs tmp, UDRE1		;check if the USART buffer is empty 
	rjmp USART_Trans					;(if UDRE1 is set do the next line, if UDRE1 is not set do the next next line. OPP: sbrc)
	
	;send the data
	;out PORTB, temp
	sts UDR1, r16		;out PORTB, r16

ret

;----------------------------------------------------------------
; Sub:	FF_Trans (Forward)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b10110000)
; Output: UDR(I) will send 0xBE and 0b10110000 
;----------------------------------------------------------------
FF_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b10110000
	rcall USART_Trans
ret


;----------------------------------------------------------------
; Sub:	RW_Trans (Reverse)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b10000000)
; Output: UDR(I) will send 0xBE and 0b10000000 
;----------------------------------------------------------------
RW_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b10000000
	rcall USART_Trans
ret

;----------------------------------------------------------------
; Sub:	FR_Trans (Frozen)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b11111000)
; Output: UDR(I) will send 0xBE and 0b11111000
;----------------------------------------------------------------
FR_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b11111000
	rcall USART_Trans
ret



;----------------------------------------------------------------
; Sub:	TR_Trans (Turn Right)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b10100000)
; Output: UDR(I) will send 0xBE and 0b10100000 
;----------------------------------------------------------------
TR_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b10100000
	rcall USART_Trans
ret

	
;----------------------------------------------------------------
; Sub:	TL_Trans (Turn Left)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b10010000)
; Output: UDR(I) will send 0xBE and 0b10010000 
;----------------------------------------------------------------
TL_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b10010000
	rcall USART_Trans
ret

;----------------------------------------------------------------
; Sub:	HT_Trans (Halt)
; Desc:	
;	Call USART_Trans subroutine
;		1) Send Device ID
;		2) Send the button press action
; Input: 1) Device ID (0xBE)     2) The action to be send (0b10110000)
; Output: UDR(I) will send 0xBE and 0b11001000
;----------------------------------------------------------------
HT_Trans:
	;sending the device ID
	ldi	r16, Dv_ID
	rcall USART_Trans
	ldi	r16, 0b11001000
	rcall USART_Trans
ret

