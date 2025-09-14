bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


extern exit, printf, scanf, fprintf, fread, fopen              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s times 200 db 0
    formated_s times 200 db 0
    fileinput db "input.txt", 0
    fileoutput db "output.txt", 0
    acces_mode_r db "r",0
    acces_mode_w db "w", 0
    fd_in dd 0
    fd_out dd 0
    format_1 db "%d", 10, 0
    scanf_format db "%s", 0
    input_from_user times 100 db 0
    string_format db "%s", 0
    number_of_characters dd 0
    empty_line_format db 10,0
    number_of_spaces dd 0

; our code starts here
segment code use32 class=code
    start:
        push dword acces_mode_r
        push dword fileinput
        call [fopen]
        add esp, 4*2
        mov [fd_in], eax
        
        push dword acces_mode_w
        push dword fileoutput
        call [fopen]
        add esp, 4*2
        mov [fd_out], eax
        
        push dword [fd_in]
        push dword 200
        push dword 1
        push dword s
        call [fread]
        add esp, 4*4
        mov [number_of_characters], eax
        
        push dword [number_of_characters]
        push dword format_1
        push dword [fd_out]
        call [fprintf]
        add esp, 4*3
        
        push dword empty_line_format
        push dword [fd_out]
        call [fprintf]
        add esp, 4*2
        
        mov ecx, [number_of_characters]
        mov esi, s
        jecxz end_loop
        
        count_spaces_loop:
            lodsb
            cmp al, ' '
            jne end_inner_loop
            add dword[number_of_spaces], 1
            
            end_inner_loop:
        loop count_spaces_loop
        end_loop:
        
        push dword [number_of_spaces]
        push dword format_1
        push dword [fd_out]
        call [fprintf]
        add esp, 4*3
        
        mov ecx, [number_of_characters]
        mov esi, s
        mov edi, formated_s
        jecxz end_loop2
        convert_to_upper:
            lodsb
            cmp al, 'a'
            jb not_a_letter
            cmp al, 'z'
            ja not_a_letter
            add al, 'A'-'a'
            
            
            not_a_letter:
            stosb
        loop convert_to_upper
        
        end_loop2:
        
        push dword formated_s
        push dword string_format
        push dword [fd_out]
        call [fprintf]
        add esp, 4*3
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
