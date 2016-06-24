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
.def	waitcnt = r17				; Wait Loop Counter
.def	ilcnt = r18				; Inner Loop Counter
.def	olcnt = r19				; Outer Loop Counter

.equ	WTime = 100				; Time to wait in wait loop

.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit

;/////////////////////////////////////////////////////////////
;These macros are the values to make the TekBot Move.
;/////////////////////////////////////////////////////////////

.equ	MovFwd = (1<<EngDirR|1<<EngDirL)	; Move Forwards Command
.equ	MovBck = $00				; Move Backwards Command
.equ	TurnR = (1<<EngDirL)			; Turn Right Command
.equ	TurnL = (1<<EngDirR)			; Turn Left Command
.equ	Halt = (1<<EngEnR|1<<EngEnL)		; Halt Command
.equ	Freez =   ($80|$F8)			;GG I'm out.


;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

;Mah Interrutp!

.org	$0006 ;INT2, EICRB, Handle when the right is hit
		rcall HitLeft
	reti

.org	$0008 ;INT3, EICRA, Handle when the left thigy is hit
		rcall HitRight
	reti

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
		
		ldi  r16, low(832)
		ldi  r17, high(832)

		out UBRRH, r17 ;Set baudrate at 2400bps
		out UBRRL, r16

		;Enable transmitter (and receiver : RXEN)
		ldi r16, (1<<RXEN)|(1<<TXEN)
		out UCSRB, r16

		;Set frame format: 8data, 2 stop bit
		ldi r16, (1<<USBS)|(3<<UCSZ0)
		out UCSRC, r16

; Initialize external interrupts
		; Set the Interrupt Sense Control to low level 
		; NOTE: must initialize both EICRA and EICRB
		ldi mpr, (0<<ISC31| 0<<ISC30)
		sts	EICRA, mpr	; I chose risen clock, ISC3n
		ldi mpr, (0<<ISC21| 0<<ISC20) 
		sts EICRA, mpr ; I chose risen clock, ISC2n
		;I don't really need EICRB I could have just put the thing in EICRA

		; Set the External Interrupt Mask
		ldi mpr, (1<<INT3|1<<INT2)
		out EIMSK, mpr	; I chose you ISC3n, ISC2n

		; Turn on interrupts\
		SEI
		;ldi mpr, (1<<7)
		;out SREG, mpr ; Release the karaken!
		; NOTE: This must be the last thing to do in the INIT function

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:	; The Main program

		;bunch of if-else to check the pressed button
		;make sure to put the stuff in R16 to be sent via USART
		; Send command to Move Robot Forward 
		ldi		mpr, (1<<5|1<<6) ; enable set 1 to moving L, R
		out		PORTB, mpr		; Move!

		rjmp	MAIN			; Create an infinite while loop to signify the 
								; end of the program.


;----------------------------------------------------------------
; Sub:	HitRight
; Desc:	Handles functionality of the TekBot when the right whisker
;		is triggered.
;----------------------------------------------------------------
HitRight:
		push	mpr			; Save mpr register
		push	waitcnt			; Save wait register
		in		mpr, SREG	; Save program state
		push	mpr			;

		; Move Backwards for a second
		ldi		mpr, MovBck	; Load Move Backwards command
		out		PORTB, mpr	; Send command to port
		ldi		waitcnt, WTime	; Wait for 1 second
		rcall	Wait			; Call wait function

		; Turn left for a second
		ldi		mpr, TurnL	; Load Turn Left Command
		out		PORTB, mpr	; Send command to port
		ldi		waitcnt, WTime	; Wait for 1 second
		rcall	Wait			; Call wait function

		; Move Forward again	
		ldi		mpr, MovFwd	; Load Move Forwards command
		out		PORTB, mpr	; Send command to port

		pop		mpr		; Restore program state
		out		SREG, mpr	;
		pop		waitcnt		; Restore wait register
		pop		mpr		; Restore mpr
		ret				; Return from subroutine


;----------------------------------------------------------------
; Sub:	HitLeft
; Desc:	Handles functionality of the TekBot when the left whisker
;		is triggered.
;----------------------------------------------------------------
HitLeft:
		push	mpr			; Save mpr register
		push	waitcnt			; Save wait register
		in		mpr, SREG	; Save program state
		push	mpr			;

		; Move Backwards for a second
		ldi		mpr, MovBck	; Load Move Backwards command
		out		PORTB, mpr	; Send command to port
		ldi		waitcnt, WTime	; Wait for 1 second
		rcall	Wait			; Call wait function

		; Turn right for a second
		ldi		mpr, TurnR	; Load Turn Left Command
		out		PORTB, mpr	; Send command to port
		ldi		waitcnt, WTime	; Wait for 1 second
		rcall	Wait			; Call wait function

		; Move Forward again	
		ldi		mpr, MovFwd	; Load Move Forwards command
		out		PORTB, mpr	; Send command to port

		pop		mpr		; Restore program state
		out		SREG, mpr	;
		pop		waitcnt		; Restore wait register
		pop		mpr		; Restore mpr
		ret				; Return from subroutine

;----------------------------------------------------------------
; Sub:	Wait
; Desc:	A wait loop that is 16 + 159975*waitcnt cycles or roughly 
;		waitcnt*10ms.  Just initialize wait for the specific amount 
;		of time in 10ms intervals. Here is the general eqaution
;		for the number of clock cycles in the wait loop:
;			((3 * ilcnt + 3) * olcnt + 3) * waitcnt + 13 + call
;----------------------------------------------------------------
Wait:
		push	waitcnt			; Save wait register
		push	ilcnt			; Save ilcnt register
		push	olcnt			; Save olcnt register

Loop:	ldi		olcnt, 224		; load olcnt register
OLoop:	ldi		ilcnt, 237		; load ilcnt register
ILoop:	dec		ilcnt			; decrement ilcnt
		brne	ILoop			; Continue Inner Loop
		dec		olcnt		; decrement olcnt
		brne	OLoop			; Continue Outer Loop
		dec		waitcnt		; Decrement wait 
		brne	Loop			; Continue Wait loop	

		pop		olcnt		; Restore olcnt register
		pop		ilcnt		; Restore ilcnt register
		pop		waitcnt		; Restore wait register
		ret				; Return from subroutine
		
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
	sbis UCSRA, UDRE
	rjmp USART_Trans

	;send the data
	out UDR, r16
ret

