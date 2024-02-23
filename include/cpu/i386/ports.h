#ifndef __IO_PORTS_H_
#define __IO_PORTS_H_

#include <stdint.h>

/* Byte */
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

/* Word */
uint16_t inw(uint16_t port);

#endif // __IO_PORTS_H_