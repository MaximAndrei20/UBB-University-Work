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
    input_from_file times 12 db 0
    acces_mode_read db "r",0
    file_descriptor_input dd 0
    input_file_name db "input2.txt", 0
    
    acces_mode_write db "w",0
    file_descriptor_output dd 0
    output_file_name db "output2.txt", 0
    
    fprintf_format db "%s   ", 0
    
    len dd 0
    
; our code starts here
segment code use32 class=code
    start:
        push dword acces_mode_read
        push dword input_file_name
        call [fopen]
        mov [file_descriptor_input], eax
        add esp, 4*2
        
        push dword acces_mode_write
        push dword output_file_name
        call [fopen]
        mov [file_descriptor_output], eax
        add esp, 4*2
        
        read:
            push dword[file_descriptor_input]
            push 10
            push 1
            push input_from_file
            call [fread]
            add esp, 4*4
            mov [len], eax
            mov [input_from_file+eax], byte 0
            
            push dword input_from_file
            push dword fprintf_format
            push dword [file_descriptor_output]
            call [fprintf]
            add esp, 4*3
            
            cmp dword[len], dword 0
            jne read
            
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
