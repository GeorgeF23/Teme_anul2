%include "io.mac"

section .text
	global caesar
	extern printf

caesar:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     edx, [ebp + 8]      ; ciphertext
	mov     esi, [ebp + 12]     ; plaintext
	mov     edi, [ebp + 16]     ; key
	mov     ecx, [ebp + 20]     ; length
	;; DO NOT MODIFY

	;; TODO: Implement the caesar cipher

	;;Reduc cheia la un numar din [0, 26)
	push edx
	xor edx, edx
	mov eax, edi
	mov ebx, 26
	div ebx
	mov edi, edx
	pop edx

	xor ebx, ebx    ; setez ebx la 0 pentru a-l folosi ca si index

loop_start:
	mov al, byte [esi + ebx]    ; iau caracter din plaintext

	;; Verific daca caracterul curent e litera
	cmp al, 'A'
	jl copy
	cmp al, 'Z'
	jle cipher
	cmp al, 'a'
	jl copy
	cmp al, 'z'
	jg copy

cipher:
	add eax, edi                ; ii adaug cheia
	cmp eax, 'Z'                ; verific daca caracterul rezultat e litera mare
	jle copy                    ; daca e mai mic decat 'Z' e bun
	cmp eax, 'a'                ; verific daca e litera mica
	jge check                   ; posibil litera mica

	sub eax, 26                 ; il readuc in intervalul [A, Z]
	jmp copy

check:
	cmp eax, 'z'                ; verific daca e litera mica
	jle copy                    ; e mai mic decat 'z' si mai mare decat 'a', deci e bun
	sub eax, 26                 ; il readuc in invervalul [a, z]

copy:
	mov [edx + ebx], al         ; pun rezultatul in ciphertext

	inc ebx						; trec la urmatorul caracter
	cmp ebx, ecx
	jnz loop_start

	;; DO NOT MODIFY
	popa
	leave
	ret
	;; DO NOT MODIFY