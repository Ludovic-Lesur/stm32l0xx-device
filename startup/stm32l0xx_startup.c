/*
 * stm32l0xx_startup.c
 *
 *  Created on: 19 jan. 2025
 *      Author: ARM
 */

#ifndef STM32L0XX_DEVICE_DISABLE_FLAGS_FILE
#include "stm32l0xx_device_flags.h"
#endif
#include "types.h"

/*** STM32L0XX DEVICE structures ***/

typedef void (*pFunc)(void);

/*** STM32L0XX DEVICE local functions declaration ***/

// Cortex-M0+ interrupts.
void Default_Handler(void);
void Reset_Handler(void);
void NMI_Handler(void)                      __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)                __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)                      __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)                   __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)                  __attribute__ ((weak, alias("Default_Handler")));
// Device interrupts.
void WWDG_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)                   __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler(void)                   __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)                 __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)                   __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_5_6_7_IRQHandler(void)   __attribute__ ((weak, alias("Default_Handler")));
void ADC1_COMP_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler(void)                __attribute__ ((weak, alias("Default_Handler")));
void USART4_5_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void TIM6_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void TIM21_IRQHandler(void)                 __attribute__ ((weak, alias("Default_Handler")));
void I2C3_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void TIM22_IRQHandler(void)                 __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)                __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)                __attribute__ ((weak, alias("Default_Handler")));
void LPUART1_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));

/*** STM32L0XX DEVICE linker variables ***/

extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

/*** STM32L0XX DEVICE local global variables ***/

static uint8_t stack[STM32L0XX_DEVICE_STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));
#if (STM32L0XX_DEVICE_HEAP_SIZE > 0)
static uint8_t heap[STM32L0XX_DEVICE_HEAP_SIZE] __attribute__ ((aligned(8), used, section(".heap")));
#endif
const pFunc __Vectors[] __attribute__ ((section(".vectors"))) = {
    // Cortex-M0+ interrupts.
    (pFunc) ((uint32_t) &__StackTop),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    // Device interrupts.
    WWDG_IRQHandler,
    PVD_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_1_IRQHandler,
    EXTI2_3_IRQHandler,
    EXTI4_15_IRQHandler,
    0,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_3_IRQHandler,
    DMA1_Channel4_5_6_7_IRQHandler,
    ADC1_COMP_IRQHandler,
    LPTIM1_IRQHandler,
    USART4_5_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM6_IRQHandler,
    TIM7_IRQHandler,
    0,
    TIM21_IRQHandler,
    I2C3_IRQHandler,
    TIM22_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    LPUART1_IRQHandler,
    0,
    0
};

/*** STM32L0XX DEVICE functions ***/

/*******************************************************************/
void Reset_Handler(void) {
    // Local variables.
    uint32_t* pSrc;
    uint32_t* pDest;
    // Init RAM.
    pSrc = &__etext;
    pDest = &__data_start__;
    for (; pDest < &__data_end__;) {
        *pDest++ = *pSrc++;
    }
    // Clear BSS section.
    pDest = &__bss_start__;
    for (; pDest < &__bss_end__;) {
        *pDest++ = 0UL;
    }
    // Start application.
    main();
}

/*******************************************************************/
void Default_Handler(void) {
    // Enter sleep mode.
    while (1) {
        __asm volatile ("wfi");
    }
}
