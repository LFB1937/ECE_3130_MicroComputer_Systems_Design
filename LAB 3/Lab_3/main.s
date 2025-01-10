 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Number1 DCD #0xAAAAAAAA ; Define a word variable called Number1 and initialize it with 0xAAAAAAAA
Number2 DCD #0xBBBBBBBB ; Define a word variable called Number2 and initialize it with 0xBBBBBBBB

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 
 LDR r0, =Number1 ; Store the address of Number1 in r0 
 LDR r1, [r0] ; store the word at this address in r1 
 LDR r0, =Number2 ; Store the address of Number2 in r0 
 LDR r2, [r0] ; store the word at this address in r2 
 STR r1, [r0] ; Store r1 in the address pointed by r0
 LDR r0, =Number2 ; Store the address of Number1 in r0
 STR r2, [r0]	; Store r2 at this address pointed by r0 
		
stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END