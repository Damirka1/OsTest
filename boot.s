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

	// print string
	movb $0x13, %ah
	movb $0x01, %al
	movb $0x00, %bh # video page number
	movb $0x07, %bl # attribute if mode 0 or 1 (AL bit 1=0) # set color
	movw $18, %cx   # length of string (ignoring attributes)

	leaw hello, %bp

	int $0x10

	hlt

hello: .asciz "Hello, BIOS world!"
	. = _start + 510

.word 0xaa55 
#.byte 0xaa
