/**
  ===========================
  * @file    : main.c
  * @brief   : 主函数
  * @author  : 白狼
  ===========================
  */

#ifndef TEST_MODE

#include "main.h"

int main(void) {
    // 初始化LED测试包
    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);
    
    while (1)
    {
        // 主函数 2s 闪烁一次 
        LEDTest_Blink(1000);
    }
}


#endif