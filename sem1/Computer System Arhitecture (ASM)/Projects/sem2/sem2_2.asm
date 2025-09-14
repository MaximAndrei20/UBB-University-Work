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
    a db 0
    b dw 0
    c db 0
    d db 0
; our code starts here
segment code use32 class=code
    start:
        mov AL, [a]
        cbw ;AX=a
        imul word[b] ;DX:AX = a*b
        mov BX,AX
        mov AL, [d]
        cbw;AX=d
        mov CX,AX
        mov AX,BX
        idiv CX
        mov BX,AX
        mov AL, [c]
        cbw
        sub BX,AX
        mov [x], BX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
