	AREA    myData, DATA, READWRITE
Array1 DCD 0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC
Array2 DCD 0,0,0
	
	
	AREA main_asm, CODE, READONLY
	GLOBAL __main_asm	
	EXPORT __main_asm
	ENTRY
__main_asm PROC
 


 ; enable GPIOA 
 LDR R0, =0x4002102C 
 LDR R1, [R0]
 LDR R2, =1
 ORRS R1, R1, R2
 STR R1, [R0]
 
 
 LDR R0,=0x50000000
 LDR R1,[R0]
 LDR R2,=0x03
 LSLS R2,R2, #24 
 BICS R1, R1, R2
 LDR R2,=0x01
 LSLS R2, R2, #24
 ORRS R1, R1, R2
 STR R1,[R0]



loop

 LDR R0,=0x50000014
 LDR R1,[R0]
 LDR R2, =1
 LSLS R2, R2, #12
 ORRS R1, R1, R2
 STR R1,[R0]

 BL delay
 
 LDR R0,=0x50000014
 LDR R1,[R0]
 LDR R2, =1
 LSLS R2, R2, #12
 BICS R1, R1, R2
 STR R1,[R0]
 
  BL delay
 
 b loop

 
	endp
		
delay PROC
	LDR R0,=0
	LDR R1,=300000
_begin	cmp R0,R1
	BEQ _exit
	ADDS R0,R0,#1
	
	B _begin
_exit	BX LR
endp	
		
	end