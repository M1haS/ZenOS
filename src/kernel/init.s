.code32

/* Declare constants for the multiboot header */
.set ALIGN,     1 << 0              /* align loaded modules on page boundaries */
.set MEMINFO,   1 << 1              /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO     /* this is the Multiboot 'flag' field */
.set MAGIC,     0x1BADB002          /* 'magic number' lets bootloader find the header */
.set CHECKSUM,  -(MAGIC + FLAGS)    /* checksum of above, to prove we are multiboot */

/* Declare a multiboot header that marks the program as a kernel. These are magic
   values that are documented in the multiboot standard (first 8 KiB)
*/
.section .multiboot
    .align  4
    .long   MAGIC
    .long   FLAGS
    .long   CHECKSUM

/* Allocating stack */
.section .bss
    .align  4
stack_bottom:
    # 1 MB of uninitialized data for stack
    .fill   104856, 1, 0
stack_top:

/* The linker script specifies _start as the entry point to the kernel and the
   bootloader will jump to this position once the kernel has been loaded
*/
.section .text
    .global _start
    .type   _start, @function

_start:
    cli
    mov     $stack_top, %esp
    
    call    kmain

.halt:
    hlt
    jmp .halt

/* Set the size of the _start symbol to the current location '.' minus its start.
   This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start