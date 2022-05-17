# basic main loaded from bios
.code16
.section .text
_bmain16:

    # print enter message
    pushw $hello
    pushw hellosize
    call bprintln

    # disable interrups
    cli

    # enable A20 line
    inb $0x92, %al
    orb $2, %al
    outb %al, $0x92

    # setting gdt
    lgdt (gdt_descriptor)

    # setting cr0 bit
    movl %cr0, %eax
    orl 1, %eax
    movl %eax, %cr0
    
    # jump to 32 bit basic main
    jmp $0x08, bmain32


hello: .asciz "  Excecuting basic main"
hellosize: .word .-hello-1

.include "gdt.s"

.code32
.section .text
bmain32:
    # setting data registers
    movw dataseg, %ax
    movw %ax, %ds
    movw %ax, %ss
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    # now enabling long mode (64 bit)

    # detecting cpuid
    pushfl
    popl %eax

    movl %eax, %ecx

    xorl $0x200000, %eax

    pushl %eax
    popfl

    pushfl
    popl %eax

    pushl %ecx
    popfl

    xorl %ecx, %eax
    jz no_long_mode

    # testing long mode
    movl $0x80000001, %eax
    cpuid
    testl $0x20000000, %edx
    jz no_long_mode

    # setting paging
    movl $0x1000, %edi
    movl %edi, %cr3
    movl $0x2003, (%edi)
    addl $0x1000, %edi
    movl $0x3003, (%edi)
    addl $0x1000, %edi
    movl $0x4003, (%edi)
    addl $0x1000, %edi

    movl $0x00000003, %ebx
    movl $512, %ecx

    .set_entry:
        movl %ebx, (%edi)
        addl $0x1000, %ebx
        addl $8, %edi
        loop .set_entry
    
    movl %cr4, %eax
    orl $0x20, %eax
    movl %eax, %cr4

    movl $0xC0000080, %ecx
    rdmsr
    orl $0x100, %eax
    wrmsr

    movl %cr0, %eax
    orl $0x80000000, %eax
    movl %eax, %cr0

    # now we are in compatibility mode


    hlt

no_long_mode:
    movl $0x11111111, %eax
    hlt

.space 2048-(.-_bmain16)

