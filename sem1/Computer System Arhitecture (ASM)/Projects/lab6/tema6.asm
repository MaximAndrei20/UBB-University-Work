bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
        ;26) A string of doublewords is given. Compute the string formed by the high bytes of the low words from the elements of the doubleword string and these bytes should be multiple of 10.
        ;Example:
        ;given the doublewords string:
        ;s DD 12345678h, 1A2B3C4Dh, FE98DC76h 
        ;obtain the string
        ;d DB 3Ch, DCh.
    s dd 0x12345678, 0x1A2B3C4D, 0xFE98DC76
    lens equ ($-s)/4
    d times lens db 0
    copy db 0
    ten db 10
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, lens
        mov ESI, s
        mov EDI, d
        itterate:
        lodsd
        ;making a copy
        mov [copy], AH
        ;in order to check if AL is divisible by 10 we will divide AX = 00AL with 10 and check if AH(the modulo) is 0
        mov AL, AH
        mov AH, 0
        div byte[ten]
        cmp AH, 0
        
        jne notdivisible
        mov AL, [copy]
        stosb
        
        notdivisible:
        loop itterate
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
