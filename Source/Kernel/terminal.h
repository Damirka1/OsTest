#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "IO.h"

unsigned char* VGABuffer = (unsigned char*)0xb8000;
unsigned short VGAWidth = 80;
unsigned short VGAHeight = 25;

unsigned short CursorPosition = 0;

void SetCursorPosition(unsigned short position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    CursorPosition = position;
}

unsigned short PosFromCoords(unsigned char x, unsigned char y)
{
    return y * VGAHeight + x;
}

void Print(const char* str)
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
            index++;
        }

        it++;
    }

    SetCursorPosition(index);
}

#endif