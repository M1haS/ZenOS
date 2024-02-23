#include "i386/gdt.h"
#include "drivers/vga.h"

__attribute__((noreturn))
void kmain(void)
{
    gdt_init();
    vga_init();

    kclear();
    kprintf("Hello, %s", "World!");

    for(;;) __asm__ __volatile__ ("hlt");
}