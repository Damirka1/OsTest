ENTRY(_start)

OUTPUT_FORMAT(binary)

INPUT
(
    boot.o
)

OUTPUT
(
    boot.bin
)

SECTIONS
{
    . = 0x7c00;

    .text :
    {
        *(.text)
    }
}

