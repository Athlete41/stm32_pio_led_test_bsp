/**
  ===========================
  * @file    : test_cdc_loss_test.c
  * @brief   : 测试CDC数据丢失, 使用全局宏 TEST_MODE & TEST_CDC_LOSS & USE_USB_CDC
  * @note    : 不停发送递增数列, 在上位机解析数据是否丢失。
  ===========================
  */

#if defined(TEST_MODE) && defined(TEST_CDC_LOSS) && defined(USE_USB_CDC)

#include "usbd_cdc_if.h"
#include "main.h"

#define DELAY_MS 10
#define BATCH_SIZE 1024

int main(void) {
    LEDTest_Init(BSP_DelayMs_Block, BSP_SetLED);

    uint32_t counter = 0;
    uint32_t buffer[BATCH_SIZE];

    while (1)
    {
        #if DELAY_MS > 0
        LEDTest_Blink(DELAY_MS / 2);
        #endif

        for (uint32_t i = 0; i < BATCH_SIZE; i++)
        {
            buffer[i] = counter++;
        }

        CDC_Transmit_FS((uint8_t*)buffer, sizeof(uint32_t) * BATCH_SIZE);
    }
}


#endif