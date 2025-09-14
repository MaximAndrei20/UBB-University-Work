bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

%include "modul.asm"
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format db "sum is = %d", 10, 13, 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword 100
        push dword 102
        call sum
        add esp, 2*4
        
        push eax
        push format
        call [printf]
        add esp, 2*4
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
