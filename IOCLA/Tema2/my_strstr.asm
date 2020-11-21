%include "io.mac"

section .data
	needle_start dd 0
	haystack_start dd 0

section .text
	global my_strstr
	extern printf

	my_strstr:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     edi, [ebp + 8]      ; substr_index
	mov     esi, [ebp + 12]     ; haystack
	mov     ebx, [ebp + 16]     ; needle
	mov     ecx, [ebp + 20]     ; haystack_len
	mov     edx, [ebp + 24]     ; needle_len
	;; DO NOT MODIFY

	;; TO DO: Implement my_strstr
	mov dword [needle_start], ebx   ; salvez adresa de inceput a lui needle
	mov dword [haystack_start], esi ; salvez adresa de inceput a lui haystack

	xor eax, eax

loop_start:
	mov al, byte [esi]		; caracterul curent din haystack
	cmp al, byte [ebx]		; compar cu caracterul din needle
	jne not_good
	inc esi
	inc ebx
	jmp loop_condition

not_good:
	inc esi
	mov ebx, dword [needle_start]

loop_condition:
	cmp byte [esi], 0
	je end
	cmp byte [ebx], 0
	je end
	jmp loop_start

end:
	cmp byte [ebx], 0
	jne not_found
	mov eax, esi
	sub eax, dword [haystack_start]
	sub eax, ebx
	add eax, dword [needle_start]
	mov [edi], eax
	jmp return

not_found:
	mov eax, ecx
	inc eax
	mov [edi], eax


return:
	;; DO NOT MODIFY
	popa
	leave
	ret
	;; DO NOT MODIFY
