#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "stdint.h"

#include "IO.h"
#include "TextColorCodes.h"

static uint8_t* VGABuffer = (unsigned char*)0xb8000;
static uint16_t VGAWidth = 80;
static uint16_t VGAHeight = 25;

static uint16_t CursorPosition = 0;

void ClearScreen(int64_t color)
{
    int64_t value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;

    for(int64_t* i = (int64_t*)VGABuffer; i < (int64_t*)(VGABuffer + 4000); i++)
        *i = value;
}

void SetCursorPosition(uint16_t position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));

    CursorPosition = position;
}

void EnableCursor(uint8_t cursor_start, uint8_t cursor_end)
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

unsigned short PosFromCoords(uint8_t x, uint8_t y)
{
    return y * VGAHeight + x;
}

void puts(char ch)
{
    *(VGABuffer + CursorPosition * 2) = ch;
    CursorPosition++;
    SetCursorPosition(CursorPosition);
}

void PrintStringColored(const char* str, uint8_t color)
{
    char* it = (char*)str;
    uint16_t index = CursorPosition;
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

        if(index >= VGAWidth * VGAHeight)
            index = 0;
    }

    SetCursorPosition(index);
}

void PrintString(const char* str)
{
    PrintStringColored(str, BACKGROUND_BLACK | FOREGROUND_WHITE);
}

static char hexToStringOutput[128];
const char* HexToString(uint16_t value){
  uint16_t* valPtr = &value;
  uint8_t* ptr;
  uint8_t temp;
  uint8_t size = (sizeof(uint16_t)) * 2 - 1;
  uint8_t i;
  for (i = 0; i < size; i++){
    ptr = ((uint8_t*)valPtr + i);
    temp = ((*ptr & 0xF0) >> 4);
    hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    temp = ((*ptr & 0x0F));
    hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
  }
  hexToStringOutput[size + 1] = 0;
  return hexToStringOutput;
}

#endif