%include "io.mac"

section .data
	letter_count dd 0
	key_len dd 0
	new_letter_offset dd 0

section .text
	global vigenere
	extern printf

vigenere:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     edx, [ebp + 8]      ; ciphertext
	mov     esi, [ebp + 12]     ; plaintext
	mov     ecx, [ebp + 16]     ; plaintext_len
	mov     edi, [ebp + 20]     ; key
	mov     ebx, [ebp + 24]     ; key_len
	;; DO NOT MODIFY

	;; TODO: Implement the Vigenere cipher
	mov [key_len], ebx			; salvez lungimea cheii in memorie pentru a elibera un registru
	xor ebx, ebx

loop_start:
	mov al, byte [esi + ebx]	; extrag caracter din plaintext
	;; Verific daca e litera
	cmp al, 'A'
	jl copy
	cmp al, 'Z'
	jle found_letter
	cmp al, 'a'
	jl copy
	cmp al, 'z'
	jg copy

found_letter:
	push edx	; salvez edx pe stiva
	push eax	; salvez eax pe stiva

	;; Caut litera corespunzatoare din cheie si ii salvez index-ul in edx
	xor edx, edx
	mov eax, dword [letter_count]
	div dword [key_len]
	mov al, [edi + edx]
	
	sub al, 'A'		; ii aflu ordinea din alfabet a literei din cheie
	mov byte [new_letter_offset], al
	pop eax
	add al, byte [new_letter_offset]	; adaug literei din plaintext index-ul din alfabet al caracterului din cheie
	pop edx
	add dword [letter_count], 1

	;; Verific daca caracterul rezultat e litera, daca nu ii scad 26 pentru a-l face litera
	cmp al, 'Z'
	jbe copy
	cmp al, 'a'
	jae check
	sub al, 26
	jmp copy

check:
	cmp al, 'z'
	jbe copy
	sub al, 26

copy:
	mov [edx + ebx], al		; pun litera rezultata in ciphertext
	inc ebx
	cmp ebx, ecx
	jl loop_start


	;; Resetez valorile din memorie astfel incat sa nu interfereze cu urmatorul test
	mov byte [letter_count], 0
	mov byte [key_len], 0
	mov byte [new_letter_offset], 0

	;; DO NOT MODIFY
	popa
	leave
	ret
	;; DO NOT MODIFY