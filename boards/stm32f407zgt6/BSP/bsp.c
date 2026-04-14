/**
  ===========================
  * @file    : bsp.c
  * @brief   : STM32F407ZGT6 BSP 实现
  * @author  : 白狼
  ===========================
  */

#include "bsp.h"
#include "stm32_init.h"


void BSP_Init(void) {
    STM32_Init();
}

void BSP_SetLED(int state) {
    if (state == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    } else if (state == 1) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    }
}

void BSP_DelayMS(int ms) {
    HAL_Delay(ms);
}