bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 6
    b db 2
    c db 3
    d dw 10
    a10 dw 0
    bc4 dw 0
    
    

; our code starts here
segment code use32 class=code
    start:
        ; 25) [100-10*a+4*(b+c)]-d   
        
        mov AL, 10
        mov BL, [a]
        mul BL
        mov [a10], AX
        ; a10 = a*10
        
        mov BL, [b]
        add BL, [c] ; BL = b+c
        mov AL, 4
        mul BL
        mov [bc4], AX
        ; bc4 = 4*(b+c)
        
        mov AX, 100
        sub AX, [a10]
        add AX, [bc4]
        sub AX, [d]
        ; AX <- resultatul final
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
