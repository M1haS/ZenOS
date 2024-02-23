#ifndef __IDT_H_
#define __IDT_H_

#include <stdint.h>

typedef struct {
    uint16_t base_low;   // Lower 16 bits of the entry's base address
    uint16_t selector;   // Code segment selector
    uint8_t  allways0;   // Always zero
    uint8_t  flags;      // Flags for the entry
    uint16_t base_high;  // Upper 16 bits of the entry's base address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_ptr_t;

void idt_init(void);

#endif // __IDT_H_