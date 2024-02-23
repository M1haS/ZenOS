#include "i386/gdt.h"
#include "drivers/vga.h"
#include "i386/idt.h"

__attribute__((noreturn))
void kmain(void)
{
    gdt_init();
    idt_init();
    vga_init();

    kclear();
    kprintf("Hello, %s", "World!");
    kputs("\n");
    
    __asm__ __volatile__ ("int $0x3");
    __asm__ __volatile__ ("int $0x4");

    for(;;) __asm__ __volatile__ ("hlt");
}