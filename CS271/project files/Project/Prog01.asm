TITLE Programming Assignment 1, Elementary Arithmatic			(prog01.asm)

; Program Description:
; Author:
; Date Created:
; Last Modification Date:

INCLUDE Irvine32.inc

; (insert symbol definitions here)

.data

myName	BYTE	"by Eric Shawn Rouse.",0	;My full name
intro	BYTE	"Programming Assignment 1, Elementary Arithmatic " , 0				;Program title?
prmpt1	BYTE	"Please enter a positive digit: ", 0
prmpt2	BYTE	"Please enter a second positive digit: ", 0
sign1	BYTE	" + ", 0
sign2	BYTE	" - ", 0
sign3	BYTE	" X ", 0
sign4	BYTE	" % ", 0
sign0	BYTE	" = ", 0
num1	DWORD	?						;first user entered value
num2	DWORD	?						;second user entered value
res1	DWORD	?						;summation result
res2	DWORD	?						;difference result
res3	DWORD	?						;multiplication result
res4	DWORD	?						;quotient result

msg1	BYTE	"So long and thanks for all the fish!",0	;termination message


.code
main PROC

;introduction
	mov		edx, OFFSET intro
	call	WriteString
	mov		edx, OFFSET myName
	call	WriteString
	call	CrLf
;get the data
	mov		edx, OFFSET prmpt1
	call	WriteString
	call	ReadInt
	mov		num1, eax

	mov		edx, OFFSET prmpt2
	call	WriteString
	call	ReadInt
	mov		num2, eax

;calculate the required values
	;addition
	mov		eax, num1
	add		eax, num2
	mov		res1, eax
	;subtraction
	mov		eax, num1
	sub		eax, num2
	mov		res2, eax

	;multiplication
	mov		eax, num1
	mov		ebx, num2
	mul		ebx
	mov		res3, eax

	;division
	mov		eax, num1
	mov		ebx, num2
	div		ebx
	mov		res4, eax

;display the results
	;addition
	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET sign1
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET sign0
	call	WriteString
	mov		eax, res1
	call	WriteDec
	call	CrLf

	;subtraction
	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET sign2
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET sign0
	call	WriteString
	mov		eax, res2
	call	WriteDec
	call	CrLf

	;multiplication
	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET sign3
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET sign0
	call	WriteString
	mov		eax, res3
	call	WriteDec
	call	CrLf

	;division
	mov		eax, num1
	call	WriteDec
	mov		edx, OFFSET sign4
	call	WriteString
	mov		eax, num2
	call	WriteDec
	mov		edx, OFFSET sign0
	call	WriteString
	mov		eax, res4
	call	WriteDec
	call	CrLf

;say goodbye
	mov		edx, OFFSET msg1
	call	WriteString
	call	CrLf

	exit		; exit to operating system
main ENDP

; (insert additional procedures here)

END main