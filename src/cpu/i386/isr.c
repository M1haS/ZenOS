#include "drivers/vga.h"
#include "i386/isr.h"
#include "i386/ports.h"

static isr_t interrupt_handlers[256];

void isr_handler(regs_t regs)
{
    if (interrupt_handlers[regs.int_num] != 0) {
        isr_t handler = interrupt_handlers[regs.int_num];
        handler(regs);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(regs_t regs)
{
    if (regs.int_num >= 40)
        outb(0xA0, 0x20);

    outb(0xA0, 0x20); /* Send EOI to slave PIC */ 

    /* In any case, send EOI to master PIC */

    outb(0x20, 0x20);

    /* Look for the handler by number and call it */
    if (interrupt_handlers[regs.int_num] != 0) {
        isr_t handler = interrupt_handlers[regs.int_num];

        handler(regs);
    }
}