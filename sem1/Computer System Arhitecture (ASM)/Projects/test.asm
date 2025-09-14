bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data ;d+[(a+b)*5-(c+c)*5]
    a db 2
    b db 3
    c db 2
    d dw 5
    ab5 dw 0
    cc5 dw 0

; our code starts here
segment code use32 class=code
    start:
        mov BL, [b]
        add [a], BL
        mov AL, 5
        mov BL, [a]
        mul BL
        mov [ab5], AX
        ; ab5 = (a+b)*5
        
        mov CL, [c]
        add CL, [c]
        mov AX, 5
        mul CL
        mov [cc5], AX
        ; cc5 = (c+c)*5
        
        mov AX, [d]
        add AX, [ab5]
        sub AX, [cc5]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
