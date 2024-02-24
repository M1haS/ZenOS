ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    __kernel_section_start = .;

    /* Text section */
    .text 2M : {
        __kernel_text_section_start = .;
        . = ALIGN(4);

        /* Set multiboot header */
	    *(.multiboot)
        code = .; _code = .; __code = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4K);
        __kernel_text_section_end = .;
    }

    /* Initialized data section */
    .data : {
        __kernel_data_section_start = .;
        data = .; _data = .; __data = .;
        *(.data)
        . = ALIGN(4K);
        __kernel_data_section_end = .;
    }

    /* Constant data section */
    .rodata : {
        __kernel_rodata_section_start = .;
        *(.rodata)
        __kernel_rodata_section_end = .;
    }

    /* Uninitialized data section */
    .bss : {
        __kernel_bss_section_start = .;
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4K);
        __kernel_bss_section_end = .;
    }

    end = .; _end = .; __end = .;
    __kernel_section_end = .;
}