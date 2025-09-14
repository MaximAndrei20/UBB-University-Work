bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

    ;29)A byte string S is given. Build the string D whose elements represent the sum of each two consecutive bytes of S.
    ;Example:
    ;S: 1, 2, 3, 4, 5, 6
    ;D: 3, 5, 7, 9, 11
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    S db 1, 2, 3, 4, 5, 6
    lenS equ $-S
    D resb $-S-2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ESI, 0
        mov ECX, lenS-1
        jecxz end_loop
        ;itterate through the elements in D
        repeat_label:
            mov AL, [S+ESI]
            add [D+ESI], AL
            
            mov AL, [S+ESI+1]
            add [D+ESI], AL
            
            ;add to D the the sum of the current and next element in S
            
            inc ESI
        loop repeat_label
        end_loop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
