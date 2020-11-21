%include "io.mac"

section .data
	hex_chars db "0123456789ABCDEF"
	groups_number dd 0		; cate grupari de 4 biti sunt in bin_sequence
	excess dd 0				; cati biti raman la inceput fara grupa de 4
	hexa_start dd 0

section .text
    global bin_to_hex
    extern printf

bin_to_hex:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]      ; hexa_value
    mov     esi, [ebp + 12]     ; bin_sequence
    mov     ecx, [ebp + 16]     ; length
    ;; DO NOT MODIFY

    ;; TODO: Implement bin to hex

	mov dword [hexa_start], edx		; Salvez adresa de inceput a sirului in hexa

	;; Calculez catul si restul impartirii lui length la 4
	push edx
	mov eax, ecx
	xor edx, edx
	mov ebx, 4
	div ebx
	mov dword [groups_number], eax
	inc dword [groups_number]
	mov dword [excess], edx
	pop edx

	xor eax, eax
	xor ebx, ebx
	xor edi, edi

	cmp dword [excess], 0
	je extract_next_group

	mov eax, 0x30303030		; Pun 4 caractere '0' in eax

process_first_group:	; Adaug 0 la primii biti, in cazul in care acestia nu sunt in pereche de 4
	shl eax, 8
	mov al, byte [esi]
	inc esi
	dec dword [excess]
	jnz process_first_group



process_groups:
	xor edi, edi
	cmp al, '0'
	je second_bit
	add edi, 1

second_bit:
	shr eax, 8
	cmp al, '0'
	je third_bit
	add edi, 2

third_bit:
	shr eax, 8
	cmp al, '0'
	je fourth_bit
	add edi, 4

fourth_bit:
	shr eax, 8
	cmp al, '0'
	je append_to_edx
	add edi, 8

append_to_edx:
	push ecx
	mov cl, [hex_chars + edi]
	mov byte [edx], cl
	inc edx
	pop ecx

extract_next_group:
	mov al, byte [esi]
	shl eax, 8
	inc esi
	mov al, byte [esi]
	shl eax, 8
	inc esi
	mov al, byte [esi]
	shl eax, 8
	inc esi
	mov al, byte [esi]
	inc esi
	dec dword [groups_number]
	jnz process_groups


end:
	mov byte [edx], 0x0a
	mov edx, dword [hexa_start]
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY