#include "terminal.h"

char str[] = "Hello, world!\n\r";

void kernel_main()
{
    SetCursorPosition(PosFromCoords(0, 0));
    Print(str);
    return;
}
