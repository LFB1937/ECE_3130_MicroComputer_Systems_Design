 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Passwords_1 DCD 345676, 87654, 902345, 290657, 0x00000000 ;
Passwords_2 DCD 1234, 34567, 345676, 87654, 902345, 56784, 0x00000000 ;
input_password DCD 290657 ;

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 

		LDR r0, =Passwords_1 ;
		LDR r1, =Passwords_2 ;
		LDR r2, =input_password ;

		LDR r3, [r0] ;
		LDR r5, [r1] ;
		LDR r6, [r2] ;
		
CHECK 	CMP r3, r6 ;
		BEQ DONE ;
		CMP r3, #0 ;
		BEQ NEXT ;
		LDR r3, [r0, #4]! ; 
		B CHECK ;
		
DONE MOV r4, #0xFFFFFFFF ;
		B NEXT ;
		
NEXT	CMP r5, r6 ;
		BEQ FINISHED ;
		CMP r5, #0 ;
		BEQ FAILED ;
		LDR r5, [r1, #4]! ; 
		B NEXT ;

FINISHED MOV r4, #0xFFFFFFFF ;
		B STOP ;

FAILED MOV r4, #0x0 ;
		B STOP ;


STOP 	B 		STOP     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END