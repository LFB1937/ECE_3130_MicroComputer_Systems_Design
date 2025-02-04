 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Array DCD 200, -14, 0, 0, 22, 0, -100, 0, -80, -180 ;

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 

			LDR r0, =Array ; loads in the  Array into r0
			LDR r1, [r0] ; loads the actual memory contents into r1
			MOV r2, #10 ; moves 10 into r2
			MOV r3, #0 ; moves 0 into r3
			MOV r4, #0 ; loads 0 into r4

		B LOOP
LOOP	ADD r3, r3, #1 ; add 1 to r3
		CMP r2, r3; compares r2 with r3
		BEQ FINISHED ; branch to finished if equal
		CMP r1, #0 ; checks to see if there is nothing in r1
		LDR r1, [r0, #4]! ; continue loading in words in the array
		BLT INCREMENT ; branch to increment if less than
		B LOOP ; continues looping

INCREMENT ADD r4, r4, #1 ; increments r4 by 1
		B LOOP ;

FINISHED MOV r5, r4 ; moves the final result into r5


stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END
