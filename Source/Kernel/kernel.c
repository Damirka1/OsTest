#include "terminal.h"

char str[] = "Hello, world!\n\r";

void kernel_main()
{
    ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
    EnableCursor(13, 15);
    SetCursorPosition(PosFromCoords(0, 0));
    PrintString(str);
    return;
}
