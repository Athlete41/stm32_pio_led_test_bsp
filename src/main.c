/**
  ===========================
  * @file    : main.c
  * @brief   : 主函数
  ===========================
  */

#ifndef TEST_MODE

#include "led_test.h"
#include "bsp.h"

int main(void) {
    // 初始化外设、时钟等 (cubeMX生成的初始化代码)
    BSP_Peripheral_Init();

    // 初始化LED测试包
    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);
    while (1)
    {
        // 主函数 2s 闪烁一次 
        LEDTest_Blink(1000);
    }
}


#endif