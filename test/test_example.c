/**
  ===========================
  * @file    : test_example.c
  * @brief   : 测试示例, 使用全局宏 TEST_MODE & TEST_EXAMPLE
  ===========================
  */

#if defined(TEST_MODE) && defined(TEST_EXAMPLE)

#include "main.h"


int main(void) {
    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);
    
    while (1)
    {
        LEDTest_Blink(100);
    }
}


#endif