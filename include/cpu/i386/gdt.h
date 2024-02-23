#ifndef __GLOBAL_DESCRIPTOR_TABLE_H__
#define __GLOBAL_DESCRIPTOR_TABLE_H__

#include <stdint.h>

typedef struct {
    uint16_t limit_low;     // Lower 16 bits of segment limit
    uint16_t base_low;      // Lower 16 bits of the segment's base address
    uint8_t  base_middle;   // Middle byte of the segment base address
    uint8_t  access;        // Access byte and segment attributes
    uint8_t  granularity;   // Byte granularity and segment size
    uint8_t  base_high;     // Upper byte of the segment base address
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

/* Assembly function in gdt_flush.s */
extern void gdt_flush(uint32_t);
void gdt_init(void);

#endif // __GLOBAL_DESCRIPTOR_TABLE_H__