;***********************************************************
;*
;*	 Author: Rattanai Sawaspanich && Kyle Sweeney
;*	   Date: 11/4/2014
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multi-Purpose Register
.def	waitcounter = r17
.def	innercount = r18
.def	outercount = r19
.def	tmp = r20
.def	idf = r21
.def	tik = r22

.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit
.equ	Dv_ID = $09


;/////////////////////////////////////////////////////////////
;These macros are the values to make the TekBot Move.
;/////////////////////////////////////////////////////////////

.equ	MoveForward =  (1<<EngDirR|1<<EngDirL)	;0b01100000 Move Forwards Command
.equ	MoveBack =  $00						;0b00000000 Move Backwards Command
.equ	TurnR =   (1<<EngDirL)				;0b01000000 Turn Right Command
.equ	TurnL =   (1<<EngDirR)				;0b00100000 Turn Left Command
.equ	Halt =    (1<<EngEnR|1<<EngEnL)		;0b10010000 Halt Command

;Recieve commands
.equ	backward =  0b10000000
.equ	forward =   0b10110000
.equ	turnRight = 0b10100000
.equ	turnLeft =  0b10010000
.equ	doHalt	=	0b11001000
.equ	freeze =    0b11111000

;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

;Should have Interrupt vectors for:
.org $0002 ;right
	  rcall BUMPR ;{pin0}
	  reti
.org $0004 ;left
      rcall BUMPL ;{pin1}
	  reti
.org $003C
	  rcall USART_RECIEVE
	  reti
.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
INIT:
	;Stack Pointer 
		ldi mpr, LOW(RAMEND) 
		out spl, mpr         
		ldi mpr, HIGH(RAMEND)
		out sph, mpr

	;I/O Ports
		ldi		mpr, (1<<EngEnl|1<<EngEnr|1<<EngDirR|1<<EngDirL) 
		out		DDRB, mpr
		ldi		mpr, MoveForward		; Initialize Port B for outputs
		out		PORTB, mpr			;
		ldi		mpr, (1<<WskrL|1<<WskrR | 1<<2)		; Initialize Port D for inputs
		out		PORTD, mpr		; with Tri-State
		ldi		mpr, $00		; except for any overrides
		out		DDRD, mpr		

	;USART1
		;Set rate double
		ldi mpr, (1<<u2x1)
		sts UCSR1A, mpr

		;Set baudrate at 2400bps
		ldi mpr, high(832)
		sts UBRR1H, mpr
		ldi mpr, low(832)
		sts UBRR1L, mpr

		;Enable receiver and enable receive interrupts
		ldi mpr, (1<<RXEN1 | 1<<RXCIE1 | 1<<TXEN1)
		sts UCSR1B, mpr
		;Set frame format: 8data bits, 2 stop bit
		ldi mpr, (0<<UMSEL1 | 1<<USBS1 | 1<<UCSZ11 | 1<< UCSZ10| 1<<UPM11)
		sts UCSR1C, mpr ;since in extened I/O space
	
	;External Interrupts
		;Set the External Interrupt Mask
		ldi mpr, (1<<INT0|1<<INT1)
		out EIMSK, mpr
		;Set the Interrupt Sense Control to low level detection
		ldi mpr, $00 
		sts EICRA, mpr
		ldi mpr, $0A ;(0b00001010)
		sts EICRB, mpr

	;Other
		clr	tik  ;clear the freeze counter
	sei

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:

		; Turn left for a second
		;ldi mpr, 0b00000000
		;out PORTB, mpr

		rjmp	MAIN

;***********************************************************
;*	Functions and Subroutines
;***********************************************************
;-----------------------------------------------------------
; Func: Handle the Bump for RIGHT!
; Desc: Handle the bump
;-----------------------------------------------------------
BUMPR:
		; Save variable by pushing them to the stack
		push mpr
		push waitcounter
		in mpr, SREG
		push mpr
		; Execute the function here
		; Move Backwards
		ldi mpr, MoveBack
		out PORTB, mpr
		ldi waitcounter, 100 ;wait for a second
		rcall WAIT
		; Turn left for a second
		ldi mpr, TurnL
		out PORTB, mpr
		ldi waitcounter, 100 ; wait for a second
		rcall WAIT

		; Restore variable by popping them from the stack in reverse order
		pop mpr
		out SREG, mpr
		pop waitcounter
		pop mpr
		ret		; End a function with RET
;-----------------------------------------------------------
; Func: Handle the Bump for Left!
; Desc: Handle the bump
;-----------------------------------------------------------
BUMPL:
		; Save variable by pushing them to the stack
		push mpr
		push waitcounter
		in mpr, SREG
		push mpr
		; Execute the function here
		; Move Backwards
		ldi mpr, MoveBack
		out PORTB, mpr
		ldi waitcounter, 100 ;wait for a second
		rcall WAIT
		; Turn left for a second
		ldi mpr, TurnR
		out PORTB, mpr
		ldi waitcounter, 100 ; wait for a second
		rcall WAIT

		; Restore variable by popping them from the stack in reverse order
		pop mpr
		out SREG, mpr
		pop waitcounter
		pop mpr
		ret		; End a function with RET
;-----------------------------------------------------------
; Func: Wait
; Desc: Waiting for a time, as said by waitcounter
;-----------------------------------------------------------
WAIT:	; Begin a function with a label
		OLOOP:
			ldi outercount, 224
		MLOOP:
			ldi innercount, 237
		ILOOP:
			dec innercount
			brne ILOOP
			dec outercount
			brne MLOOP
			dec waitcounter
			brne OLOOP
			ret
;-----------------------------------------------------------
; Func: USART_RECIEVE
; Desc: Called for when usart is done recieving data
;-----------------------------------------------------------
USART_RECIEVE:
	;Push stuff
	push mpr
	in mpr, SREG
	push mpr

	lds mpr, UCSR1A
	sbrc mpr, UPE1
	jmp DONE

	;main part
	lds r17, UDR1
	cpi r17, 0b11111000
	breq stay_frosty

	;Check if the ID has been set

	cpi idf, $FF		;if so, do the command!
	breq DECODE_COMMAND	

	;The ID has not been set
	cpi r17, Dv_ID
	breq send_me_in_coach
	clr idf	;It's not me coach

	jmp DONE


;----------------------------------------------------------------
; Sub:	stay_frosty
; Desc:	The subroutine is called when the robot got hit by the deathray
; Input: 1) info from IR
; Output: Robot's debuff / Death
;----------------------------------------------------------------

stay_frosty:
		cli
		cpi	tik, $03	;check if it has been 3 times
		breq GG			;if it is, GG

		inc tik			;increment freeze counter
		ldi mpr, freeze	;output led
		out PORTB, mpr

		ldi waitcounter, 100 ;that tenacity tho
		rcall WAIT		

		sei
		ret

;----------------------------------------------------------------
; Sub:	GG
; Desc:	
;	This subroutine is called when the robot got frozen 3 times and out of the game
;----------------------------------------------------------------

GG:
		cli
		ldi	mpr,	0b11111111
		out PORTB, mpr
		jmp GG


;----------------------------------------------------------------
; Sub:	FR_Trans (Frozen)
; Desc:	
;	Call USART_Trans subroutine
;			1) Send the death ray to another robot
; Input: 1) info from IR
; Output: Deathray
;----------------------------------------------------------------
FR_Trans:
	ldi	r16, 0b11111000
	rcall USART_Trans
ret

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
; Sub:	send_me_in_coach
; Desc:	this subroutine get the Device ID and set the idf to be 1 
; if the ID transmitted is the device's id.
; Input: UDR1 (Bot ID)
; Output: Set idf(R21) to 1
;----------------------------------------------------------------

send_me_in_coach:
	ldi idf, $FF
	jmp DONE
	

;----------------------------------------------------------------
; Sub:	DECODE_COMMAND
; Desc:	this subroutine decode the signal from IR 
;----------------------------------------------------------------


DECODE_COMMAND:
		lds r17, UDR1
		cpi r17, backward
		breq RW_Rcv
		cpi r17, forward
		breq FF_Rcv
		cpi r17, turnRight
		breq TR_Rcv
		cpi r17, turnLeft
		breq TL_Rcv
		cpi r17, doHalt
		breq HT_Rcv
		cpi  r17, freeze
		breq FR_Rcv
		jmp DONE

	;subroutines
	RW_Rcv:
		ldi mpr, MoveBack 
		out PORTB, mpr
		jmp DONE
	FF_Rcv:
		ldi mpr, MoveForward 
		out PORTB, mpr
		jmp DONE
	TR_Rcv:
		ldi mpr, TurnR 
		out PORTB, mpr
		jmp DONE
	TL_Rcv:
		ldi mpr, TurnL 
		out PORTB, mpr
		jmp DONE
	HT_Rcv:
		ldi mpr, Halt 
		out PORTB, mpr
		jmp DONE
	FR_Rcv:
		rcall FR_Trans	;send the freeze laser beam
		ldi mpr, 0b10101010
		out PORTB, mpr
		jmp DONE



;----------------------------------------------------------------
; Sub:	DONE
; Desc:	
;	pop the stack and return to MAIN
;----------------------------------------------------------------
DONE:
	;pop
	pop mpr
	out SREG, mpr
	pop mpr
	ret

