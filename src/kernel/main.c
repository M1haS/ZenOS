#include "i386/gdt.h"
#include <stdint.h>

#define WHITE_ON_BLACK 0x0F
#define VGA_MEMORY     0xB8000

void kputs(char *str)
{
    uint8_t *vga = (uint8_t *) VGA_MEMORY;
    for(int i = 0; str[i] != '\0'; ++i) {
        *vga++ = str[i];
        *vga++ = WHITE_ON_BLACK;
    }
}

void kclear()
{
    uint8_t *vga = (uint8_t *) VGA_MEMORY;
    for(int i = 0; i <= 80 * 20; ++i) {
        *vga++ = ' ';
        *vga++ = WHITE_ON_BLACK;
    }
}

__attribute__((noreturn))
void kmain(void)
{
    kclear();
    kputs("Hello, World");
    
    gdt_init();

    for(;;) __asm__ __volatile__ ("hlt");
}