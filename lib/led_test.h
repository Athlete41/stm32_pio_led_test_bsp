/**
  ===========================
  * @file    : led_test.h
  * @brief   : LED 头文件
  ===========================
  */

#ifndef LED_TEST_H
#define LED_TEST_H

#include <stdint.h>

/**
 * @brief 初始化 LED 测试模块
 * @param delay_ms   毫秒延时函数指针 (需要阻塞式延时)（裸机环境必须提供；RTOS 环境下可为 NULL，因为任务中使用 osDelay）
 * @param setLEDState LED 状态设置函数指针（必须有效，不能为 NULL）
 *
 * @return 无
 */
void LEDTest_Init(void (*delay_ms)(uint32_t),
                  void (*setLEDState)(uint8_t state));

/**
 * @brief  以指定周期闪烁一次LED
 * @param  period_half_ms: 闪烁周期/2，单位毫秒
 */
void LEDTest_Blink(uint32_t period_half_ms);

/**
 * @brief  以指定高电平时间和低电平时间闪烁一次LED
 * @param  high_ms: 高电平时间，单位毫秒
 * @param  low_ms: 低电平时间，单位毫秒
 */
void LEDTest_BlinkWithDuty(uint32_t high_ms, uint32_t low_ms);


#ifdef LEDTEST_USE_CMSIS_RTOS_V2
#include "cmsis_os2.h"

/**
 * @brief  LED 测试任务参数结构体定义 CMSIS-RTOS V2
 * @param  high_ms: 高电平时间，单位毫秒
 * @param  low_ms:  低电平时间，单位毫秒
 * @param  repetitions: 闪烁次数, 0 表示立即返回
 */
typedef struct
{
    uint32_t high_ms;
    uint32_t low_ms;
    uint32_t repetitions;
} ledBlinkParams_t;

#endif

#endif /* LED_TEST_H */
