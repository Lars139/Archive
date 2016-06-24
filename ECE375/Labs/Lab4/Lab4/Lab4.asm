;***********************************************************
;*
;*	Lab4
;*
;*	Enter the description of the program here
;*
;*	This is the skeleton file Lab 3 of ECE 375
;*
;***********************************************************
;*
;*	 Author: Rattanai Sawaspanich
;*	   Date: 10/20/2014
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register 
.def	rlo = r0				; Low byte of MUL result
.def	rhi = r1				; High byte of MUL result
.def	zero = r2				; Zero register, set to zero in INIT, useful for calculations
.def	A = r3					; An operand
.def	B = r4					; Another operand
.def	tmp = r24

.def	oloop = r17				; Outer Loop Counter
.def	iloop = r18				; Inner Loop Counter

.equ	addrA = $0100			; Beginning Address of Operand A data
.equ	addrB = $0102			; Beginning Address of Operand B data
.equ	LAddrP = $0104			; Beginning Address of Product Result
.equ	HAddrP = $0109			; End Address of Product Result


;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
INIT:							; The initialization routine
		; Initialize Stack Pointer
		; TODO					; Init the 2 stack pointer registers
		LDI	R16, LOW(RAMEND)	; Low Byte of End SRAM addr
		OUT SPL, R16			; write byte to SPL
		LDI R16, HIGH(RAMEND)	; same steps for high
		OUT SPH, R16
		
		clr		zero			; Set the zero register to zero, maintain
								; these semantics, meaning, don't load anything
								; to it.

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:							; The Main program

		;Note: X is a 16 bits (2 bytes) pointer. X itself has 2 bytes. The first and second byte are named XH, and XL respectively
		ldi		XL, low(addrA)	; settting the x ptr (16bits ptr) Starting from the beginning of X-reg
		ldi		XH, high(addrA)	
		
		ldi		YL, low(addrB)	; setting the y ptr. Starting from the beginning of the Y-reg
		ldi		YH, high(addrB)	
		
		;init value of first byte of x to 11. To do so, we need to do the following steps
		ldi tmp, 101		;create a temp var that has the value of 11
		st X+ , tmp		;store the value of tmp into the first byte of X (and post-increment the X pointer to point to the next step)
		ldi tmp, 101
		st X , tmp		;store the value of tmp into the first byte of X.
		ldi tmp, 101
		st -X , tmp
		

		ldi tmp, 8
		st Y+ , tmp				
		ldi tmp, 101
		st Y , tmp		
		ldi tmp, 101		
		st -Y, tmp
		
		rcall ADD16			;rcall	ADD16			; Call the add function

		ldi		XL, low(addrA)	; settting the x ptr (16bits ptr) Starting from the beginning of X-reg
		ldi		XH, high(addrA)	

		LDI ZH, high($0113)
		LDI ZL, low($0113)

		clr zero
		LD	tmp, Z+
		ST X+ , tmp
		LD	tmp, Z+
		ST X+, tmp
		LD	tmp, Z+
		ST X, tmp
	
		ldi	ZL, low($0103)
		ldi ZH, high($0103)

		clr zero
		st	Z+, zero
		st	Z+, zero
		st	Z+, zero
		st	Z+, zero
		st	Z+, zero
		

		; Multiply two 24-bit numbers
		rcall MUL24				;rcall	MUL24			; Call the multiply function

DONE:	rjmp	DONE			; Create an infinite while loop to signify the 
								; end of the program.

;***********************************************************
;*	Functions and Subroutines
;***********************************************************

;-----------------------------------------------------------
; Func: ADD16
; Desc: Adds two 16-bit numbers and generates a 24-bit number
;		where the high byte of the result contains the carry
;		out bit.
; Input: OptA ($0100); OptB($0102)
; Output: OptZ ($0113:$0114:$0115)  lower bit 
;-----------------------------------------------------------
ADD16:
		push 	A				; Save A register
		push	B				; Save B register
		push	zero			; Save zero register
		push	XH				; Save X-ptr
		push	XL
		push	YH				; Save Y-ptr
		push	YL				
		push	ZH				; Save Z-ptr
		push	ZL

		LDI	XH, high(addrA)
		LDI	XL, low(addrA)	
		LDI	YH,	high(addrB)
		LDI YL, low(addrB)
		LDI ZH, high($0113)
		LDI ZL, low($0113)

	LD A, X+ ;add the first least sig bit
	LD B, Y+
	ADD A,B
	ST Z+, A

	LD A, X ;load the num in to the A-reg
	LD B, Y
	ADC A,B ;add the second least sig bit
	ST Z+, A ;increment Z to the next bit

	clr zero ; make sure that the zero is clear
	ADC zero, zero ; zero = zero + zero + carry; this is for chekcing if there is a carry bit. The result of carry bit will be stored in zero-register
	ST Z, zero  ;move the carry bit from zero-reg to Z reg

		pop		ZL				
		pop		ZH
		pop		YL
		pop		YH
		pop		XL
		pop		XH
		pop		zero
		pop		B
		pop		A
	ret						; End a function with RET

;-----------------------------------------------------------
; Func: MUL24
; Desc: Multiplies two 24-bit numbers and generates a 48-bit 
;		result.
; Input: OptA, OptB  $0103:$0101$0100 
; Output: Result   $0108:0107:$0106:$0105:$0104
;-----------------------------------------------------------
MUL24:
		push 	A				; Save A register
		push	B				; Save B register
		push	rhi				; Save rhi register
		push	rlo				; Save rlo register
		push	zero			; Save zero register
		push	XH				; Save X-ptr
		push	XL
		push	YH				; Save Y-ptr
		push	YL				
		push	ZH				; Save Z-ptr
		push	ZL
		push	oloop			; Save counters
		push	iloop				

		clr		zero			; Maintain zero semantics

		; Set Y to beginning address of B

		LDI	YH,	high($0100)
		LDI YL, low($0100)

		; Set Z to begginning address of resulting Product
		ldi		ZL, low(LAddrP)	; setting the z ptr
		ldi		ZH, high(LAddrP)

		; Begin outer for loop
		ldi		oloop, 3		; Load counter
MUL24_OLOOP:
		; Set X to beginning address of A
		LDI	XH, high($0100) ; Load high byte
		LDI	XL, low($0100)	; Load low byte

		; Begin inner for loop
		ldi		iloop, 3		; Load counter
MUL24_ILOOP:
		ld		A, X+			; Get byte of A operand
		ld		B, Y			; Get byte of B operand
		mul		A,B				; Multiply A and B
		ld		A, Z+			; Get a result byte from memory
		ld		B, Z+			; Get the next result byte from memory
		add		rlo, A			; rlo <= rlo + A
		adc		rhi, B			; rhi <= rhi + B + carry
		ld		A, Z			; Get a third byte from the result
		adc		A, zero			; Add carry to A
		st		Z, A			; Store third byte to memory
		st		-Z, rhi			; Store second byte to memory
		st		-Z, rlo			; Store third byte to memory
		adiw	ZH:ZL, 1		; Z <= Z + 1			
		dec		iloop			; Decrement counter
		brne	MUL24_ILOOP		; Loop if iLoop != 0
		; End inner for loop

		sbiw	ZH:ZL, 2		; Z <= Z - 1
		adiw	YH:YL, 1		; Y <= Y + 1
		dec		oloop			; Decrement counter
		brne	MUL24_OLOOP		; Loop if oLoop != 0
		; End outer for loop
		 		
		pop		iloop			; Restore all registers in reverves order
		pop		oloop
		pop		ZL				
		pop		ZH
		pop		YL
		pop		YH
		pop		XL
		pop		XH
		pop		zero
		pop		rlo
		pop		rhi
		pop		B
		pop		A
		ret						; End a function with RET
		ret						; End a function with RET

;-----------------------------------------------------------
; Func: MUL16
; Desc: An example function that multiplies two 16-bit numbers
;			A - Operand A is gathered from address $0102:0101:0100
;			B - Operand B is gathered from address $0105:0104:0103
;			Res - Result is stored in address 
;					$0107:$0106:$0105:$0104
;		You will need to make sure that Res is cleared before
;		calling this function.
;-----------------------------------------------------------
MUL16:
		push 	A				; Save A register
		push	B				; Save B register
		push	rhi				; Save rhi register
		push	rlo				; Save rlo register
		push	zero			; Save zero register
		push	XH				; Save X-ptr
		push	XL
		push	YH				; Save Y-ptr
		push	YL				
		push	ZH				; Save Z-ptr
		push	ZL
		push	oloop			; Save counters
		push	iloop				

		clr		zero			; Maintain zero semantics

		; Set Y to beginning address of B

		LDI	YH,	high(addrB)
		LDI YL, low(addrB)

		; Set Z to begginning address of resulting Product
		ldi		ZL, low(LAddrP)	; setting the z ptr
		ldi		ZH, high(LAddrP)

		; Begin outer for loop
		ldi		oloop, 2		; Load counter
MUL16_OLOOP:
		; Set X to beginning address of A
		LDI	XH, high(addrA) ; Load low byte
		LDI	XL, low(addrA)	; Load high byte

		; Begin inner for loop
		ldi		iloop, 2		; Load counter
MUL16_ILOOP:
		ld		A, X+			; Get byte of A operand
		ld		B, Y			; Get byte of B operand
		mul		A,B				; Multiply A and B
		ld		A, Z+			; Get a result byte from memory
		ld		B, Z+			; Get the next result byte from memory
		add		rlo, A			; rlo <= rlo + A
		adc		rhi, B			; rhi <= rhi + B + carry
		ld		A, Z			; Get a third byte from the result
		adc		A, zero			; Add carry to A
		st		Z, A			; Store third byte to memory
		st		-Z, rhi			; Store second byte to memory
		st		-Z, rlo			; Store third byte to memory
		adiw	ZH:ZL, 1		; Z <= Z + 1			
		dec		iloop			; Decrement counter
		brne	MUL16_ILOOP		; Loop if iLoop != 0
		; End inner for loop

		sbiw	ZH:ZL, 1		; Z <= Z - 1
		adiw	YH:YL, 1		; Y <= Y + 1
		dec		oloop			; Decrement counter
		brne	MUL16_OLOOP		; Loop if oLoop != 0
		; End outer for loop
		 		
		pop		iloop			; Restore all registers in reverves order
		pop		oloop
		pop		ZL				
		pop		ZH
		pop		YL
		pop		YH
		pop		XL
		pop		XH
		pop		zero
		pop		rlo
		pop		rhi
		pop		B
		pop		A
		ret						; End a function with RET

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

; Enter any stored data you might need here

;***********************************************************
;*	Additional Program Includes
;***********************************************************
; There are no additional file includes for this program
