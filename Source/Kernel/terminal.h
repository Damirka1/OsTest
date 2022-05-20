#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "IO.h"
#include "TextColorCodes.h"

static unsigned char* VGABuffer = (unsigned char*)0xb8000;
static unsigned short VGAWidth = 80;
static unsigned short VGAHeight = 25;

static unsigned short CursorPosition = 0;

void ClearScreen(long long color)
{
    long long value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for(long long* i = (long long*)VGABuffer; i < (long long*)(VGABuffer + 4000); i++)
        *i = value;
}

void SetCursorPosition(unsigned short position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    CursorPosition = position;
}

void EnableCursor(unsigned char cursor_start, unsigned char cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void DisableCursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

unsigned short PosFromCoords(unsigned char x, unsigned char y)
{
    return y * VGAHeight + x;
}

void PrintStringColored(const char* str, unsigned char color)
{
    char* it = (char*)str;
    unsigned short index = CursorPosition;
    while(*it != 0)
    {
        switch (*it)
        {
        case 10:    // "\n"
            index += VGAWidth;
            break;
        case 13:    // "\r"
            index -= index % VGAWidth;
            break;
        default:
            *(VGABuffer + index * 2) = *it;
            *(VGABuffer + index * 2 + 1) = color;
            index++;
        }

        it++;
    }

    SetCursorPosition(index);
}

void PrintString(const char* str)
{
    PrintStringColored(str, BACKGROUND_BLACK | FOREGROUND_WHITE);
}

#endif