 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
NUMBERS DCD 0x000000F0,	0x00000000,	0xFFFFFFFF,	0xF0000A00

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 

	; Part 1
	MOV r0, #0x000000F0 ;  
	MOV r2, #0x00000010 ; 
	AND r0, r0, r2 ; 
	CMP r0, r2 ; 
	MOVEQ r1, #0xFFFFFFFF ; 
	MOVNE r1, #0x00000000 ; 

	; Part 2
	MOV r0, #0x00000000 ;  
	AND r0, r0, r2 ; 
	CMP r0, r2 ; 
	MOVEQ r1, #0xFFFFFFFF ; 
	MOVNE r1, #0x00000000 ; 
	
	; Part 3	
	MOV r0, #0xFFFFFFFF ;  
	AND r0, r0, r2 ; 
	CMP r0, r2 ; 
	MOVEQ r1, #0xFFFFFFFF ; 
	MOVNE r1, #0x00000000 ; 
	
	; Part 4
	LDR r0, =0xF0000A00 ;  
	AND r0, r0, r2 ; 
	CMP r0, r2 ; 
	MOVEQ r1, #0xFFFFFFFF ; 
	MOVNE r1, #0x00000000 ; 

stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END