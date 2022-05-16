ENTRY(_start)

OUTPUT_FORMAT(elf64-x86-64)

INPUT
(
    bin/boot.o
)

OUTPUT
(
    bin/boot.elf
)


SECTIONS
{
    . = 0x7c00;

    .text :
    {
        *(.text)
    }
}

