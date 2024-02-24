#ifndef __MULTIBOOT_H_
#define __MULTIBOOT_H_

#include <stdint.h>

#define MULTIBOOT_MAGIC_HEADER      0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002

/* The Multiboot header. */
typedef struct {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
} multiboot_header_t;

/* The symbol table for a.out. */
typedef struct {
    uint32_t tabsize;
    uint32_t strsize;
    uint32_t addr;
    uint32_t reserved;
} aout_symbol_table_t;

/* The section header table for ELF. */
typedef struct {
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
} elf_section_header_table_t;

typedef struct {
    /* Required, defined in init.s */
    uint32_t flags;

    /* Available low-high memory from BIOS, present if flags[0] is set(MEMINFO in init.s) */
    uint32_t mem_low;
    uint32_t mem_high;

    /* "root" partition, present if flags[1] is set(BOOTDEVICE in init.s) */
    uint32_t boot_device;

    /* kernel command line, present if flags[2] is set(CMDLINE in init.s) */
    uint32_t cmdline;

    /* no of modules loaded, present if flags[3] is set(MODULECOUNT in init.s) */
    uint32_t modules_count;
    uint32_t modules_addr;

    /* symbol table info, present if flags[4] & flags[5] is set(SYMT in init.s) */
    union {
        aout_symbol_table_t        aout_sym;
        elf_section_header_table_t elf_sec;
    } u;

    /* memory mapping, present if flags[6] is set(MEMMAP in init.s) */
    uint32_t mmap_length;
    uint32_t mmap_addr;

    /* drive info, present if flags[7] is set(DRIVE in init.s) */
    uint32_t drives_length;
    uint32_t drives_addr;

    /* ROM configuration table, present if flags[8] is set(CONFIGT in init.s) */
    uint32_t config_table;

    /* boot loader name, present if flags[9] is set(BOOTLDNAME in init.s) */
    uint32_t boot_loader_name;

    /* Advanced Power Management(APM) table, present if flags[10] is set(APMT in init.s) */
    uint32_t apm_table;

    /* video info, present if flags[11] is set(VIDEO in init.s) */
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    /* video framebufer info, present if flags[12] is set(VIDEO_FRAMEBUF in init.s)  */
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;  // indexed = 0, RGB = 1, EGA = 2
} multiboot_info_t;

typedef enum {
    MULTIBOOT_MEMORY_AVAILABLE = 1,
    MULTIBOOT_MEMORY_RESERVED,
    MULTIBOOT_MEMORY_ACPI_RECLAIMABLE,
    MULTIBOOT_MEMORY_NVS,
    MULTIBOOT_MEMORY_BADRAM
} multiboot_memory_type_t;

typedef struct {
    uint32_t size;
    uint32_t addr_low;
    uint32_t addr_high;
    uint32_t len_low;
    uint32_t len_high;
    multiboot_memory_type_t type;
} multiboot_memory_map_t;

#endif // __MULTIBOOT_H_