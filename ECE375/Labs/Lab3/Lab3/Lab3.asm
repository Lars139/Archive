/*
 * Lab3.asm
 *
 *  Created: 10/13/2014 12:12:46 PM
 *   Author: sawaspar
 */ 


 ;***********************************************************
;*
;*	Lab3
;*	Output: 1st line LCD, my name
;*			2nd line LCD, "Hello World"
;*	This is the skeleton file Lab 3 of ECE 375
;***********************************************************
;*	 Author: Rattanai Sawaspanich
;*	   Date: 10/13/2014
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register required for LCD Driver
.def	ReadCnt = r23			; Counter used to read data from Program Memory
.def	counter = r4			; Counter used for Bin2ASCII demo
.def	val = r5				; Value to be compared with
.def	TimerCnt = r6			; Counter used for the timer

.equ	CountAddr = $0130		; Address of ASCII counter text
;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp INIT				; Reset interrupt

.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
.org	$0046					; Origin of the Program, after IVs
INIT:							; Initialize Stack Pointer
		ldi		mpr, HIGH(RAMEND)
		out		SPH, mpr
		ldi		mpr, LOW(RAMEND)
		out		SPL, mpr

;		ldi		mpr, 170
;		ldi		XL, 10
;;		ldi		XH, 01
;		rcall   Bin2ASCII

		rcall	LCDInit			; INITIALIZE THE LCD DISPLAY



		; Write initial LCD line 1
		ldi		ZL, low(TXT0<<1); Init variable registers
		ldi		ZH, high(TXT0<<1)
		ldi		YL, low(LCDLn1Addr)
		ldi		YH, high(LCDLn1Addr)
		ldi		ReadCnt, LCDMaxCnt



INIT_LINE1:
		lpm		mpr, Z+			; Read Program memory
		st		Y+, mpr			; Store into memory
		dec		ReadCnt			; Decrement Read Counter
		brne	INIT_LINE1		; Continue untill all data is read
		rcall	LCDWrLn1		; WRITE LINE 1 DATA

		


		; Initialize LCD Display
		;*rcall LCDInit;						; An RCALL statement

		; Move strings from Program Memory to Data Memory
		;*rcall INIT_LINE1;
								; A while loop will go here

		; NOTE that there is no RET or RJMP from INIT, this is
		; because the next instruction executed is the first for
		; the main program

TXT0:
.DB "Rattanai Sawaspa"

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:							; The Main program
		; Display the strings on the LCD Display


WriteText:
				; CLEAR LINE 2 OF LCD
								; LOAD THE LCD MAX LINE COUNT (16)
		
								; LOAD THE Y POINTER WITH THE DATA
								; ADDRESS FOR LINE 2 DATA
		
;***********************************************************
;*	Functions and Subroutines
;***********************************************************

;-----------------------------------------------------------
; Func: Template function header
; Desc: Cut and paste this and fill in the info at the 
;		beginning of your functions
;-----------------------------------------------------------
FUNC:							; Begin a function with a label
		; Save variable by pushing them to the stack

		; Execute the function here
		
		; Restore variable by popping them from the stack in reverse order\
		ret						; End a function with RET


;***********************************************************
;*	Stored Program Data
;***********************************************************

;----------------------------------------------------------
; An example of storing a string, note the preceeding and
; appending labels, these help to access the data
;----------------------------------------------------------

;***********************************************************
;*	Additional Program Includes
;***********************************************************

.include "LCDDriver.asm"		; Include the LCD Driver



