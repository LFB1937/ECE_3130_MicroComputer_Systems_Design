 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
Number1 DCD 0xFFF00F00, 0x00000000, 0xFFFFFFFF,	0xF0000000

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 

		LDR r0, =Number1 ;
		MOVS r1, #32 ;
		MOVS r2, #0 ;
		LDR r3, [r0] ; 

		B CHECK

CHECK CMP r1, #0 ; 
	  BEQ STOP ;
	  LSRS r3, #1 ;
	  BCC NEXT ;
	  ADD r2, r2, #1 ;
NEXT  SUB r1, #1 ; 
	  
	  B CHECK ;
	  

STOP 	B 		STOP     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END