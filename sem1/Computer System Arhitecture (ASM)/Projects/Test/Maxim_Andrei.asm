bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll

                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    input_file_name db "input.txt",0
    output_file_name db "output.txt", 0
    acces_mode_w db "w", 0
    acces_mode_r db "r", 0
    input_file_descriptor dd 0
    output_file_descriptor dd 0
    text times 105 db 0
    len dd 0
    format_print_number db "%d", 10, 0
    nume times 100 db 0
    format_print_string db "%s", 10, 0
    counter_plus_10 dd 0
    len_nume dd 0
    gender times 3 db 0
    
; our code starts here
segment code use32 class=code
    start:
        push dword acces_mode_r
        push dword input_file_name
        call [fopen]
        add esp, 4*2
        
        test eax, eax
        jz final
        mov [input_file_descriptor], eax
        
        push dword acces_mode_w
        push dword output_file_name
        call [fopen]
        add esp, 4*2
        
        test eax,eax
        jz final
        mov [output_file_descriptor], eax
        
        
        push dword [input_file_descriptor]
        push dword 104
        push dword 1
        push text
        call [fread]
        add esp, 4*4
        mov [len], eax
        
        push dword [len]
        push dword format_print_number
        push dword [output_file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        ;get the name
        mov esi, text
        mov edi, nume
        
        start_loop_nume:
            cmp byte[esi], ' '
            je final_loop_nume
            movsb
            add dword [len_nume], 1
            jmp start_loop_nume
        final_loop_nume:
        
        ; get the counter
        
        add esi, 5
        mov bl, [esi]
        sub bl, '0'
        xor eax, eax
        mov al,bl
        add eax, 10
        mov [counter_plus_10], eax
        
        
        
        push dword nume
        push dword format_print_string
        push dword [output_file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        push dword [counter_plus_10]
        push dword format_print_number
        push dword [output_file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        ;check char from nume+len_nume-1
        
        mov eax, [len_nume]
        cmp byte[eax+nume-1], 'a'
        je fata
        ;caz baiat
        mov byte[gender], 'M'
        jmp gata_gender
        fata:
        mov byte[gender], 'F'
        jmp gata_gender
        
        gata_gender:
        push dword gender
        push dword format_print_string
        push dword [output_file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        
        
        final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
