.extern _idt

idt_descriptor:
    .word 4095
    .quad _idt

.macro PUSHALL
    pushq %rax
    pushq %rcx
    pushq %rdx
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
    popq %rdx
    popq %rcx
    popq %rax
.endm

.extern isr1_handler

.globl isr1
isr1:
    PUSHALL
    call isr1_handler
    POPALL
    iretq

.globl load_idt
load_idt:
    lidt idt_descriptor
    sti
    retq
