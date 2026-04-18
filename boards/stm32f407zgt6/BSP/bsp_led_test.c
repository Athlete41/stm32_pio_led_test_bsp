/**
  ===========================
  * @file    : bsp_led_test.c
  * @brief   : LED 测试模块所需的相关硬件接口 实现 (STM32F407ZGT6)
  * @author  : 白狼
  ===========================
  */

#include "bsp_led_test.h"

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