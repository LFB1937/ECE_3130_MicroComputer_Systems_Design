 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Number7 DCD 0x00000001 ; Define a memory word variable called Number8 and initialize it with 80.

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 
	LDR r0, =Number7 ; loads Number8 into r0
	LDR	r0, [r0] ; load the actual contents of Number8 into ro
	LSL r0, #3 ; Multiplies the number by 8 
	ADD r0, #2 ; Then adds 2 to the number
	
stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END