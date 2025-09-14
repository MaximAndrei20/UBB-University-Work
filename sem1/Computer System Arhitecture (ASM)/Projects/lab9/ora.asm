bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf, fprintf, fread, fopen              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s times 100 db 0
    filename db "input.txt", 0
    fileoutput db "output.txt", 0
    acces_mode db "r",0
    acces_mode_w db "w", 0
    fd dd 0
    fd_out dd 0
    format_output db "%s", 0
    scanf_format db "%s", 0
    input_from_user times 100 db 0
    printf_format db " %s", 0
    

; our code starts here
segment code use32 class=code
    start:
        push dword acces_mode
        push dword filename
        call [fopen]
        add esp, 4*2
        mov [fd], eax
        
        
        push dword [fd]
        push dword 50
        push dword 1
        push dword s
        call [fread]
        add esp, 4*4
        
        push dword acces_mode_w
        push dword fileoutput
        call [fopen]
        add esp, 4*2
        mov [fd_out], eax
        
        push dword s
        push dword format_output
        push dword [fd_out]
        call [fprintf]
        add esp, 4*3
        
        push input_from_user
        push scanf_format
        call [scanf]
        add esp, 4*2
        
        push dword input_from_user
        push dword printf_format
        push dword [fd_out]
        call [fprintf]
        add esp, 4*3
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
