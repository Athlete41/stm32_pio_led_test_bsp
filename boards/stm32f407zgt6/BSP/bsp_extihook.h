/**
  ===========================
  * @file    : bsp_extihook.h
  * @brief   : 外部中断钩子管理 接口 (STM32F407ZGT6)
  * @note    : 因为STM32常有多个中断复用一个入口，所以需要分发, 这里是个非常简单例子。
  * @note    : 最好在注册钩子时关闭中断，避免极端情况下跑飞，不建议在中断回调中注册
  ===========================
  */

#ifndef BSP_EXTIHOOK_H
#define BSP_EXTIHOOK_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    EXTI_LINE_0 = 0,
    EXTI_LINE_1,
    EXTI_LINE_2,
    EXTI_LINE_3,
    EXTI_LINE_4,
    EXTI_LINE_5,
    EXTI_LINE_6,
    EXTI_LINE_7,
    EXTI_LINE_8,
    EXTI_LINE_9,
    EXTI_LINE_10,
    EXTI_LINE_11,
    EXTI_LINE_12,
    EXTI_LINE_13,
    EXTI_LINE_14,
    EXTI_LINE_15,
    EXTI_LINE_MAX
} extiLine_t;

#define MAX_HOOKS_PER_LINE 5

// 钩子函数类型
typedef void (*extiCallback_t)(void *context);


/**
 * @brief 关闭所有中断
 * @note 关闭所有中断后，需要手动启用中断，否则会导致系统无法正常工作
 * */
void BSP_DisableIRQ(void);

/**
 * @brief 启用所有中断
 * @note 最好在注册钩子时关闭中断，避免极端情况下跑飞，不建议在中断回调中注册
 * */
void BSP_EnableIRQ(void);

/**
 * @brief 注册钩子
 * @param callback 回调函数
 * @param context 用户自定义上下文
 * @return true 成功
 * @return false 失败
 * */
bool BSP_EXTIHOOK_Register(extiLine_t line, extiCallback_t callback,
                           void *context);

/**
 * @brief 注销钩子
 * @param callback 回调函数
 * @param context 用户自定义上下文
 * @return true 成功
 * @return false 失败
 * */
bool BSP_EXTIHOOK_Unregister(extiLine_t line, extiCallback_t callback, void *context);

#endif