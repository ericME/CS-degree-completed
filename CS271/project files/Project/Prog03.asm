TITLE Programming Assignment #3		Prog03.asm

; Program Description: Prog Assignment 3, Integer Operations
; Author: Eric Rouse
; Date Created: 10/27/2012
; Last Modification Date: 10/27/2012

INCLUDE Irvine32.inc


UPPERLIMIT	EQU		<100>
LOWERLIMIT	EQU		<0>

.data

myName		BYTE	"by Eric Shawn Rouse.",0	;My full name
intro		BYTE	"Programming Assignment 3, Integer Stuff " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE	 21 DUP(0)					;how are you called?
greeting	BYTE	"Nice to meet you, ",0		;greet the user
parting		BYTE	"Good night, good night! Parting is such sweet sorrow/That I shall say good night till it be morrow. Good bye, ", 0		;good bye message
promptNum	BYTE	"Please enter a number less than or equal to ",0	;prompt for a number
instruct	BYTE	"We are going to do some fun integer math. Input numbers as specified, input a negative number to stop the cycle.",0	;tell them about the fun
space		BYTE	": ",0						;space colon
negMsg		BYTE	"You entered a negative number, we will now calculate.", 0 ;let the user know what is happening next
ovrMsg		BYTE	"You entered a value greater than specified, it will be ignored.", 0;let the user know their value is bad
posMsg		BYTE	" is a good value, it will be added to the accumulator.",0 ;feedback for a good value
cntMsg		BYTE	"The number of accepted values you have entered is: ",0 ;
accMsg		BYTE	"The summation of the accepted values is: ", 0;
avgMsg		BYTE	"The average of the accepted values is: ", 0;
nonumMSg	BYTE	"Oops! Looks like there were not any acceptable values entered. There is nothing to calculate. We are done here.",0;
number		DWORD	1							;
accumulator	DWORD	0
counter		DWORD	0

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

;user Instructions
	;basic instructions
	mov		edx, OFFSET instruct
	call	WriteString
	call	CrLf
	;prompt for a number
	numberPrompt:
		mov		edx, OFFSET promptNum
		call	WriteString
		mov		eax, UPPERLIMIT
		call	WriteDec
		mov		edx, OFFSET space
		call	WriteString
		call	ReadInt
		mov		number, eax
		call	CrLf
		jmp numberValidate

;tests and resultant messages
;test the number
numberValidate:
	mov		eax, number
	cmp		eax, LOWERLIMIT
	jl		negativeEntered
	cmp		eax, UPPERLIMIT
	jle		positiveEntered
	jg		overmaxEntered
	;a negative value was entered, end the cycle, do the math
	negativeEntered:
		mov		edx, OFFSET negMsg
		call	WriteString
		call	CrLf
		jmp		calculate
	;a positive value below the UPPERLIMIT was entered, let the user know, keep going
	positiveEntered:
		mov		eax, number
		call	WriteDec
		mov		edx, OFFSET posMsg
		call	WriteString
		call	CrLf
		inc		counter
		mov		eax, accumulator
		add		eax, number
		mov		accumulator, eax
		jmp		numberPrompt
	;a value that is too high was entered, let the user know, keep going
	overmaxEntered:
		mov		edx, OFFSET ovrMsg
		call	WriteString
		call	CrLf
		jmp		numberPrompt

;caculations	
calculate:
	;check if any acceptable numbers were entered. If not, let the user know and end the program.
	mov		eax, counter
	cmp		eax, 0
	jle		nothingHere
	;else, do the following:
	;display the number of positive integers entered
	mov		edx, OFFSET cntMsg
	call	WriteString
	mov		eax, counter
	call	WriteDec
	call	CrLf
	;display the sum of positive integers entered
	mov		edx, OFFSET accMsg
	call	WriteString
	mov		eax, accumulator
	call	WriteDec
	call	CrLf
	;display the average of positive integers entered
	mov		edx, OFFSET avgMsg
	call	WriteString
	mov		eax, accumulator
	cdq
	mov		ebx, counter
	div		ebx
	call	WriteDec
	call	CrLf
	jmp		farewell

;no values were entered
nothingHere:
	mov		edx, OFFSET nonumMsg
	call	WriteString
	call	CrLf
	jmp		farewell

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