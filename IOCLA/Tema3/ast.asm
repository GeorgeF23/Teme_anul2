section .data
    delim db " ", 0xA, 0
    my_str db "123", 0
    format db "%s", 0xA, 0

section .bss
    root resd 1

section .text

extern check_atoi
extern print_tree_inorder
extern print_tree_preorder
extern evaluate_tree
extern printf

global create_tree
global iocla_atoi

iocla_atoi: 
    push ebp
    mov ebp, esp

    mov ecx, [ebp + 8]  ; token
    xor eax, eax        ; numarul convertit

start:
    movzx edx, byte [ecx]
    inc ecx
    cmp edx, '0'
    jb end
    cmp edx, '9'
    jg end
    sub edx, '0'
    imul eax, 10
    add eax, edx
    jmp start

end:
    leave
    ret


create_tree:
    push ebp
    mov ebp, esp

    push my_str
    call check_atoi

    mov esi, [ebp + 8]

    xor eax, eax
    leave
    ret
