ENTRY(_start)

OUTPUT_FORMAT(elf64-x86-64)

INPUT
(
    bin/boot.o
    bin/bmain.o
    bin/kernel.o
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

