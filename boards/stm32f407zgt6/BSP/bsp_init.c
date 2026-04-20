/**
  ===========================
  * @file    : bsp_init.c
  * @brief   : 管理所有初始化操作
  * @note    : 为了避免使用表来管理初始化操作, 这里使用 __attribute__((constructor)) 来在程序启动时自动调用。
        由于咱的编译器似乎不支持 __attribute__((constructor(xxx))), 所以在这个文件统一管理, 调整优先级需用手动。
        所以并不适合大型项目。
  ===========================
  */

#include "stm32_init.h"
#include "bsp_exti_dispatch.h"
#include "bsp_led_test.h"


// 模拟 USB 断开连接
static void USB_Emulate_Disconnect(void *arg)
{
    UNUSED(arg);

    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    // 2. 关闭 USB 设备模式下的 D+ 上拉电阻（直接使用 USB_OTG_FS 宏）
    USB_OTG_FS->GCCFG &= ~USB_OTG_GCCFG_PWRDWN;   // 清除 PWRDWN 位（关闭内部上拉）
    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBUSASEN;  // 可选：禁用 VBUS 检测
    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBUSBSEN;

    // 3. 软复位 USB 模块
    USB_OTG_FS->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
    BSP_DelayMS_NOP(1);
    USB_OTG_FS->GRSTCTL &= ~USB_OTG_GRSTCTL_CSRST;

    // 4. 关闭 USB 时钟
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);


    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    for (int i = 0; i < 2; i++)
    {
        BSP_SetLED(1);
        BSP_DelayMS_NOP(10);
        BSP_SetLED(0);
        BSP_DelayMS_NOP(10);
    }

    while (1) {}
}


// 按键模拟 USB 断开连接，这是为我那操蛋的DFU下载方式准备的
__attribute__((constructor)) static void EXTI_DFU_Handler_Init(void)
{
    BSP_EXTIHOOK_Register(BSP_EXTI_LINE_15, USB_Emulate_Disconnect, NULL);
}

__attribute__((constructor)) static void Peripheral_Init(void)
{
    STM32_CubeMX_Init();
}

// __attribute__((constructor)) static void SystemCoreClock_Update(void)
// {
//     SystemCoreClockUpdate();
// }
