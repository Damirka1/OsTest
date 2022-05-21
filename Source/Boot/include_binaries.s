.macro include_binary name, file
    .section .rodata
    .globl \name
\name:
    .incbin "\file"
    .byte 0
    \name\()_size: .quad \name\()_size - \name
.endm

include_binary file "test.txt"
