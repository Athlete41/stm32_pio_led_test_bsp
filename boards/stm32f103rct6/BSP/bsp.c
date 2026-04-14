// 实现 BSP 接口

#include "bsp.h"
#include "stm32_init.h"

void BSP_Init(void)
{
    STM32_Init();
}

void BSP_SetLED(int state) {
    if (state == 0) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
    } else if (state == 1) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
    }
}

void BSP_DelayMS(int ms) {
    HAL_Delay(ms);
}