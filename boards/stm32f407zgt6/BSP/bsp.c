/**
  ===========================
  * @file    : bsp.c
  * @brief   : BSP 实现 (STM32F407ZGT6)
  ===========================
  */

#include "bsp.h"
#include "stm32_init.h"

void BSP_Peripheral_Init(void)
{
    STM32_Init();
}

void BSP_SetLED(uint8_t state)
{
    if (state)
        state = GPIO_PIN_SET;
    else
        state = GPIO_PIN_RESET;

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state);
}

void BSP_DelayMs_Block(uint32_t ms)
{
    HAL_Delay(ms);
}