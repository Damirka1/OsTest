.code16
.section .text 
.globl _start;
_start:
	// setting stack
	movw $0x7c00, %bp
	movw %bp, %sp

	// Set graphics type  80x25 text mode, color
	movb $0x00, %ah
	movb $0x03, %al
	int $0x10

	# disabling cursor
	movb $0x01, %ah
	movb $0x3f, %ch
	int $0x10

	# print hello world
	pushw $hello		# $ get pointer of
	pushw hellosize		# get value of
	call bprintln

	# free stack
	addw $4, %sp

	# read disk 
	pushw bmain16		# pointer to buffer
	pushw $16		# count of sectors to read
	call rdisk

	addw $4, %sp

	jmp *bmain16

	hlt


hello: .asciz "Hello, BIOS world!"
hellosize: .word .-hello-1

# basic main
bmain16: .word 0x8000	# buffer for readed code of programm

.include "bprintln.s"
.include "rdisk.s"

.space 510-(.-_start)

.word 0xaa55 
