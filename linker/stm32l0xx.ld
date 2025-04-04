/*
 * stm32l0xx.ld
 *
 *  Created on: 04 apr. 2025
 *      Author: ARM
 */

MEMORY
{
    FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = __flash_size__
    RAM    (rwx) : ORIGIN = 0x20000000, LENGTH = __ram_size__
    EEPROM (rw)  : ORIGIN = 0x08080000, LENGTH = __eeprom_size__
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

    __flash_end__ = ALIGN(4);

    .data : AT(__flash_end__)
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(vtable)
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    .heap (COPY) :
    {
        __heap_start__ = .;
        KEEP(*(.heap*))
        __heap_end__ = .;
    } > RAM

    .stack (COPY) :
    {
        KEEP(*(.stack*))
    } > RAM

    __stack_top__ = ORIGIN(RAM) + LENGTH(RAM);
    __stack_limit__ = __stack_top__ - SIZEOF(.stack);

    ASSERT((__stack_limit__ >= __heap_end__), "Region RAM overflowed with stack")
}