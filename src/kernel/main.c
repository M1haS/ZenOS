#include "i386/gdt.h"
#include "drivers/vga.h"
#include "i386/idt.h"
#include "i386/timer.h"

__attribute__((noreturn))
void kmain(void)
{
    gdt_init();
    idt_init();
    vga_init();

    kclear();
    kprintf("Hello, %s", "World!\n");
    
    __asm__ __volatile__ ("int $0x3");
    __asm__ __volatile__ ("int $0x4");
    
    timer_init(BASE_FREQ);
    __asm__ __volatile__ ("sti");

    for(;;) __asm__ __volatile__ ("hlt");
}