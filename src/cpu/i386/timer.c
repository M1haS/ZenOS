#include "i386/timer.h"
#include "i386/isr.h"
#include "i386/ports.h"
#include "drivers/vga.h"

uint32_t tick = 0;

uint8_t  hour = 0;
uint8_t  min = 0;
uint8_t  sec = 0;

static void timer_callback(regs_t regs)
{
    ++tick;
    
    if (tick == BASE_FREQ) {
        tick = 0;
        ++sec;

        if (sec >= 60) {
            sec = 0;
            ++min;
            
            if (min >= 60) {
                min = 0;
                ++hour;
                
                if (hour >= 24)
                    hour = 0;
            }
        }
    }
    kprintf("Time of work: %d:%d:%d\r", hour, min, sec);
}

void timer_init(uint32_t frequency)
{
    uint32_t divisor;       /* Frequency divider*/
    uint8_t low;            /* Low byte of the divider */
    uint8_t high;           /* High byte of the divider */
    
    /* Register a handler for IRQ0 in the system */
    register_interrupt_handler(IRQ0, &timer_callback);
    
    /* Calculate the divider based on the given frequency */
    divisor = 1193180/frequency;
    
    /* Set the timer operating mode */
    outb(0x43, 0x36);
    
    /* Parse the divider into bytes */
    low = (uint8_t) (divisor & 0xFF);
    high = (uint8_t) ( (divisor >> 8) & 0xFF );
    
    /* Send the divider to channel 0 PIT */
    outb(0x40, low);
    outb(0x40, high);
}