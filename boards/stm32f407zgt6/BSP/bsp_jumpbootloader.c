/**
  ===========================
  * @file    : bsp_jumpbootloader.c
  * @brief   : 跳转系统BootLoader 
  ===========================
  */
 
#include "bsp_jumpbootloader.h"

#define BOOTLOADER_VECTOR_TABLE_BASE  0x1FFF0000
#define BOOTLOADER_ENTRY  BOOTLOADER_VECTOR_TABLE_BASE + 4

static void JumpToBootloader(void) {
    void (*SysMemBootJump)(void);

    __disable_irq();

    // 关闭 SysTick
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    // 复位 RCC 并关闭所有外设时钟（HAL 方式）
    HAL_RCC_DeInit();

    // 关闭所有外设的时钟使能
    // __HAL_RCC_GPIOA_CLK_DISABLE(); ...

    // 清除所有 NVIC 中断使能与挂起
    for (int i = 0; i < 8; i++) {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }

    // 清除可能的 fault 状态（可选）
    SCB->SHCSR = 0;

    // 设置 MSP 和 CONTROL
    __set_MSP(*(uint32_t *)BOOTLOADER_VECTOR_TABLE_BASE);
    __set_CONTROL(0);

    // 设置 VTOR
    // SCB->VTOR = BOOTLOADER_VECTOR_TABLE_BASE;

    // 数据屏障与相关缓存处理
    __DSB();
    __ISB();

    // 跳转
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(BOOTLOADER_ENTRY)));
    SysMemBootJump();

    while (1);
}


#define DELAY_US_CYCLES (SystemCoreClock / 1000000)
static void Delay_us(uint32_t us) {
    uint32_t cycles = us * DELAY_US_CYCLES;
    while(cycles--) __NOP();
}

static void Delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
        Delay_us(1000);
    }
}

static void SetDPLow(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


static void JumpToBootloaderDFU(void)
{
    __disable_irq();

    // 模拟USB插拔
    SetDPLow();
    delay_ms(200);

    JumpToBootloader();
}

