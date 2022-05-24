#include "terminal.h"
#include "idt.h"

extern const char file[];

void kernel_main()
{
    ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
    EnableCursor(13, 15);
    SetCursorPosition(PosFromCoords(0, 0));
    PrintStringColored(file, BACKGROUND_BLACK | FOREGROUND_YELLOW);

    InitializeIDT();

    asm volatile("int $0x30");
    asm volatile("movw $0x32, %ax; int $0x31");
    asm volatile("movl $0, %edx; movl $0, %eax; movl $0, %ecx; divl %ecx");

    while(1);

    return;
}
