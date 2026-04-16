/**
  ===========================
  * @file    : led_test.c
  * @brief   : LED测试
  ===========================
  */

#include "led_test.h"
#include <stddef.h>
#include <stdlib.h>

static void (*Delay_ms)(uint32_t) = NULL;
static void (*SetLEDState)(uint8_t state) = NULL;

void LEDTest_Init(void (*delay_ms)(uint32_t),
                  void (*setLEDState)(uint8_t state))
{
    Delay_ms = delay_ms;
    SetLEDState = setLEDState;
}

void LEDTest_Blink(uint32_t period_half_ms)
{
    if (!Delay_ms || !SetLEDState)
        return;
    SetLEDState(1);
    Delay_ms(period_half_ms);
    SetLEDState(0);
    Delay_ms(period_half_ms);
}

void LEDTest_BlinkWithDuty(uint32_t high_ms, uint32_t low_ms)
{
    if (!Delay_ms || !SetLEDState)
        return;
    SetLEDState(1);
    Delay_ms(high_ms);
    SetLEDState(0);
    Delay_ms(low_ms);
}

#ifdef LEDTEST_USE_CMSIS_RTOS_V2
#include "cmsis_os2.h"

void vLEDTEST_BlinkTask_CMSIS(void *argument)
{

    ledBlinkParams_t *params = (ledBlinkParams_t *)argument;
    uint32_t          reps = params->repetitions;

    if (!SetLEDState || reps == 0)
    {
        if (argument) free(argument);
        return;
    }

    while (1)
    {
        SetLEDState(1);
        osDelay(params->high_ms);

        SetLEDState(0);
        osDelay(params->low_ms);


        reps--;
        if (reps == 0)
            break;
    }

    SetLEDState(0);

    free(params);
}

#endif /* LEDTEST_USE_CMSIS_RTOS_V2 */
