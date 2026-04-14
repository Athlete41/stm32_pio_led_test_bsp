/**
  ===========================
  * @file    : test_example.c
  * @brief   : 测试示例, 使用全局宏 TEST_MODE & TEST_EXAMPLE
  * @author  : 白狼
  ===========================
  */

#if defined(TEST_MODE) && defined(TEST_EXAMPLE)

#include "bsp.h"

int main(void) {
    BSP_Init();
    
    while(1) 
    {
        /* 测试代码 */
        BSP_SetLED(1);
        BSP_DelayMS(100);
        BSP_SetLED(0);
        BSP_DelayMS(100);
    }
}

#endif