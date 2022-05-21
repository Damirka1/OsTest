#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "IO.h"
#include "TextColorCodes.h"

static uint8* VGABuffer = (unsigned char*)0xb8000;
static uint16 VGAWidth = 80;
static uint16 VGAHeight = 25;

static uint16 CursorPosition = 0;

void ClearScreen(int64 color)
{
    int64 value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for(int64* i = (long long*)VGABuffer; i < (long long*)(VGABuffer + 4000); i++)
        *i = value;
}

void SetCursorPosition(uint16 position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8)((position >> 8) & 0xFF));

    CursorPosition = position;
}

void EnableCursor(uint8 cursor_start, uint8 cursor_end)
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

unsigned short PosFromCoords(uint8 x, uint8 y)
{
    return y * VGAHeight + x;
}

void PrintStringColored(const int8* str, uint8 color)
{
    int8* it = (int8*)str;
    uint16 index = CursorPosition;
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

void PrintString(const int8* str)
{
    PrintStringColored(str, BACKGROUND_BLACK | FOREGROUND_WHITE);
}

#endif