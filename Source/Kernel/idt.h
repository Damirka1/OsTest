#ifndef IDT_HEADER
#define IDT_HEADER

#include "stdint.h"

#include "interrupts.h"

struct Idt64
{
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	  	ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
};

extern struct Idt64 _idt[256];
extern void load_idt();
extern void remap_pic();

static void IdtSetDescriptor(uint8_t vector, void* isr, uint8_t flags) 
{
    struct Idt64* descriptor = &_idt[vector];
 
    descriptor->isr_low       = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs     = 0x08;
    descriptor->ist           = 0;
    descriptor->attributes    = flags;
    descriptor->isr_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved      = 0;
}

static void SetExceptions()
{
	IdtSetDescriptor(0, &divide_by_zero_isr, 0x8E);
	IdtSetDescriptor(1, &debug_isr, 0x8E);
	IdtSetDescriptor(2, &non_maskable_isr, 0x8E);
	IdtSetDescriptor(3, &breakpoint_isr, 0x8E);
	IdtSetDescriptor(4, &overflow_isr, 0x8E);
	IdtSetDescriptor(5, &bound_range_exceeded_isr, 0x8E);
	IdtSetDescriptor(6, &invalid_opcode_isr, 0x8E);
	IdtSetDescriptor(7, &device_not_available_isr, 0x8E);
	IdtSetDescriptor(8, &double_fault_isr, 0x8E);
	//IdtSetDescriptor(9, &coprocessor_segment_overrun_isr, 0x8E); // not used, skipping
	IdtSetDescriptor(10, &invalid_tss_isr, 0x8E);
	IdtSetDescriptor(11, &segment_not_present_isr, 0x8E);
	IdtSetDescriptor(12, &stack_segment_fault_isr, 0x8E);
	IdtSetDescriptor(13, &general_potection_fault_isr, 0x8E);
	IdtSetDescriptor(14, &page_fault_isr, 0x8E);
	//IdtSetDescriptor(15, &reserved, 0x8E); // reserved
	IdtSetDescriptor(16, &x87_floating_point_exception_isr, 0x8E);
	IdtSetDescriptor(17, &aligment_check_isr, 0x8E);
	IdtSetDescriptor(18, &machine_check_isr, 0x8E);
	IdtSetDescriptor(19, &simd_floating_point_exception_isr, 0x8E);
	IdtSetDescriptor(20, &virtualization_exception_isr, 0x8E);
	IdtSetDescriptor(21, &control_protection_exception_isr, 0x8E);
	// from 22 - 27 - reserved
	IdtSetDescriptor(28, &hypervisor_injection_exception_isr, 0x8E);
	IdtSetDescriptor(29, &vmm_communiction_exception_isr, 0x8E);
	IdtSetDescriptor(30, &security_exception_isr, 0x8E);
	//IdtSetDescriptor(31, &divide_by_zero_isr, 0x8E); // reserved
}

static void SetIRQ()
{
	// Timer interrupt
	IdtSetDescriptor(32, &hpt_isr, 0x8E);
	// Keyboard interrupt
	IdtSetDescriptor(33, &keyboard_isr, 0x8E);
	// // Mouse interrupt
	IdtSetDescriptor(44, &mouse_isr, 0x8E);
	// // Primary ATA Hard Disk interrupt
	// IdtSetDescriptor(46, &isr1, 0x8E);
}

static void SetSystemInterrupts()
{
	IdtSetDescriptor(48, &system_test_isr, 0x8E);
	IdtSetDescriptor(49, &system_test2_isr, 0x8E);
}

void InitializeIDT()
{
	// Set up exceptions (0 - 31)
	SetExceptions();

	// Set up IRQs (32 - 47)
	SetIRQ();

	// Set up system interrupts (48 - 255)
	SetSystemInterrupts();
	
	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	load_idt();

	remap_pic();
}




#endif