bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data ;[(a-b)*5+d]-2*c
    a db 7
    b db 3
    c db 2
    d db 8
    ab5 dw 0
    
; our code starts here
segment code use32 class=code
    start:
        mov AL, [a]
        sub AL, [b]
        mov BL, 5
        mul BL
        mov [ab5], AX
        ; ab5 = (a-b)*5
        
        mov AL, 2
        mov BL, [c]
        mul BL
        mov BX, AX
        ; BX = 2*c
        
        mov CX, [ab5]
        add CX, [d]

        sub CX, BX
        
        ; TEMA [100-10*a+4*(b+c)]-d   !!! 25)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
