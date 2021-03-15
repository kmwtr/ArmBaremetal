/* link.lds */

OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)

MEMORY {
    sram_s(rwx) : ORIGIN = 0xfff80000, LENGTH = 0x00000010    /* start    16B */
    sram_i(rwx) : ORIGIN = 0xfff80010, LENGTH = 0x000003f0    /* init   1008B */
    sram_a(rwx) : ORIGIN = 0xfff80400, LENGTH = 0x0003fc00    /* A     255KiB */
    sram_b(rwx) : ORIGIN = 0xfff00000, LENGTH = 0x00080000    /* B      32KiB */
}

SECTIONS {

    .start : {
        *(.start*)
    } > sram_s

    .init : {
        . = ALIGN(4);
        *(.init*)
    } > sram_i

    .text : {
        . = ALIGN(4);
        *(.text*)
    } > sram_a

    .rodata : { 
        . = ALIGN(4);
        *(.rodata*)
    } > sram_a
    
    .data : {
        . = ALIGN(4);
        *(.data*)
    } > sram_a
    
    .bss : {
        . = ALIGN(4);
        *(.bss*)
    } > sram_a

    /DISCARD/ : {
        *(.comment*)
        *(.ARM.attributes)
    }
}