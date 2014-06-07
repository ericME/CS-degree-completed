TITLE Program Template			(template.asm)

; Program Description: Prog Assignment 2, Fibonacci Numbers
; Author: Eric Rouse
; Date Created: 10/14/2012
; Last Modification Date: 10/14/2012

INCLUDE Irvine32.inc


UPPERLIMIT	EQU		<46>
LOWERLIMIT	EQU		<1>

.data

myName		BYTE	"by Eric Shawn Rouse.",0	;My full name
intro		BYTE	"Programming Assignment 2, Fibonacci Numbers " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE 21 DUP(0)						;how are you called?
greeting	BYTE	"Nice to meet you, ",0		;greet the user
tellFibs	BYTE	"This program generates Fibonacci numbers. ", 0
getFibs		BYTE	"How many fibonacci numbers would you like to see? (between 1 and 46) ",0
parting		BYTE	"See you later, ", 0		;good bye message
spaces		BYTE	"      ",0					; six spaces
sizeError	BYTE	"The value you entered was not between 1 and 46 inclusive. Try again.",0
numFibs		DWORD	?
fib1		DWORD	1							;first fib number
fib2		DWORD	1							;second fib number
ctr			DWORD	0							;loop counter
count		DWORD	0							;fake looper
temp		DWORD	0							;temp variable


.code
main PROC

;introduction
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
;userInstructions
	;tell them about fibs
	mov		edx, OFFSET tellFibs
	call	WriteString
	call	CrLf

getUserData:
	;grab the desired amount of fibs to display
	mov		edx, OFFSET getFibs
	call	WriteString
	call	ReadInt
	mov		numFibs, eax
	;test the input value to make sure it is within range (1-46)
	mov		eax, numFibs
	cmp		eax, UPPERLIMIT
	jg		error
	cmp		eax, LOWERLIMIT
	jl		error
	jmp		displayFibsInit

	;error message to print if the number is outside the range
	error:
		mov edx, OFFSET sizeError
		call	WriteString
		call	CrLf
		jmp		getUserData

;the main display loop, iterates through generating the number of fibs requested and prints them
displayFibsInit:
	mov ecx, numFibs

displayFibs:
		;loop operation, increment the counter,
	;if ctr > numFibs, stop looping
	;must check before each fib
	inc		ctr
	
	;print the first fibonacci number
	mov		eax, fib1
	call	WriteDec
	mov		edx, OFFSET spaces
	call	WriteString


	;find the next fib1
	mov		eax, temp
	add		eax, fib1
	mov		ebx, fib1
	mov		temp, ebx
	mov		fib1, eax

	;do a carriage return/linefeed after every 5 values
	mov		eax, ctr
	cdq
	mov		ebx, 5
	div		ebx
	cmp		edx, 0
	je		carriagereturn
	jmp		looper
		
	carriagereturn:
		call	CrLf
	
	;if we made it this far, time to loop again!
	looper:
	loop	displayFibs



;friendly exit message to the user
farewell:
	call	CrLf
	call	CrLf
	mov		edx, OFFSET parting
	call	WriteString
	mov		edx, OFFSET theirName
	call	WriteString
	call	CrLf

	exit		; exit to operating system
main ENDP

; (insert additional procedures here)

END main