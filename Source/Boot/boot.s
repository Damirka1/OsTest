.code16

.section .text 
	.globl _start;
	
_start:
	// Set graphics type
	movb $0x00, %ah
	movb $0x03, %al
	int $0x10

	// Set cursor type
	movb $0x01, %ah
	movb $0x0D, %ch # start
	movb $0x0E, %cl # end
	int $0x10

	// Set cursor position
	movb $0x02, %ah
	movb $0x00, %bh
	movb $0x00, %dh
	movb $0x00, %dl
	int $0x10

	movw $0x7c00, %bp
	movw %bp, %sp

	pushw $hello
	pushw $18

	call bprint
	
	hlt



hello: .asciz "Hello, BIOS world!"

.include "bprint.s"

	.space 510-(.-_start)

.word 0xaa55 
