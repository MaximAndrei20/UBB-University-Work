bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fprintf msvcrt.dll                      
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    output_file_name db "out.txt",0
    text db "ana  are   mere"
    lenT equ $-text
    formated_text times 100 db 0
    acces_mode_write db 'w', 0
    output_file_descriptor dd 0
    counter dd 0
    format_print_number db "%d", 0
    format_print_character db '%c', 0
    ecx_copy dd 0
    
    

; our code starts here
segment code use32 class=code
    start:
        push acces_mode_write
        push output_file_name
        call [fopen]
        add esp, 4*2
        mov [output_file_descriptor], eax
        ;getting file descriptor
        
        mov ecx, lenT
        mov esi, text
        mov edi, formated_text
        mov dword[counter], 1
        
        jecxz endloop
        repeat_label:
            mov [ecx_copy], ecx
            lodsb
            cmp al, ' '
            je do_not_change
            mov ebx, [counter]
            and ebx, 1 ;checking the parity of the index
            cmp ebx, 0
            jne do_not_change
            
            push dword[counter]
            push dword format_print_number
            push dword[output_file_descriptor]
            call [fprintf]
            add esp, 4*3
            jmp end_loop
            
            
            do_not_change:
            
            mov bl, al
            mov eax, 0
            mov al, bl
            
            push eax
            push format_print_character
            push dword [output_file_descriptor]
            call [fprintf]
            add esp, 4*3
            
            end_loop:
            inc dword[counter]
            
            mov ecx, [ecx_copy]
            loop repeat_label
        endloop
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
