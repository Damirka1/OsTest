gdt_nulldesc:
    .long 0
    .long 0
gdt_codedesc:
    .word 0xFFFF        # limit
    .word 0x0000        # Base (low)
    .byte 0x00          # Base (medium)
    .byte 0b10011010    # Flags
    .byte 0b11001111    # Flags + Upper limit
    .byte 0x00          # Base (high)
gdt_datadesc:
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0b10010010
    .byte 0b11001111
    .byte 0x00

gtd_end:

gdt_descriptor:
    gdt_size:
        .word gtd_end - gdt_nulldesc - 1
        .long gdt_nulldesc

codeseg:
    .word gdt_codedesc - gdt_nulldesc
dataseg:
    .word gdt_datadesc - gdt_nulldesc
