#ifndef __IDT_H_
#define __IDT_H_

#include <stdint.h>

#define PIC1_ICW1 0x11
#define PIC1_ICW2 0x20
#define PIC1_ICW3 0x04
#define PIC1_ICW4 0x01

#define PIC2_ICW1 0x11
#define PIC2_ICW2 0x28
#define PIC2_ICW3 0x02
#define PIC2_ICW4 0x01

typedef struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  allways0;
    uint8_t  flags;
    uint16_t base_high;
}__attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_ptr_t;

void idt_init(void);

#endif // __IDT_H_