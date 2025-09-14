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
    a db 1
    b dw 1
    c db 2
    d db 3
    x dw 0
; our code starts here
segment code use32 class=code
    start:
        ; x = a*b/d-c, a,c,d-bytes, b - word
        mov AH, 0
        mov AL, a
        mul word[b]
        
        mov BL, [d]
        mov BH, 0
        div BX
        
        mov BL, [c]
        mov BH, 0
        add AX, BX
        
        mov [x], AX
        
        ;cbw ; AL -> AX
        ;cwd ; AX -> DX:AX
        ;cwde ; AX -> EAX
        ;cdq ; EAX -> EDX:EAX 
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
