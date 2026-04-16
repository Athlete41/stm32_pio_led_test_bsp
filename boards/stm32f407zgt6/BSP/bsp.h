/**
  ===========================
  * @file    : bsp.h
  * @brief   : BSP 接口 (STM32F407ZGT6)
  ===========================
  */

#ifndef BSP_H
#define BSP_H

#include <stdint.h>
/**
 * @brief 初始化单片机外设等配置
 *
 */
void BSP_Peripheral_Init(void);

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
