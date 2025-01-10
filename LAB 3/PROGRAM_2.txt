 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Array1 DCD 0, 0, 0 ; Define an array with three elements called Array1. Each element is a word. Initialize the elements with zeros. 

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 
 LDR r0, =Array1 ; load the beginning address of the array (the base address) in r0 
 MOVS r1, #0xAAAAAAAA  ; Copy 0xAAAAAAAA in r1
 STR r1, [r0] ; store r0 in r1
 MOVS r1, #0xBBBBBBBB ; Copy 0xBBBBBBBB in r1
 MOVS r2, #4 ; copys 4 into r2 
 STR r1, [r0, r2] ; store the value of r2 + r0 in r1
 MOVS r1, #0xCCCCCCCC ; Copy 0xCCCCCCCC in r1
 STR r1, [r0, r2, LSL #1] ;  store the value of r2 + r0 left shifted by 1 bit in r1
		
stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END