
section .data
    delim db " ", 0

section .bss
    root resd 1

section .text

extern evaluate_ast
global create_tree
global iocla_atoi

iocla_atoi: 
    ; TODO
    ret


create_tree:
    ; TODO
    enter 0, 0
    xor eax, eax
    leave
    ret
