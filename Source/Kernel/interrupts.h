#include "stdint.h"

#define IsrHandler(name, x) \
extern uint32_t name##_isr; \
void name##_handler() x

#define NullFunc { return; }

#define NullHandler(name) IsrHandler(name, NullFunc)

// 32 exceptions
IsrHandler(divide_by_zero, 
{
    PrintString("Testing interrupts, 0 / 0\n\r");
    PrintStringColored("Exception interrupt: divide by zero", FOREGROUND_LIGHTRED | BACKGROUND_BLACK);
    asm volatile("cli; hlt;");
    return;
})
IsrHandler(debug, NullFunc)

IsrHandler(non_maskable, NullFunc)
IsrHandler(breakpoint, NullFunc)

IsrHandler(overflow, NullFunc)
IsrHandler(bound_range_exceeded, NullFunc)
IsrHandler(invalid_opcode, NullFunc)
IsrHandler(device_not_available, NullFunc)

IsrHandler(double_fault, NullFunc)

NullHandler(coprocessor_segment_overrun)

NullHandler(invalid_tss)
NullHandler(segment_not_present)
NullHandler(stack_segment_fault)
NullHandler(general_potection_fault)
NullHandler(page_fault)

NullHandler(x87_floating_point_exception)
NullHandler(aligment_check)
NullHandler(machine_check)
NullHandler(simd_floating_point_exception)
NullHandler(virtualization_exception)
NullHandler(control_protection_exception)

NullHandler(hypervisor_injection_exception)
NullHandler(vmm_communiction_exception)
NullHandler(security_exception)

// 16 IRQ

IsrHandler(hpt, 
{
    return;
})

IsrHandler(keyboard, 
{
    uint16_t value = inb(0x60);
    PrintString(HexToString(value));
    return;
})
