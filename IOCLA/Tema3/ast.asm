section .data
    delim db " ", 0xA, 0
    format db "%s", 0xA, 0

    node_size dd 12
    root dd 0

section .text

extern check_atoi
extern print_tree_inorder
extern print_tree_preorder
extern evaluate_tree
extern printf
extern strtok
extern malloc
extern strdup

global create_tree
global iocla_atoi
global create_new_node

iocla_atoi: 
    push ebp
    mov ebp, esp

    mov ecx, [ebp + 8]  ; token
    xor eax, eax        ; numarul convertit

start:
    movzx edx, byte [ecx]
    inc ecx
    cmp edx, '0'
    jb end_atoi
    cmp edx, '9'
    jg end_atoi
    sub edx, '0'
    imul eax, 10
    add eax, edx
    jmp start

end_atoi:
    leave
    ret

create_new_node:
    push ebp
    mov ebp, esp

    push ebx
    mov ebx, [ebp + 8]  ; data

    push dword [node_size]
    call malloc     ; aloc memorie pentru noul nod
    add esp, 4

    push eax        ; salvez adresa nodului
    push ebx        ; pun data pe stiva
    call strdup     ; duplic sirul data
    add esp, 4      ; refac stiva
    mov ebx, eax    ; salvez rezultatul lui strdup
    pop eax         ; reiau de pe stiva adresa nodului

    mov dword [eax], ebx    ; setez data
    mov dword [eax + 4], 0  ; setez left
    mov dword [eax + 8], 0  ; setez right

    pop ebx
    leave
    ret

create_tree:
    push ebp
    mov ebp, esp
    
    push esi    ; salvez esi
    push ebx    ; salvez ebx
    mov esi, [ebp + 8]  ; token

    push delim
    push esi
    call strtok     ; scot primul operator
    add esp, 8      ; refac stiva

    push eax    ; parametrul functiei create_new_node
    call create_new_node    ; creez nodul nou
    add esp, 4  ; refac stiva
    mov dword [root], eax   ; salvez radacina

    push eax


start_while:
    push delim
    push 0x00000000
    call strtok     ; extrag urmatorul operator
    add esp, 8      ; refac stiva

    cmp eax, 0
    je end_create_tree
    pop ebx         ; scot ultimul nod pus pe stiva

    push eax
    call create_new_node    ; creez nodul nou
    add esp, 4      ; refac stiva

    cmp dword [ebx + 4], 0
    jne put_right
    mov [ebx + 4], eax
    push ebx
    jmp check_operator

put_right:
    mov [ebx + 8], eax

check_operator:
    nop

    jmp start_while

end_create_tree:
    pop ebx     ; restaurez ebx
    pop esi     ; restaurez esi
    mov eax, dword [root]   ; salvez valoarea de return
    leave
    ret
