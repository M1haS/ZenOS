ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    . = 2M;

    .text BLOCK(4K) : ALIGN(4K)
    {
        code = .; _code = .; __code = .;
	    *(.multiboot)
        *(.text)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
    }

    end = .; _end = .; __end = .;
}