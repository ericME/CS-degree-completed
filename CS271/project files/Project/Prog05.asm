TITLE Program Template			(template.asm)

; Program Description: This program takes as input a number of array elements. It then fills an array with
; random numbers. It then sorts that array and calculates/displays the median;
; Author: Eric Rouse
; Date Created: 11/12/2012
; Last Modification Date: 11/17/2012

INCLUDE Irvine32.inc

UPPERLIMIT	EQU		<200>
LOWERLIMIT	EQU		<10>
RANDLOW		EQU		<100>
RANDHIGH	EQU		<999>

.data

myName		BYTE	"by Eric Rouse.",0			;My full name
intro		BYTE	"Programming Assignment 5, Random integer generation and sorting. " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE	 21 DUP(0)					;how are you called?
greeting	BYTE	"Nice to meet you, ",0		;greet the user
parting		BYTE	"Stay thirsty my friend ", 0	;good bye message
promptNum	BYTE	"Please enter a number from 10 to ",0	;prompt for a number
instruct	BYTE	"Enter the number of random integers to generate. The range is inclusive. ",0	;tell them about the fun
space		BYTE	": ",0						;space colon
undMsg		BYTE	"You entered a value less than specified. Try again: ", 0 ;let the user know what is happening next
ovrMsg		BYTE	"You entered a value greater than specified. Try again: ", 0;let the user know their value is bad
calcMsg		BYTE	" random numbers are being generated...", 0
testMsg		BYTE	"Made it here ... ",0
spaces		BYTE	" ",0
excl		BYTE	"!",0
titleUnsorted		BYTE	"Unsorted Array:",0
titleSorted			BYTE	"Sorted Array:",0
titleMedian			BYTE	"The Median is:",0


number		DWORD	1							;number of elements/random numbers to generate
array		DWORD	UPPERLIMIT DUP(?)			;array to hold rands
temp		DWORD	?

.code
main PROC
	call	Randomize			;generate some randomness

	call	introduction		;introduce yourself
	
	push	OFFSET number
	call	getUserData			;get the data you need
	
	mov		edx, OFFSET calcMsg
	mov		eax, number
	call	writeDec
	call	writeString
	call	CrLf
	;put the items we need on the stack. Leave them there for everyone
	push	OFFSET array
	push	number
	
	call	fillArray			;fill the array w/random nums
	push	OFFSET titleUnsorted;title
	call	display				;display the unsorted list
	call	sortlist			;sort the recently filled array
	push	OFFSET titleSorted	;title
	call	display				;display the sorted list
	push	OFFSET titleMedian	;title
	call	dispMedian			;find and display the median value
	call	clear				;remove the items from the stack
	call	farewell			;end it all nicely

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
; Postconditions: Valid integer
; Recieves: Reference to the number location.
; Returns: Updates the number location.
;--------------------------------------
	;basic instructions
	push	ebp
	mov		ebp, esp
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
	call	CrLf

	;put the parameters in the right places
	mov		ebx, [ebp+8]	;move the address
	mov		[ebx], eax		;put the input number at the address
	push	ebx				;send the address up to validate on the stack
	;check validity of input
	call	validate
	pop		ebp
	ret		4
getUserData ENDP

;-------------------------------------
validate PROC
;Checks the values from the user to determin if it is good
; Preconditions: Integer entered
; Postconditions: Integer validated
; Recieves: Reference to the number location.
; Returns: Updates the number location.
;--------------------------------------
	push	ebp
	mov		ebp, esp
	startval:
	mov		ebx, [ebp+8]	;move the address
	mov		eax, [ebx]
	;compare to the lower limit
	cmp		eax, LOWERLIMIT
	jl		tooLow
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
	mov		ebx, [ebp+8]	;move the address
	mov		[ebx], eax		;overwrite the address with eax
	call	CrLf
	jmp		startval

	valgood:
	pop		ebp
	ret		4
validate ENDP

;-------------------------------------
fillArray PROC
;Fills an array with random numbers
; Preconditions: None
; Postconditions: None
; Recieves: number of elements, array
; Returns: array filled with random numbers
;--------------------------------------
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+8]	;number of elements to count register
	mov		edi, [ebp+12]	;address of array
	mov		ebx, 0
	
	;loop, fill the array with random numbers
	again:
		mov		eax, RANDHIGH
		sub		eax, RANDLOW
		call	randomrange
		add		eax, RANDLOW
		mov		[edi], eax
		inc		ebx
		add		edi, 4
		loop	again



	pop		ebp
	ret
fillArray ENDP

;-------------------------------------
display PROC
;prints a list of elements to the display
; Preconditions: None
; Postconditions: None
; Recieves: number of elements, array
; Returns: Nothing
;--------------------------------------
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+12]	;number of elements to count register
	mov		edi, [ebp+16]	;address of array
	mov		edx, [ebp+8]	;address of title
	call	CrLf
	call	writeString		
	call	CrLf
	mov		ebx, 0			;element counter
	mov		edx, 0			;elements per line counter

	

	;loop through the array, printing each value along the way
	again:
		mov		eax,[edi+ebx*4]	;start with first element
		inc		ebx
		call	WriteDec			;display element
		;insert some spaces
		mov		al,32
		call	WriteChar
		call	WriteChar
		inc		edx
		cmp		edx, 10
		jl		nocrlf
		mov		edx, 0
		call	CrLf
		nocrlf:
		loop	again
	
	call CrLf
	call CrLf
	pop		ebp
	ret		4
display ENDP

;-------------------------------------
dispMedian PROC
;calculates and displays the median value
; Preconditions: sorted array
; Postconditions: None
; Recieves: number of elements, sorted array
; Returns: prints 
;--------------------------------------
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+12]	;number of elements to count register
	mov		edi, [ebp+16]	;address of array
	mov		edx, [ebp+8]	;address of title
	mov		eax, edi
	call	writedec
	call	crlf
	call	CrLf
	call	writeString		
	call	CrLf
	
	;find out if the number of elements is even or odd
	mov		eax, ecx
	cdq
	mov		ebx, 2
	div		ebx
	cmp		edx, 0
	je		evenelem

	;odd number of elements, median is middle one
	mov		eax, [edi+eax*4]
	jmp		write

	;even number of elements, median is the avg of middle two
	evenelem:
	mov		ebx, [edi+eax*4-4]
	mov		eax, [edi+eax*4]
	add		eax, ebx
	cdq
	mov		ebx, 2
	div		ebx
	cmp		edx, 0
	je		write
	add		eax, 1
	
	write:
	call	WriteDec
	
	call CrLf
	call CrLf
	pop		ebp
	ret		4
dispMedian ENDP


;-------------------------------------
sortList PROC
;Sorts a list of random elements
; Preconditions: unsorted array
; Postconditions: None
; Recieves: number of elements, array
; Returns: sorted array
;--------------------------------------

	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+8]	;number of elements to count register
	sub		ecx, 1
	mov		edi, [ebp+12]	;indirect address of array
	mov		eax, ecx
	mov		esi, 0
	mov		ebx, 0

	
	master:
		again:
			mov		eax, [edi]				;get first value
			mov		edx, [edi+4]			;get next value
			cmp		eax, edx				;compare, if next is greater, swap
			jge		noswap

			mov		esi, 1					;store a "swap occured bit, we have to loop again"
			push	edi						;put the first value on the stack
			add		edi, 4					;incrememnt to next array value
			push	edi						;put the second value on the stack
			;swap the two values on the stack
			call swap
			jmp		swapped

			;swap not needed
			noswap:
			add		edi, 4
			
			swapped:
			loop again

		cmp		esi, 0
		je done
		mov		esi, 0
		mov		ecx, [ebp+8]
		mov		edi, [ebp+12]
		sub		ecx, 1
		jmp master
	done:

	pop		ebp
	
	ret
sortList ENDP

;-------------------------------------
swap PROC
;swaps two values in an array
; Preconditions: array has two elements at the locations indicated
; Postconditions: None
; Recieves: memory locations of the elements to swap
; Returns: swapped elements
;--------------------------------------
	push	ebp
	mov		ebp, esp
	push	edi				;calling routine uses edi, store current value
	push	esi				;calling routine uses esi, store current value
	mov		edi, [ebp+8]	;first element to swap
	mov		esi, [ebp+12]	;second element to swap
	mov		eax, [edi]		;get the value at edi
	mov		edx, [esi]		;get the value at esi

	;do the swapping
	mov		[edi], edx
	mov		[esi], eax

	;remove the stored esi and edi from the stack, put them back in the registers
	pop		esi
	pop		edi

	pop		ebp
	ret		8				;clear the stack, free up the memories
swap ENDP

;-------------------------------------
clear PROC
;Clears the stack remains
; Preconditions: stack has number of elements and array
; Postconditions: None
; Recieves: number of elements, array
; Returns: Nothing
;--------------------------------------
	push	ebp
	mov		ebp, esp

	pop		ebp
	ret		8		;clear the stack, free up the memories
clear ENDP


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