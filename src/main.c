/**
  ===========================
  * @file    : main.c
  * @brief   : 主函数
  * @author  : 白狼
  ===========================
  */

#include "bsp.h"

#ifndef TEST_MODE

int main(void) {
    BSP_Init();

    while (1)
    {
        /** 闪烁 LED */
        BSP_SetLED(1);
        BSP_DelayMS(1000);
        BSP_SetLED(0);
        BSP_DelayMS(1000);
    }
}

#endif