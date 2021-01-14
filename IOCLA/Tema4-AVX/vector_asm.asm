section .text
    global i_vector_op
    global i_vector_op_avx

i_vector_op:
    push rbp
    mov rbp, rsp

    ; I'll use rdx below, so I copy its value in r9
    ; Also, loop changes the value of rcx, so I make a copy in r10
    mov r9, rdx
    mov r10, rcx

; I square each element of A and place the result in C
square_loop:
    mov eax, [rdi + 4 * rcx - 4]
    mov edx, eax
    mul edx
    mov [r9 + 4 * rcx - 4], eax
    loop square_loop

    mov rcx, r10

; I multiply each element of B with 2, and add it to C
x2_loop:
    mov eax, [rsi + 4 * rcx - 4]
    mov edx, 2
    mul edx
    add [r9 + 4 * rcx - 4], eax
    loop x2_loop

    leave
    ret

i_vector_op_avx:
    ; Optimize the code above
    push rbp
    mov rbp, rsp

    ; rdi -> A
    ; rsi -> B
    ; rdx -> C
    ; rcx -> n

    push 0x2    ; pun 2 pe stiva
    vbroadcastss ymm2, [rsp]    ; Fac un vector __m256i plin de 2
    pop rbx ; scot 2 de pe stiva

    xor rbx, rbx    ; loop index


avx_square_loop:

    vmovdqu ymm0, [rdi] ; Incarc A in ymm0
    vmovdqu ymm1, [rsi] ; Incarc B in ymm0
    
    vpmulld ymm0, ymm0, ymm0    ; A = A .* A
    vpmulld ymm1, ymm1, ymm2    ; B = B .* 2
    vpaddd ymm3, ymm0, ymm1     ; ymm3 = ymm0 + ymm1 = A .* A + B .* 2
    vmovdqu [rdx], ymm3         ; C = ymm3
    

    add rbx, 8  ; incrementez loop index
    ; trec la urmatoarele valori
    add rdi, 32 
    add rsi, 32
    add rdx, 32

    cmp rbx, rcx
    jb avx_square_loop

    leave
    ret