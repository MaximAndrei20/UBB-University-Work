bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


;Read two doublewords a and b in base 16 from the keyboard. Display the sum of the low parts of the two numbers and the difference between the high parts of the two numbers in base 16 Example:
;a = 00101A35h
;b = 00023219h
;sum = 4C4Eh
;difference = Eh

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    x dd 0
    y dd 0
    scanf_format db "%xh", 0
    printf_sum_format db "sum = %Xh",10,0
    printf_diff_format db "difference = %Xh",0
    sum dd 0
    diff dd 0

; our code starts here
segment code use32 class=code
    solve:
        mov eax, [esp+8]
        mov ebx, [esp+4]
        
        push eax
        pop ax
        pop dx
        push ebx
        pop bx
        pop cx
        
        ; dx:ax = a, cx:bx = b
        
        add ax,bx
        sub dx,cx
        
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
        call solve
        ;dx - diff, ax - sum
        
        cwde
        mov [sum], eax
        
        mov ax, dx
        cwde
        mov [diff], eax
        
        
        push dword[sum]
        push printf_sum_format
        call [printf]
        add esp, 4*2
        
        push dword[diff]
        push printf_diff_format
        call [printf]
        add esp, 4*2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
