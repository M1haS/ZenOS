#ifndef __KERNEL_H_
#define __KERNEL_H_

#include <stdint.h>

/* i386 */
#include "i386/gdt.h"
#include "i386/idt.h"
#include "i386/timer.h"

/* drivers */
#include "drivers/vga.h"

/* Symbols from linker.ld for section addresses */
extern uint8_t __kernel_section_start;
extern uint8_t __kernel_section_end;
extern uint8_t __kernel_text_section_start;
extern uint8_t __kernel_text_section_end;
extern uint8_t __kernel_data_section_start;
extern uint8_t __kernel_data_section_end;
extern uint8_t __kernel_rodata_section_start;
extern uint8_t __kernel_rodata_section_end;
extern uint8_t __kernel_bss_section_start;
extern uint8_t __kernel_bss_section_end;

#endif // __KERNEL_H_