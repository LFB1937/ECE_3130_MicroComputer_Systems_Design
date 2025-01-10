 AREA   myData1, DATA, READWRITE  ; your variables and arrays are defined here 
sum DCD 0             ; Allocate one word for sum

	AREA    main, CODE, READONLY		
	EXPORT	__main				; make __main visible to linker
	ENTRY			

; your code is written here  

__main	PROC
; main function 
 MOVS r1,#0xFFFFFF25 ; r1= 0xFFFFFF25
 ADDS r1, r1,#0x34   ; r1=r1+0x00000034
 ADDS r1, r1,#0x11   ; r1=r1+0x00000011
 ADDS r1, r1,#18    ; r1=r1+0x00000012
 ADDS r1, r1,#2_00011100 ; r1=r1+0x0000001C
 ;ADDS r1, r1,#0xFF  ; run with and without this line
 
 LDR r0,=sum  ; r0=the address of sum 
 STR r1,[r0]  ; sum=r1
		
stop 	B 		stop     		; dead loop & program hangs here
	ENDP
							
 ; if you have more functions put them here  
	
	END