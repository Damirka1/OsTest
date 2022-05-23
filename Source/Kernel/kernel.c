#include "terminal.h"
#include "idt.h"

extern const int8_t file[];

void kernel_main()
{
    ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
    EnableCursor(13, 15);
    SetCursorPosition(PosFromCoords(0, 0));
    PrintStringColored(file, BACKGROUND_BLACK | FOREGROUND_YELLOW);

    InitializeIDT();

    // Вот из-за этой ерунды снизу я не спалл всю ночь, пытаясь разобраться
    // почему не работают прерывания.
    while(1);

    return;
}
