# Base function to print in bios state

# parameters (1 - ptr to str, 2 - str length)
bprint:
	pushw %bp
	movw %sp, %bp
	
	pushw %ax
	pushw %bx

	movb $0x13, %ah
	movb $0x01, %al
	movb $0x00, %bh   	# video page number
	movb $0x07, %bl   	# attribute if mode 0 or 1 (AL bit 1=0) # set color
	movw 4(%bp), %cx   	# length of string (ignoring attributes) # second arg

	push %bp			# save bp
	addw $6, %bp		# get address of ptr (first arg)

	movw (%bp), %bp		# load address to bp

	int $0x10

	popw %bp

	addw $4, %sp

	movw %bp, %sp
	popw %bp

    ret