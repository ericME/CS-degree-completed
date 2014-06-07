TITLE Program 6a			(prog6a.asm)

; Program Description:This program will get 10 valid integers from the user,
; store the numeric values in an array then display the integers, their sum, and their average.
; Author: Eric Rouse
; Date Created: 12/1/2012
; Last Modification Date: 12/1/2012

INCLUDE Irvine32.inc

UPPERLIMIT	EQU		<99>
LOWERLIMIT	EQU		<0>
RANDLOW		EQU		<100>
RANDHIGH	EQU		<999>

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
x	DWORD 3
y	DWORD 3
matrix        DWORD    10 DUP(8 DUP(?))
myName		BYTE	"by Eric Rouse.",0			;My full name
intro		BYTE	"Programming Assignment 6a, Macros and String to int conversion. " , 0				;Program title?
getName		BYTE	"What is your name? ",0		;I want to know their name too
theirName	BYTE	21 DUP(0)					;how are you called?
theirNum	BYTE	32 DUP(0)					;their number input
strNum		BYTE	32 DUP(0)					;number converted to string
greeting	BYTE	"Nice to meet you, ",0		;greet the user
parting		BYTE	"It's over for you, ", 0	;good bye message
promptNum	BYTE	"Please enter a positive number up to 99",0	;prompt for a number
instruct	BYTE	"This program will get 10 valid integers from you, store the numeric values in an array then display the integers, their sum, and their average.  ",0	;tell them about the fun
space		BYTE	": ",0						;space colon
undMsg		BYTE	"You entered a value less than specified. Try again: ", 0 ;let the user know what is happening next
ovrMsg		BYTE	"You entered a value greater than specified.", 0;let the user know their value is bad
errMsg		BYTE	"You entered a non-integer value. ", 0;let the user know their value is bad
calcMsg		BYTE	" random numbers are being generated...", 0
testMsg		BYTE	"Made it here ... ",0
spaces		BYTE	" ",0
excl		BYTE	"!",0

titleArray			BYTE	"The Entered Array:",0
titleMedian			BYTE	"The Median is:",0
titleSumm			BYTE	"The Summation is:",0

number		DWORD	0							;their integer converted
array		DWORD	20 DUP(0)					;array to hold user inputs
radix		DWORD	?							;number of radices found
temp		DWORD	?
str1		BYTE	"Last quiz!!",0

.code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
main PROC
	call	introduction		;introduce yourself
	displayString		OFFSET instruct
	call crlf


	push	OFFSET array
	push	10
	call	fillArray			;fill the array w/input

	push	OFFSET	array
	push	10
	push	OFFSET titleArray	;title
	call	display

	push	OFFSET	array
	push	10
	call	sortlist			;sort the recently filled array
	push	OFFSET titleMedian	;title
	call	dispMedian			;find and display the median value

	push	OFFSET	array
	push	15
	push	OFFSET titleSumm	;title
	call	dispSum				;find and display the median value
	
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
	cmp		number, UPPERLIMIT
	jle		valid
	displayString OFFSET ovrMsg
	jmp		main_thread

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
	ret		8

writeVal ENDP
;-------------------------------------
dispSum PROC
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
	mov		ebx, 0

	displayString edx
	mov		edx, 0		

	
;loop through the array, printing each value along the way
	again:
		mov		eax,[edi+ebx*4]	;start with first element
		inc		ebx
		add		edx, eax
		loop	again
	
	mov		eax, edx
	write:
	call	WriteDec
	
	call CrLf
	call CrLf
	pop		ebp
	ret		12
dispSum ENDP

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

	displayString edx		

	
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
	ret		12
dispMedian ENDP

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
	ret		12
display ENDP

;-------------------------------------
fillArray PROC
;Fills an array with user input numbers
; Preconditions: None
; Postconditions: None
; Recieves: number of elements, array
; Returns: array filled with random numbers
;--------------------------------------
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+8]	;number of elements to count register
	mov		edi, [ebp+12]	;address of array
	add		ecx, 2

	;loop, fill the array
	again:
		cmp		ecx, 2
		jle		lpr
		call	readVal
		mov		[edi], eax
		add		edi, 4
		lpr:
		loop	again



	pop		ebp
	ret		8
fillArray ENDP
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

END main