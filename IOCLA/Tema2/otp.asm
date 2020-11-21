%include "io.mac"

section .text
	global otp
	extern printf

otp:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     edx, [ebp + 8]      ; ciphertext
	mov     esi, [ebp + 12]     ; plaintext
	mov     edi, [ebp + 16]     ; key
	mov     ecx, [ebp + 20]     ; length
	;; DO NOT MODIFY

	xor ebx, ebx	; folosit ca index

loop_start:
	mov al, byte [esi + ebx]	; extrag caracter in plaintext
	xor al, byte [edi + ebx]	; ii fac xor cu cel din key
	mov byte [edx + ebx], al	; mut rezultatul in ciphertext
	inc ebx						; trec la urmatorul index
	cmp ebx, ecx				; conditie de oprire
	jnz loop_start

	;; DO NOT MODIFY
	popa
	leave
	ret
	;; DO NOT MODIFY