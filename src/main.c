#include "bsp.h"

int main(void) {
    BSP_Init();

    while (1)
    {
        // 闪烁 LED
        BSP_SetLED(1);
        BSP_DelayMS(1000);
        BSP_SetLED(0);
        BSP_DelayMS(1000);
    }
}