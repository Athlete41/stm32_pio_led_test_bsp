/**
  * @file    main.c
  * @brief   主函数文件
  * @note    需要实现以下功能：
  *           - BSP_DelayMs_Block：阻塞式毫秒延时
  *           - BSP_SetLED：设置LED状态
  *           - CDC_Transmit_FS：USB CDC数据发送（可选）
  */

#ifndef TEST_MODE

#include "main.h"

#ifdef USE_USB_CDC
#include "usbd_cdc_if.h"
#endif


int main(void) {
    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);
    
    while (1)
    {
        LEDTest_Blink(500);

        #ifdef USE_USB_CDC
        uint8_t buf[] = "Hello From STM32 PIO + USB CDC!\r\n";
        CDC_Transmit_FS(buf, sizeof(buf));
        #endif
    }
}


#endif