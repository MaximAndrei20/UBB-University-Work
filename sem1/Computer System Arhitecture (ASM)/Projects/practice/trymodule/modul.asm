%ifndef _SUM_
%define _SUM_
    sum:
        mov eax, [esp + 4]
        add eax, [esp+8]
        ret
%endif