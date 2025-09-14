bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
    ;29)
    ;   Given the doublewords A si B, obtain the quadword C as follows:
    ; 1)the bits 0-7 of C are the same as the bits 21-28 of A
    ; 2)the bits 8-15 of C are the same as the bits 23-30 of B complemented
    ; 3)the bits 16-21 of C have the value 101010
    ; 4)the bits 22-31 of C have the value 0
    ; 5)the bits 32-42 of C are the same as the bits 21-31 of B
    ; 6)the bits 43-55 of C are the same as the bits 1-13 of A
    ; 7)the bits 56-63 of C are the same as the bits 24-31 of the result A XOR 0ABh
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dd 0xA384CCC
    b dd 0x992FDD3
    C dq 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; storing the result into EDX:EAX, and will move afterwards into C
        mov EAX, 0
        mov EDX, 0
        mov EBX, [a]
        shr EBX, 21
        and EBX, 0x000000FF
        ; EBX has 00...0A(21-28 bits)
        or EAX, EBX
        ; 1) setting bits 0-7 of C to the 21-28 bits of A
        
        mov EBX, [b]
        shr EBX, 23
        neg EBX
        and EBX, 0x0000FF00
        or EAX, EBX
        ; 2) setting bits 8-15 to the 23-30 bits of B complemented
        
        or EAX, 0x002A0000
        ; 0000 0000 0010 1010b = 0x2A  for subtasks 3 and 4
        
        mov EBX, [b]
        shr EBX, 21
        and EBX, 0x000007FF
        ;saving only 11 bits, from 21-31
        and edx, ebx
        ;storing into the higher part of C 
        
        mov EBX, [a]
        shr EBX, 9
        ; putting the bits 1-13 on the possition 11-23 in order to move them into EDX
        and EBX, 0x00FFF800
        or EDX, EBX
        
        mov EBX, [a]
        xor EBX, 0xAB
        and EBX, 0xFF000000
        or EDX,EBX
        
        mov [C], EAX
        mov [C+4], EDX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
