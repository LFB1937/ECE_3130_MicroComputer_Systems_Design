	AREA    main, CODE, READONLY
	EXPORT	__main	; make __main visible to linker
	ENTRY			
				
__main	PROC		
  ldr r0,=Scores ; r0= the begining address of Scores 
  ldr r0,=Miles ; r0= the begining address of Miles
  ldr r0,=Speed ; r0= the begining address of Speed
  ldr r0,=Half_Word_Array ; r0= the begining address of Half_Word_Array
  ldr r0,=MSG1 ; r0= the begining address of MSG1
  ldr r0,=Searchfor ; r0= the begining address of Searchfor
  ldr r0,=Volt ; r0= the begining address of Volt 
  ldr r0,=Byte_Array ; r0= the begining address of Byte_Array
  ldr r0,=Zero_Array  ; r0= the begining address of Zero_Array 
  ldr r0,=Ones_Array ; r0= the begining address of Ones_Array
  
stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			
	AREA    myData, DATA, READWRITE
Scores DCD 0XAABBCCDD, 370 ; Define an array of two words called Scores - initialize it with 0XAABBCCDD and 370
Miles DCD 0xBBBBBBBB ; Define a word variable called Miles - initialize it with 0xBBBBBBBB
Speed DCW 0xAABB ; Define a half word variable called Speed  - initialize it with 0xAABB
Half_Word_Array DCW 0x00FF, 20000 ; Define an array of two half words called Half_Word_Array  - initialize it with 0x00FF and 20000
MSG1 DCB "Enter 4 Digit PIN?" ,0; Define a message (an array of characters) called MSG1  - the message is "Enter 4 Digit PIN?" add Null delimiter at the end 
Searchfor DCB '@'; Define a character variable (a byte variable that stores a character) called Searchfor  - Initialize it with @
Volt DCB 120 ; Define a byte variable called Volt   - Initialize it with 120
Byte_Array DCB -1,0xA2, 2_11110000 ; Define an array of bytes called Byte_Array   - Initialize it with -1,0xA2, and 2_11110000 
Zero_Array SPACE 8; Store zeros in 8 bytes - call this array Zero_Array
Ones_Array FILL 10,0xFF,1; Store 0xFF in 10 bytes - call this Ones_Array

	END
