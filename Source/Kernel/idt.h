#ifndef IDT_HEADER
#define IDT_HEADER

#include "stdint.h"

struct Idt64
{
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	  ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
};


extern struct Idt64 _idt[256];
extern uint64_t isr1;
extern void load_idt();

void InitializeIDT()
{
	for(uint64_t t = 0; t < 256; t++)
	{
		_idt[t].reserved = 0;
		_idt[t].isr_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
		_idt[t].isr_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
		_idt[t].isr_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
		_idt[t].ist = 0;
		_idt[t].kernel_cs = 0x08;
		_idt[t].attributes = 0x8e;

	}

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	load_idt();
}

void isr1_handler()
{
	uint8_t input = inb(0x60);

	PrintStringLn(HexToString(input));

	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}

#endif