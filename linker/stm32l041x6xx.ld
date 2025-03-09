/*
 * stm32l041x6xx.ld
 *
 *  Created on: 19 jan. 2025
 *      Author: ARM
 */

MEMORY
{
    FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    RAM    (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
    EEPROM (rw)  : ORIGIN = 0x08080000, LENGTH = 1K
}

__eeprom_address__ = ORIGIN(EEPROM);
__eeprom_size_bytes__ = LENGTH(EEPROM);

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        KEEP(*(.ResetHandler))
        KEEP(*(.DefaultHandler))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        KEEP(*(.eh_frame*))
    } > FLASH

    .ARM.extab (READONLY) :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx (READONLY) :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    __etext = .;

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(vtable)
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    .heap (COPY):
    {
        __HeapBase = .;
        __end__ = .;
        end = __end__;
        KEEP(*(.heap*))
        __HeapLimit = .;
    } > RAM

    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (COPY):
    {
        KEEP(*(.stack*))
    } > RAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
