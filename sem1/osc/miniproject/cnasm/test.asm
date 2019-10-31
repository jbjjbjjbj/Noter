global _start

section .data
        align 2
        ; String, which is just a collection of bytes, 0xA is newline
        str:     db 'Hello, world!',0xA
        strLen:  equ $-str

section .bss

section .text
        _start:

        mov     edx, strLen     ; Arg three: the length of the string
        mov     ecx, str        ; Arg two: the address of the string
        mov     ebx, 1          ; Arg one: file descriptor, in this case stdout
        mov     eax, 4          ; Syscall number, in this case the 
        int     0x80            ; Interrupt 0x80        

		if ( hej = 10 ) {
			mov     ebx, 0          ; Arg one: the status
			mov     eax, 1          ; Syscall number:
			if(cool) {
				int     0x80
			}
		} else {
			while( lol ) {
				mov hej, 0
			}
		}
		while( lol ) {
			mov hej, 0
		}

		hej

		for(mov a, 0( a < 100( a++ ) {
			test
		}
