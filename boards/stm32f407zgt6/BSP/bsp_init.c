/**
  ===========================
  * @file    : bsp_init.c
  * @brief   : 管理所有初始化操作
  * @note    : 为了避免使用表来管理初始化操作, 这里使用 __attribute__((constructor)) 来在程序启动时自动调用。
        由于咱的编译器似乎不支持 __attribute__((constructor(xxx))), 所以在这个文件统一管理, 调整优先级需用手动。
        所以并不适合大型项目。
  ===========================
  */

#include "stm32_init.h"
#include "bsp_exti_dispatch.h"


static void SetDPLow(void *arg)
{
    UNUSED(arg);

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

__attribute__((constructor)) static void EXTI_DFU_Handler_Init(void)
{
    BSP_EXTIHOOK_Register(BSP_EXTI_LINE_15, SetDPLow, NULL);
}

__attribute__((constructor)) static void Peripheral_Init(void)
{
    STM32_CubeMx_Init();
}
