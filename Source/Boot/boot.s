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

	# print hello world
	pushw $hello		# $ get pointer of
	pushw hellosize		# get value of
	call bprintln

	# read disk 
	pushw programm	# pointer to buffer
	pushw $4		# count of sectors to read
	call rdisk

	hlt



hello: .asciz "Hello, BIOS world!"
hellosize: .word .-hello-1

programm: .word 0x7e00	# buffer for readed code of programm

.include "bprintln.s"
.include "rdisk.s"

.space 510-(.-_start)

.word 0xaa55 
