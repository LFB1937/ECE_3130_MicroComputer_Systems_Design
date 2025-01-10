	AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 

Array1_bytes DCB 2, 3, 0xFE, 0xFF; 1. Define an array of bytes that has four elements called Array1_bytes and initialize it with 2, 3, 0xFE, and 0xFF.
Array1_Signed_Words DCD 0, 0, 0, 0 ; 2. Define an array of words that has four elements called Array1_Signed_Words and initialize it with zeros.
Array1_unsigned_Words DCD 0, 0, 0, 0 ; 3. Define an array of words that has four elements called Array1_unsigned_Words and initialize it with zeros.
Array1_Add_Words DCD 0, 0, 0, 0 ; 4. Define an array of words that has four elements called Array1_Add_Words and initialize it with zeros.
Array1_Mul_Words DCD 0, 0, 0, 0 ; 5. Define an array of words that has four elements called Array1_Mul_Words and initialize it with zeros.
Array1_Div_Words DCD 0, 0, 0, 0 ; 6. Define an array of words that has four elements called Array1_Div_Words and initialize it with zeros.


	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 
	LDR r0, =Array1_bytes ; 1. Initialize r0 to Array1_bytes
	LDR r1, =Array1_Signed_Words ; 1. Initialize r1 to Array1_Signed_Words
	LDR r2, =Array1_unsigned_Words ; 1. Initialize r2 to Array1_unsigned_Words
	LDR r3, =Array1_Add_Words ; 1. Initialize r3 to Array1_Add_Words
	LDR r4, =Array1_Mul_Words ; 1. Initialize r4 to Array1_Mul_Words
	LDR r5, =Array1_Div_Words ; 1. Initialize r5 to Array1_Div_Words
	
	; PART 1
	LDRB r6, [r0] ; 
	UXTB r6, r6 ; 2.	Extend the byte pointed by R0 using unsigned extension and store the result in R6.
	LDRB r7, [r0] ; 
	SXTB r7, r7 ; 3.	Extend the byte pointed by R0 using signed extension and store the result in R7.
	STR r6, [r2] ; 4. Store R6 in the word pointed by R2.
	STR r7, [r1] ; 5. Store R7 in the word pointed by R1.
	ADD r9, r6, r7 ; 6.	Add R6 and R7 and store the result in the word pointed by R3.
	STR r9, [r3] ; 
	MOV r9, #10 ; Moves in the immeadiate value
	MUL r8, r6, r9 ; 7.	Multiply R8 by 10 and store the result in the word pointed by R0.
	STR r8, [r4] ;
	MOV r9, #2 ; Moves the immeadiate value of 2 into r8
	UDIV r8, r6, r9 ; 8. Divide R6 by 2 using unsigned division and store the result in the word pointed by R5.
	STR r8, [r5] ; 
	
	; PART 2
	LDRB r6, [r0, #1]! ;
	UXTB r6, r6 ;
	LDRB r7, [r0,#1] ; 
	SXTB r7, r7 ;
	STR r6, [r2, #4]! ;
	STR r7, [r1, #4]! ; 
	ADD r9, r6, r7 ;
	STR r9, [r3,#4]! ; 
	MOV r9, #10 ;
	MUL r8, r6, r9 ; 
	STR r8, [r4,#4]! ;
	MOV r9, #2 ; 
	UDIV r8, r6, r9 ; 
	STR r8, [r5,#4]! ;

	; PART 3
	LDRB r6, [r0, #1]! ;
	UXTB r6, r6 ;
	LDRB r7, [r0,#1] ; 
	SXTB r7, r7 ;
	STR r6, [r2, #4]! ;
	STR r7, [r1, #4]! ; 
	ADD r9, r6, r7 ;
	STR r9, [r3,#4]! ; 
	MOV r9, #10 ;
	MUL r8, r6, r9 ; 
	STR r8, [r4,#4]! ;
	MOV r9, #2 ; 
	UDIV r8, r6, r9 ; 
	STR r8, [r5,#4]! ;
	
	; PART 4
	LDRB r6, [r0, #1]! ;
	UXTB r6, r6 ;
	LDRB r7, [r0,#1] ; 
	SXTB r7, r7 ;
	STR r6, [r2, #4]! ;
	STR r7, [r1, #4]! ; 
	ADD r9, r6, r7 ;
	STR r9, [r3,#4]! ; 
	MOV r9, #10 ;
	MUL r8, r6, r9 ; 
	STR r8, [r4,#4]! ;
	MOV r9, #2 ; 
	UDIV r8, r6, r9 ; 
	STR r8, [r5,#4]! ;
	
	
	ENDP
							
 ; if you have more functions put them here  
	
	END