TITLE Program 6b			(prog6b.asm)

; Program Description:This program will get randomly generate two numbers,
; ask the user to calculate their combination and compare the users answer with the actual compnination.
; at that point, it will tell them if they are right or wrong.
; Author: Eric Rouse
; Date Created: 12/1/2012
; Last Modification Date: 12/1/2012

INCLUDE Irvine32.inc

UPPERLIMIT	EQU		<4000000000>
LOWERLIMIT	EQU		<0>
N_LOW		EQU		<3>
N_HIGH		EQU		<12>
R_LOW		EQU		<1>
R_HIGH		EQU		<12>

;getString Macro
;requires address of a message to "write"
;and the address of a "number" to store
getString		MACRO	write,	number
	push	edx				;Save edx register
	
	mov	edx, write
	call	WriteString
	call	CrLf
	mov	edx, number
	mov	ecx, 32
	call	ReadString
	
	pop	edx				;Restore edx
ENDM


;dispalyString Macro
;requires address of a message to "write"
displayString	MACRO	write
	push	edx				;Save edx register
	mov		edx, write
	call	WriteString
	call	CrLf
	

	pop	edx				;Restore edx
ENDM

.data
myName		BYTE	"by Eric Rouse.",0			;My full name
intro		BYTE	"Programming Assignment 6b, Recursion and str to int conversion. " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE	21 DUP(0)					;how are you called?
theirNum	BYTE	32 DUP(0)					;their number input
strNum		BYTE	32 DUP(0)					;number converted to string
greeting	BYTE	"Nice to meet you, ",0		;greet the user
parting		BYTE	"It's over for you, ", 0	;good bye message
promptNum	BYTE	"Please enter your answer",0	;prompt for a number
instruct	BYTE	"This program will generate a combination problem for you to solve, then tell you if you are correct or not.  ",0	;tell them about the fun
space		BYTE	": ",0						;space colon
undMsg		BYTE	"You entered a value less than specified. Try again: ", 0 ;let the user know what is happening next
ovrMsg		BYTE	"You entered a value greater than specified.", 0;let the user know their value is bad
errMsg		BYTE	"You entered a non-integer value. ", 0;let the user know their value is bad
calcMsg		BYTE	" random numbers are being generated...", 0
testMsg		BYTE	"Made it here ... ",0
spaces		BYTE	" ",0
excl		BYTE	"!",0

anotProb			BYTE	"Would you like another? For yes, press y, otherwise any other key for no.",0
anotAns				BYTE	3 DUP(0)
posAns				BYTE	"y",0
fake				BYTE	" ",0
probLine1			BYTE	"  number of elements in the set.", 0
probLine2			BYTE	"  number of elements to choose from the set.", 0
probLine3			BYTE	"How many ways do you choose? ", 0

p1					BYTE "There are: ", 0
p2					BYTE " combinations of: ", 0
p3					BYTE " items froma set of : ", 0
p4					BYTE ". Your answer: ", 0

correctAns			BYTE	"You are right!", 0
notcorrAns			BYTE	"Bad news, not the right answer.", 0

number		DWORD	0							;their integer converted
radix		DWORD	?							;number of radices found
temp		DWORD	?
answer		DWORD	?							;their answer
result		DWORD	1234							;the correct result

n_val		DWORD	N_LOW						;n value
r_val		DWORD	R_LOW						;r value

.code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
main PROC
	call	Randomize			;generate some randomness
	call	introduction		;introduce yourself
	another:
	push	OFFSET n_val
	push	OFFSET r_val
	call	showProblem			;show them the problem
	
	push	OFFSET	answer
	call	getData				;ask for the answer
	
	push	OFFSET result
	push	r_val
	push	n_val
	call	combinations		;do the calculation
	
	push	result
	push	answer
	push	r_val
	push	n_val
	call	showResults			;let them know how they did
	

	getString		OFFSET	anotProb, OFFSET	anotAns
	
	;see if they want another go.
	mov		esi, OFFSET anotAns
	mov		edi, OFFSET posAns
	cmpsb
	je		another
	;else, end it
	call	farewell			;end it all nicely

	exit		; exit to operating system
main ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
	displayString		OFFSET instruct
	call crlf
	ret
introduction ENDP

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

;-------------------------------------
readVal PROC
;Asks the user for a value, converts from string to int and validates it
; Preconditions: None
; Postconditions: Valid integer
; Recieves: Reference to the number location.
; Returns: Updates the number location.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	pushad
	
	main_thread:
	;prompt for a number
	getString		OFFSET promptNum,	OFFSET theirNum
	cld
	mov		esi, OFFSET theirNum
	mov		ecx, LENGTHOF theirNum
	mov		radix, -1
	mov		number, 0


	;convert to a number
	l1:	lodsb

		;check that the byte is between 48 and 57, the decimal ASCII range for ints
		cmp al, 48
		jl	error
		cmp al, 57
		jg	error
		inc	radix
		jmp	l2
		error:
		;check if we are at a null char, or the end of the input string
		cmp al, 0
		je	l_end
		;else, we have a bad input, let the user know
		displayString	OFFSET errMsg
		jmp main_thread
		l2:
		loop l1
	l_end:

	;take the string with a number in it an convert it to an integer
	cld
	mov		esi, OFFSET theirNum
	mov		ecx, LENGTHOF theirNum
	
	li1: lodsb
		;check if we are at a null char, or the end of the input string
		cmp		al, 0
		je		li_end
		;else subtract 48 to get from string bytes to integers
		sub		al, 48
		cbw
		cwd
		
		push	eax
		push	ecx

		;find and multiply the value by its radix
		mov		ebx, 1
		cmp		radix, 0
		je		li3
		jl		li_end
		mov		ecx, radix
		
		li2:	mov	eax, 10
				mul	ebx
				mov	ebx, eax
				loop li2

		li3:
		dec		radix
		pop		ecx
		pop		eax
		mul		ebx
		
		add		number, eax
		loop li1
	li_end:

	;check validity of output
	;cmp		number, UPPERLIMIT
	;jle		valid
	;displayString OFFSET ovrMsg
	;jmp		main_thread

	valid:
	popad
	mov		eax, number
	pop		ebp
	ret		

readVal ENDP


;-------------------------------------
writeVal PROC
;converts numeric value to string
; Preconditions: two digit positive integer
; Postconditions: Valid integer
; Recieves: Memory location of number to conver, memory location of string to store and size of number.
; Returns: Updates the number location.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp



	;take the string with a number in it an convert it to an integer
	cld
	mov		esi, eax
	mov		ecx, 32
	mov		edi, OFFSET strNum
	
	li1: lodsb
		cbw
		mov		bl, 10
		div		bl
		cmp		al, 0
		jle		no_tens
		add		al, 48
		stosb
		inc ecx
		no_tens:
		cmp		ah, 0
		jle		li_end
		mov		al, ah
		add		al, 48
		stosb
		
		loop li1
	li_end:

	displayString	OFFSET	strNum
	
	pop		ebp
	ret

writeVal ENDP

;-------------------------------------
showProblem PROC
;converts numeric value to string
; Preconditions: addresses of n and r are not null
; Postconditions: Valid randomly generated problem
; Recieves: Memory location of n and r values.
; Returns: Updates the n and r values, displays problem.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	mov		ebx, [ebp+8]	;address of r value
	mov		ecx, [ebp+12]	;address of n value

	;generate n_val
	mov		eax, N_HIGH
	sub		eax, N_LOW
	call	randomrange
	add		eax, N_LOW
	mov		[ecx], eax

	;generate r_val
	mov		eax, [ecx]
	sub		eax, R_LOW
	call	randomrange
	add		eax, R_LOW
	mov		[ebx], eax

	;display the problem
	mov		eax, [ecx]
	call	WriteDec
	displayString OFFSET probLine1
	mov		eax, [ebx]
	call	WriteDec
	displayString OFFSET probLine2
	
	pop		ebp
	ret		8

showProblem ENDP

;-------------------------------------
getData PROC
;asks user for answer, converts from string to int
; Preconditions: None
; Postconditions: Valid integer
; Recieves: Memory location of answer to store.
; Returns: Updates the number location.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	mov		ebx, [ebp+8]	;address of answer

	call	readVal
	mov		[ebx], eax
	pop		ebp
	ret		4

getData ENDP

;-------------------------------------
combinations PROC
;does teh combination calcultions
; Preconditions: two digit positive integer
; Postconditions: Valid integer
; Recieves: Memory location of number to conver, memory location of string to store and size of number.
; Returns: Updates the number location.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	mov		esi, [ebp+8]	;n value
	mov		ecx, [ebp+12]	;r value
	mov		edi, esi
	sub		edi, ecx		;n-r value

	push	esi
	call	factorial
	mov		esi, eax		;n!

	push	ecx
	call	factorial
	mov		ecx, eax		;r!

	push	edi
	call	factorial
	mov		edi, eax		;(n-r)!
	
	mul		ecx				;r!*(n-r)!
	mov		ecx, eax

	mov		eax, esi
	cdq
	div		ecx				;n!/r!*(n-r)!
	
	mov		edx, [ebp+16]	;result address
	mov		[edx], eax
	
	pop		ebp
	ret		12

combinations ENDP

;-------------------------------------
showResults PROC
;shows the results
; Preconditions: calculations are done
; Postconditions: output message
; Recieves: memory location of n, r, answer and result
; Returns: message
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	mov		esi, [ebp+8]		;n value
	mov		ebx, [ebp+12]		;r value
	mov		ecx, [ebp+16]		;answer
	mov		edi, [ebp+20]		;result

	mov	edx, OFFSET p1
	call	WriteString
	mov	eax, edi
	call	WriteDec
	mov	edx, OFFSET p2
	call	WriteString
	mov	eax, ebx
	call	WriteDec
	mov	edx, OFFSET p3
	call	WriteString
	mov	eax, esi
	call	WriteDec
	mov	edx, OFFSET p4
	call	WriteString
	mov eax, ecx
	call	WriteDec
	call	CrLf

	cmp		ecx,edi
	jne		fail
	displayString	OFFSET correctAns
	jmp		the_end
	fail:
	displayString	OFFSET notcorrAns
	the_end:
	pop		ebp
	ret		16

showResults ENDP

;-------------------------------------
factorial PROC
;converts numeric value to string
; Preconditions: two digit positive integer
; Postconditions: Valid integer
; Recieves: Memory location of number to factorialize
; Returns: eax with result
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
	mov		eax, [ebp+8]	;factorial value

	cmp		eax, 0
	ja		L1
	mov		eax, 1
	jmp		L2

	L1:	dec eax
		push eax
		call factorial

	ReturnFact:
		mov	ebx, [ebp+8]
		mul	ebx

	L2:
	pop		ebp
	ret		4

factorial ENDP

END main