MEMORY
{
  /* Definición de la memoria física del LPC845 */
  PROGRAM_FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 64K
  SRAM (rwx)         : ORIGIN = 0x10000000, LENGTH = 16K
}

ENTRY(ResetISR)

SECTIONS
{
    /* Vectores de interrupción al inicio de la Flash */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > PROGRAM_FLASH

    /* Datos inicializados que van a la RAM */
    .data : ALIGN(4)
    {
        _data = .;
        *(.data*)
        _edata = .;
    } > SRAM AT> PROGRAM_FLASH

    /* Datos no inicializados (BSS) en RAM */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    _end = .;
}