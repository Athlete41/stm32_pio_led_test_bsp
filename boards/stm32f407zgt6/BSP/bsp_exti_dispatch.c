/**
  ===========================
  * @file    : bsp_exti_dispatch.c
  * @brief   : 外部中断分发器 (STM32F407ZGT6)
  * @note    : 这里是个非常简单例子, 没有提供优先级参数
  ===========================
  */

#include "bsp_exti_dispatch.h"
#include "stm32f4xx_hal.h"
#include <stddef.h>
#include <string.h>


// 钩子节点
typedef struct {
    extiCallback_t callback;
    void *context;
    bool active;
} exti_hook_t;

// 每个中断线的钩子表
static exti_hook_t extiHookTable[BSP_EXTI_LINE_MAX][MAX_HOOKS_PER_LINE];



void BSP_DisableIRQ(void) {
    __disable_irq();
}

void BSP_EnableIRQ(void) {
    __enable_irq();
}



bool BSP_EXTIHOOK_Register(extiLine_t line, extiCallback_t callback, void *context) {
    if (line >= BSP_EXTI_LINE_MAX || callback == NULL) return false;


    // 检查是否已存在相同的 (callback, context)
    for (int i = 0; i < MAX_HOOKS_PER_LINE; i++) {
        if (extiHookTable[line][i].active &&
            extiHookTable[line][i].callback == callback &&
            extiHookTable[line][i].context == context) {
            return true; // 已存在，视为成功 
        }
    }

    // 找空闲槽位
    for (int i = 0; i < MAX_HOOKS_PER_LINE; i++) {
        if (!extiHookTable[line][i].active) {
            extiHookTable[line][i].callback = callback;
            extiHookTable[line][i].context = context;
            extiHookTable[line][i].active = true;
            return true;
        }
    }

    return false;
}

bool BSP_EXTIHOOK_Unregister(extiLine_t line, extiCallback_t callback, void *context)
{
    if (line >= BSP_EXTI_LINE_MAX || callback == NULL) return false;
    
    for (int i = 0; i < MAX_HOOKS_PER_LINE; i++) {
        if (extiHookTable[line][i].active && 
            extiHookTable[line][i].callback == callback &&
            extiHookTable[line][i].context == context) {
            
            extiHookTable[line][i].active = false;
            
            return true;
        }
    }
    return false;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    extiLine_t line;
    switch (GPIO_Pin) {
        case GPIO_PIN_0:  line = BSP_EXTI_LINE_0; break;
        case GPIO_PIN_1:  line = BSP_EXTI_LINE_1; break;
        case GPIO_PIN_2:  line = BSP_EXTI_LINE_2; break;
        case GPIO_PIN_3:  line = BSP_EXTI_LINE_3; break;
        case GPIO_PIN_4:  line = BSP_EXTI_LINE_4; break;
        case GPIO_PIN_5:  line = BSP_EXTI_LINE_5; break;
        case GPIO_PIN_6:  line = BSP_EXTI_LINE_6; break;
        case GPIO_PIN_7:  line = BSP_EXTI_LINE_7; break;
        case GPIO_PIN_8:  line = BSP_EXTI_LINE_8; break;
        case GPIO_PIN_9:  line = BSP_EXTI_LINE_9; break;
        case GPIO_PIN_10: line = BSP_EXTI_LINE_10; break;
        case GPIO_PIN_11: line = BSP_EXTI_LINE_11; break;
        case GPIO_PIN_12: line = BSP_EXTI_LINE_12; break;
        case GPIO_PIN_13: line = BSP_EXTI_LINE_13; break;
        case GPIO_PIN_14: line = BSP_EXTI_LINE_14; break;
        case GPIO_PIN_15: line = BSP_EXTI_LINE_15; break;
        default: return;
    }
    
    for (int i = 0; i < MAX_HOOKS_PER_LINE; i++) {
        if (extiHookTable[line][i].active) {
            extiHookTable[line][i].callback(extiHookTable[line][i].context);
        }
    }
}


