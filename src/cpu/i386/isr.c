#include "drivers/vga.h"
#include "i386/isr.h"

void isr_handler(regs_t regs) {
    kprintf("\nHandled interrupt %d!", regs.int_num);
}