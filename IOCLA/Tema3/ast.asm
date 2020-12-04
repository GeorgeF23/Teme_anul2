
section .data
    delim db " ", 0
    format db "%s", 0xA, 0

section .bss
    root resd 1

section .text

extern evaluate_ast
extern printf
global create_tree
global iocla_atoi

iocla_atoi: 
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]  ; token
    xor eax, eax        ; numarul convertit

start:
    movzx ebx, byte [esi]
    inc esi
    cmp ebx, '0'
    jb end
    cmp ebx, '9'
    jg end
    sub ebx, '0'
    imul eax, 10
    add eax, ebx
    jmp start

end:
    leave
    ret


create_tree:
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]
    inc esi
    mov [ebp + 8], esi
    push dword [ebp + 8]
    push format
    call printf

    xor eax, eax
    leave
    ret
