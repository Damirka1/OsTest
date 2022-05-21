#ifndef IDT_HEADER
#define IDT_HEADER

#include "typedef.h"

struct IdtEntry 
{
	uint16    isr_low;      // The lower 16 bits of the ISR's address
	uint16    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8	  ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8     attributes;   // Type and attributes; see the IDT page
	uint16    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32    isr_high;     // The higher 32 bits of the ISR's address
	uint32    reserved;     // Set to zero
};

struct Idtr
{
    uint16 limit;
    uint64 base;
};

static struct IdtEntry idt[256];
static struct Idtr idtr;



#endif