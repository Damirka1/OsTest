.extern _idt

idt_descriptor:
    .word 4095
    .quad _idt

.macro PUSHALL
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rax
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
.endm

.macro POPALL
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rax
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    
.endm

.macro reserved name
.globl \name\()_isr
\name\()_isr:
    iretq
.endm

.macro isr_with_error_code name
.extern \name\()_handler
.globl \name\()_isr
\name\()_isr:
    PUSHALL
    call \name\()_handler
    // end of interrupt
    movb $0x20, %al
    outb %al, $0x20
    movb $0xa0, %al
	outb %al, $0x20
    POPALL
    addq $4, %rsp
    iretq
.endm

.macro isr name
.extern \name\()_handler
.globl \name\()_isr
\name\()_isr:
    PUSHALL
    call \name\()_handler
    // end of interrupt
    movb $0x20, %al
    outb %al, $0x20
    movb $0xa0, %al
	outb %al, $0x20
    POPALL
    iretq
.endm

// 32 exceptions
isr divide_by_zero
isr debug
isr non_maskable
isr breakpoint
isr overflow
isr bound_range_exceeded
isr invalid_opcode
isr device_not_available
isr_with_error_code double_fault
// reserved coprocessor_segment_overrun
isr_with_error_code invalid_tss
isr_with_error_code segment_not_present
isr_with_error_code stack_segment_fault
isr_with_error_code general_potection_fault
isr_with_error_code page_fault
// reserved res15
isr x87_floating_point_exception
isr_with_error_code aligment_check
isr machine_check
isr simd_floating_point_exception
isr virtualization_exception
isr_with_error_code control_protection_exception
// reserved res22
// reserved res23
// reserved res24
// reserved res25
// reserved res26
// reserved res27
isr hypervisor_injection_exception
isr_with_error_code vmm_communiction_exception
isr_with_error_code security_exception

// 16 IRQ
isr hpt
isr keyboard

.globl load_idt
load_idt:
    lidt idt_descriptor
    sti
    retq


.globl remap_pic
remap_pic:

	movb $0x11, %al
	outb %al, $0x20
 
	outb %al, $0xA0
 
	movb $0x20, %al
	outb %al, $0x21 
	movb $0x28, %al
	outb %al, $0xA1

	movb $0x4, %al
	outb %al, $0x21
 
	movb $0x2, %al
	outb %al, $0xA1
 
	movb $1, %al
 
	outb %al, $0x21
	outb %al, $0xA1

	movb $0, %al
	outb %al, $0x21
	outb %al, $0xA1

    retq
