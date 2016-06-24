;*
;*	 Author: Bear
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

.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit

.equ	BotID = $09;(Enter you group ID here (8bits)); Unique XD ID (MSB = 0)

;/////////////////////////////////////////////////////////////
;These macros are the values to make the TekBot Move.
;/////////////////////////////////////////////////////////////

.equ	MoveForward =  (1<<EngDirR|1<<EngDirL)	;0b01100000 Move Forwards Command
.equ	MoveBack =  $00						;0b00000000 Move Backwards Command
.equ	TurnR =   (1<<EngDirL)				;0b01000000 Turn Right Command
.equ	TurnL =   (1<<EngDirR)				;0b00100000 Turn Left Command
.equ	Halt =    (1<<EngEnR|1<<EngEnL)		;0b10010000 Halt Command

;Recieve commands
.equ	backward =  $80 ; 0b10000000
.equ	forward =   $B0 ; 0b10110000
.equ	turnRight = $A0 ; 0b10100000
.equ	turnLeft =  $90 ; 0b10010000
.equ	doHalt	=	$C8 ; 0b11001000
.equ	future_freeze =    $F8 ; 0b11111000

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
.org $0040
	 rcall FINISH_USART_SEND
	 reti
.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
INIT:
	;Stack Pointer (VERY IMPORTANT!!!!)
		ldi mpr, LOW(RAMEND) 
		out spl, mpr         
		ldi mpr, HIGH(RAMEND)
		out sph, mpr
	;I/O Ports
		;ports all good
		ldi		mpr, (1<<EngEnl|1<<EngEnr|1<<EngDirR|1<<EngDirL) 
		out		DDRB, mpr
		ldi		mpr, MoveForward		; Initialize Port B for outputs
		out		PORTB, mpr			;
		ldi		mpr, (1<<WskrL|1<<WskrR | 1<<2)		; Initialize Port D for inputs
		out		PORTD, mpr		; with Tri-State
		ldi		mpr, $00		; except for any overrides
		out		DDRD, mpr		;
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
		ldi mpr, (0<<UMSEL1 | 1<<USBS1 | 1<<UCSZ11 | 1<< UCSZ10 | 1<<UPM11)
		sts UCSR1C, mpr ;since in extened I/O space
	;External Interrupts
		;Set the External Interrupt Mask
		ldi mpr, (1<<INT0|1<<INT1)
		out EIMSK, mpr
		;Set the Interrupt Sense Control to low level detection
		ldi mpr, $00 
		sts EICRA, mpr
		ldi mpr, $0A ;(00001010)
		sts EICRB, mpr

	;Other
	sei
	ldi r22, $00; to see how many times we got frozone

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:

		cpi r24, $01
		breq TRANSMIT_FREEZE


		cpi r22, $03 ;allow 0,1,2
		breq HALT_PERM

		rjmp	MAIN

		HALT_PERM:
			clr mpr
			out EIMSK, mpr
			sts UCSR1B, mpr
			ldi mpr, Halt 
			out PORTB, mpr
			rjmp HALT_PERM

;***********************************************************
;*	Functions and Subroutines
;***********************************************************
;-----------------------------------------------------------
; Func: Transmit the Freeze command
; Desc: What the func title is
;-----------------------------------------------------------
TRANSMIT_FREEZE:
	;we don't want to freeze ourselves... so disallow that
	
	ldi mpr, ( 1<<TXEN1 |1<<TXCIE1| 0<<RXEN1)
	sts UCSR1B, mpr
	;wait for empty transmit buffer
	lds r24, UCSR1A
	sbrs r24, UDRE1		;check if the USART buffer is empty 
	rjmp TRANSMIT_FREEZE

	;send the data
	push r17
	ldi r17, $55;0b01010101
	sts UDR1, r17
	pop r17
	clr r24 ;we sent the freeze command, don't need this flag set anymore
	
	cli
	ldi r17, 200
	ldi mpr, 0b10010000
	out PORTB, mpr
	rcall WAIT
	sei
	

	jmp MAIN
;-----------------------------------------------------------
; Func: Usart send finished
; Desc: re-allow the USART1 to recieve data.
;-----------------------------------------------------------
FINISH_USART_SEND:
	push mpr
	ldi mpr, (1<<RXEN1 | 1<<RXCIE1 | 1<<TXEN1)
	sts UCSR1B, mpr
	pop mpr
	ret
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
		push outercount
		push innercount
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
			pop innercount
			pop outercount
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
	push r17

	;Error Checking
	lds mpr, UCSR1A
	sbrc mpr, UPE1
	jmp DONE

	;main part
	lds r17, UDR1
	cpi r17, $55 ;0b01010101
	breq GOT_FROZEN ; we recieved a freeze command from a robot
	cpi r25, $01 ;have we already recieved the id?
	breq DECODE_COMMAND ;decode the command
	cpi r17, BotID ;we have not recieved the ID, check to see if what we got was the ID
	breq RECIEVED_ID;if we have ID, then do stuff
	clr r25 ;havn't gotten ID or proper command, because reasons, set that
	jmp DONE ;done

	RECIEVED_ID:
		ldi r25, $01
		jmp DONE

	DECODE_COMMAND:
		clr r25
		;out PORTB, r17
		cpi r17, backward
		breq DO_BACK
		cpi r17, forward
		breq DO_FORWARD
		cpi r17, turnRight
		breq DO_TURN_RIGHT
		cpi r17, turnLeft
		breq DO_TURN_LEFT
		cpi r17, doHalt
		breq DO_HALT
		cpi  r17, future_freeze
		breq DO_FUTURE
		jmp DONE

	;subroutines
	DO_BACK:
		ldi mpr, MoveBack 
		out PORTB, mpr
		mov r21, mpr
		jmp DONE
	DO_FORWARD:
		ldi mpr, MoveForward 
		out PORTB, mpr
		mov r21, mpr
		jmp DONE
	DO_TURN_RIGHT:
		ldi mpr, TurnR 
		out PORTB, mpr
		mov r21, mpr
		jmp DONE
	DO_TURN_LEFT:
		ldi mpr, TurnL 
		out PORTB, mpr
		mov r21, mpr
		jmp DONE
	DO_HALT:
		ldi mpr, Halt 
		out PORTB, mpr
		mov r21, mpr
		jmp DONE
	DO_FUTURE:
		ldi r24, $01 ;set the r24 flag since we just got the command to send the tag signal
		jmp DONE
	DONE:
	;lds mpr, UCSR1A
	;cbr mpr, RXC1
	;sts UCSR1A, mpr
	;pop
	pop r17
	pop mpr
	out SREG, mpr
	pop mpr
	ret

GOT_FROZEN: ;since we are in an interrupt vector, external interrupt should be empty
		push mpr
		ldi mpr, halt
		;out PORTB, mpr ;first thing's first: Freeze!
		;InnerFrozoneLoop:
		;	ldi waitcounter, 100
		;	rcall WAIT
			;inc mpr
			;cpi mpr, 5
			;brne InnerFrozoneLoop ;if not yet 5?
		;out PORTB, r21
		inc r22 
		pop mpr
		jmp DONE
;***********************************************************
;*	Stored Program Data
;***********************************************************



;***********************************************************
;*	Additional Program Includes
;***********************************************************

