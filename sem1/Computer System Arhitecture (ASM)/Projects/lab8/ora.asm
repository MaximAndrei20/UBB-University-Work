bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    x dd 0
    y dd 0
    scanf_format db "%d", 0
    printf_format db "x+y=%d",0

; our code starts here
segment code use32 class=code
    add_numbers:
        mov eax, [esp+8]
        mov ebx, [esp+4]
        
        add eax, ebx
        ret
    start:
        push dword x
        push scanf_format
        call [scanf]
        add esp, 4*2
        
        push dword y
        push scanf_format
        call [scanf]
        add esp, 4*2
        
        push dword[x]
        push dword[y]
        call add_numbers
        
        push eax
        push printf_format
        call [printf]
        add esp, 4*2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
