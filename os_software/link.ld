SECTIONS
{
    . = 0x80000;     /* Kernel load address for AArch64 */
    .text BLOCK(512) : ALIGN(512) { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata BLOCK(512) : ALIGN(512) { *(.rodata .rodata.* .gnu.linkonce.r*) }
    PROVIDE(_data = .);
    .data BLOCK(512) : ALIGN(512) { *(.data .data.* .gnu.linkonce.d*) }
    .bss BLOCK(512) (NOLOAD) : ALIGN(512) {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }

    /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
    _end = .;

    .pad BLOCK(512) : ALIGN(512) {
        BYTE(0);
        . = ALIGN(512);
    }

}
__bss_size = (__bss_end - __bss_start)>>3;
