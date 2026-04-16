/**
  ===========================
  * @file    : test_example.c
  * @brief   : 测试示例, 使用全局宏 TEST_MODE & TEST_EXAMPLE
  ===========================
  */

#if defined(TEST_MODE) && defined(TEST_EXAMPLE)

#include "led_test.h"
#include "bsp.h"

int main(void) {
    BSP_Peripheral_Init();

    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);
    while (1)
    {
        // 测试代码 200ms 闪烁一次
        LEDTest_Blink(100);
    }
}


#endif