#include "terminal.h"

extern const int8 file[];

void kernel_main()
{
    ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
    EnableCursor(13, 15);
    SetCursorPosition(PosFromCoords(0, 0));
    PrintStringColored(file, BACKGROUND_BLACK | FOREGROUND_YELLOW);

    return;
}
