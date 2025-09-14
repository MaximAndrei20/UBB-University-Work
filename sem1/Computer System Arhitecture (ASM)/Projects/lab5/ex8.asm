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
    S db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    lenS db $-S
    D resb $-S-1
    
    
    ; 29) A byte string S is given. Build the string D whose elements represent the sum of each two consecutive bytes of S.
;Example:
;S: 1, 2, 3, 4, 5, 6
;D: 3, 5, 7, 9, 11

; our code starts here
segment code use32 class=code
    start:
        mov ESI, 0
        mov ECX, lenS
        mov EBX, 0
        jecxz end_loop
        repeat_label:
            mov AL, [S+ESI]
            cmp AL, 'Z'
            ja not_a_uppercase_letter
            cmp AL, 'A'
            jb not_a_uppercase_letter

            mov [D+EBX], AL
            inc EBX
            
            
            not_a_uppercase_letter:
            inc ESI
        loop repeat_label
        end_loop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        