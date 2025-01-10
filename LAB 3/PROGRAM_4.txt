 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Array1 DCD 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC ; Initialize Array1 with 0xAAAAAAAA, 0xBBBBBBBB, and 0xCCCCCCCC 
Array2 DCD 0, 0, 0 ; initialize Array2 with zeros

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; Write a program to copy Array1 to Array2 using Post-Index addressing mode  

__main	PROC
; main function 
 LDR r0, =Array1  ; load the address of Array1 into r0
 LDR r1, =Array2  ; load the address of Array2 into r1
 LDR r2, [r0] ; load r0 into r2
 STR r2, [r1] ; store r1 into r2
 LDR r2, [r0, #4]! ; load r0 + 4 into r2 with Pre-index with update addressing
 STR r2, [r1, #4]! ; store r1 + 4 into r2 with Pre-index with update addressing
 LDR r2, [r0, #4]! ; load r0 + 4 into r2 with Pre-index with update addressing
 STR r2, [r1, #4]! ; store r1 + 4 into r2 with Pre-index with update addressing
		
stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END