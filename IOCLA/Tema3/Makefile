CC=gcc -g
CFLAGS=-m32
ASM=nasm
ASMFLAGS=-f elf32 -g



build: ast.o ast_utils.o
	$(CC) $(CFLAGS) -o ast $^
ast.o: ast.asm
	$(ASM) $(ASMFLAGS) $< -o $@
clean: 
	rm ast ast.o
