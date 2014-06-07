TITLE Program Template			(template.asm)

; Program Description: Prog Assignment 4, Primes.
; This program calculates prime numbers. The user enters a number between 1 and 200
; and the program calculates and displays the primes up to and including the number entere.
; Results are displayed 10 primes per line, 3 spaces between each prime
; Author: Eric Rouse
; Date Created: 11/4/2012
; Last Modification Date: 11/4/2012

INCLUDE Irvine32.inc

UPPERLIMIT	EQU		<200>
LOWERLIMIT	EQU		<1>

.data
myName		BYTE	"by Eric Shawn Rouse.",0	;My full name
intro		BYTE	"Programming Assignment 4, Prime Number Generator " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE	 21 DUP(0)					;how are you called?
greeting	BYTE	"Nice to meet you, ",0		;greet the user
parting		BYTE	"Au revoir, bon voyage, ", 0	;good bye message
promptNum	BYTE	"Please enter a number from 1 to ",0	;prompt for a number
instruct	BYTE	"Enter the number of primes to display. The range is inclusive. ",0	;tell them about the fun
space		BYTE	": ",0						;space colon
undMsg		BYTE	"You entered a value less than specified. Try again: ", 0 ;let the user know what is happening next
ovrMsg		BYTE	"You entered a value greater than specified. Try again: ", 0;let the user know their value is bad
calcMsg		BYTE	"Calculating...", 0
testMsg		BYTE	"Not a Prime  ",0
spaces		BYTE	" ",0
excl		BYTE	"!",0

number		DWORD	1							;
primetest	DWORD	1							;
primedec	DWORD	1							;
savespot	DWORD	1							;
primitude	WORD	0							;


.code
main PROC

	call introduction		;introduce yourself
	call getUserData		;get the data you need
	call showPrimes			;display the primes
	call farewell			;end it all nicely

	exit		; exit to operating system
main ENDP



;-------------------------------------
introduction PROC
;Introduces the programmer to the user
; Preconditions: None
; Postconditions: None
; Recieves: Nothing
; Returns: Nothing
;--------------------------------------
	;introduce myself
	mov		edx, OFFSET intro
	call	WriteString
	mov		edx, OFFSET myName
	call	WriteString
	call	CrLf
	;ask their name
	mov		edx, OFFSET getName
	call	WriteString
	mov		ecx, SIZEOF theirName
	mov		edx, OFFSET theirName
	call	ReadString
	;greet them by name
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET theirName
	call	WriteString
	call	CrLf
	ret
introduction ENDP

;-------------------------------------
getUserData PROC
;Asks the user for a value in order to find the primes
; Preconditions: None
; Postconditions: None
; Recieves: Nothing
; Returns: Nothing
;--------------------------------------
	;basic instructions
	mov		edx, OFFSET instruct
	call	WriteString
	call	CrLf
	;prompt for a number
	mov		edx, OFFSET promptNum
	call	WriteString
	mov		eax, UPPERLIMIT
	call	WriteDec
	mov		edx, OFFSET space
	call	WriteString
	call	ReadInt
	mov		number, eax
	call	CrLf
	call	validate
	;-------------------------------------
	validate PROC
	;Checks the values from the user to determin if it is good
	; Preconditions: None
	; Postconditions: None
	; Recieves: Nothing
	; Returns: Nothing
	;--------------------------------------
		startval:
		mov		eax, number
		;compare to the lower limit
		cmp		eax, LOWERLIMIT
		jl		tooLow
		mov		eax, number
		;compare to the upper limit
		cmp		eax, UPPERLIMIT
		jg		tooHigh
		jmp		valgood
		;too low, tell the user enter another value, then validate that
		tooLow:
		mov		edx, OFFSET undMsg
		call	WriteString
		jmp		reprompt
		;too high, tell the user to enter another value, then validate that
		tooHigh:
		mov		edx, OFFSET ovrMsg
		call	WriteString
		jmp		reprompt
		;reprompt for good data
		reprompt:
		call	ReadInt
		mov		number, eax
		call	CrLf
		jmp		startval

		valgood:
		ret
	validate ENDP
	ret
getUserData ENDP

;-------------------------------------
showPrimes PROC
;Starts printing the primes to the display
; Preconditions: None
; Postconditions: None
; Recieves: Nothing
; Returns: Nothing
;--------------------------------------
	; Let the user know something is happening
	mov		edx, OFFSET calcMsg
	call	writeString
	call	CrLf
	;initialize the counter to the number the user entered
	mov ecx, number
	countLoop:
		mov		eax, ecx
		push	number
		;normalize the test value and decrement it through the loop
		pop		primetest
		sub		primetest, ecx
		mov		eax, primetest
		add		primetest, 1
		;once the appropriate test value is located, call isPrime to find out if it is a prime
		call	isPrime
		loop	countLoop
		ret
	;-------------------------------------
	isPrime PROC
	;Checks if a values is prime or not
	; Preconditions: None
	; Postconditions: None
	; Recieves: Nothing
	; Returns: Nothing
	;--------------------------------------
			mov		savespot, ecx ;save the loop position for when we jump back

			;special case, 1, is not prime
			cmp		primetest, 1
			je		notPrime
			;store the test value in a decrement value
			push	primetest
			pop		primedec
			;loop through all divisible values
			mov		ecx, primetest
			primeloop:
				dec		primedec
				cmp		primedec, 1
				je		yesPrime  ;if primedec has made it to one we have a prime number
				mov		edx, 0
				mov		eax, primetest
				div		primedec
				cmp		edx, 0
				je		notPrime  ;if the remainder is zero, we don't have a prime number
				loop	primeloop
			;YAHOO, we found a prime, print it and the appropriate spaces (based on number size)
			yesPrime:
				mov		eax, primetest
				call	writeDec
				mov		edx, OFFSET spaces
				call	writeString
				call	writeString
				call	writeString
				cmp		primetest, 100
				jge		donespaces
				call	writeString
				cmp		primetest, 10
				jge		donespaces
				call	writeString
				donespaces:
					inc		primitude
					cmp		primitude, 10
					jne		nocrlf
					mov		primitude, 0
					call	CrLf
				nocrlf:
					mov		ecx, savespot
					ret

			;found a divisible number, must move on to the next test
			notPrime:
				mov		ecx, savespot
				ret
			

	isPrime ENDP
showPrimes ENDP

;-------------------------------------
farewell PROC
;Says goodbye to the user
; Preconditions: None
; Postconditions: None
; Recieves: Nothing
; Returns: Nothing
;--------------------------------------
	call	CrLf
	call	CrLf
	mov		edx, OFFSET parting
	call	WriteString
	mov		edx, OFFSET theirName
	call	WriteString
	mov		edx, OFFSET excl
	call	WriteString
	call	CrLf
	ret
farewell ENDP

END main