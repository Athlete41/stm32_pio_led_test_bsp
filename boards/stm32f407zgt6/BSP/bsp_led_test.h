/**
  ===========================
  * @file    : bsp_led_test.h
  * @brief   : LED 测试模块所需的相关硬件接口 声明 (STM32F407ZGT6)
  ===========================
  */

#ifndef BSP_LED_TEST_H
#define BSP_LED_TEST_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

/**
 * @brief 设置 LED 状态
 * @param state 0: 关闭, 1: 打开
 */
void BSP_SetLED(uint8_t state);

/**
 * @brief 延时指定毫秒数 （阻塞式）
 * @param ms 延时时间 (毫秒)
 */
void BSP_DelayMs_Block(uint32_t ms);

#endif
