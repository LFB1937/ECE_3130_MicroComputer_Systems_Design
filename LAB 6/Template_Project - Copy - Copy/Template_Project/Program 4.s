 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Array DCD -10, 14, -1, 0, 22, -7, -100, 0, -99, 77 ;

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 

			LDR r0, =Array ;
			LDR r1, [r0] ;
			MOV r2, #10 ;
			MOV r3, #0 ;
			LDR r4, #0 ;

		B LOOP
LOOP	ADD r3, r3, #1 ;
		CMP r2, r3;
		BEQ FINISHED ;
		CMP r1, #0 ;
		LDR r1, [r1, #4]! ;
		BLT INCREMENT ;
		B LOOP ;

INCREMENT ADD r4, r4, #1 ;
		B LOOP ;

FINISHED MOV r5, r4 ;


stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END
