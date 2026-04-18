/**
  ===========================
  * @file    : bsp_init.c
  * @brief   : 管理所有初始化操作
  * @note    : 为了避免使用表来管理初始化操作, 这里使用 __attribute__((constructor)) 来在程序启动时自动调用。
        由于咱的编译器似乎不支持 __attribute__((constructor(xxx))), 所以在这个文件统一管理, 调整优先级需用手动。
        所以并不适合大型项目。
  * @author  : 白狼
  ===========================
  */

#include "stm32_init.h"



__attribute__((constructor)) static void BSP_Init(void)
{
    STM32_CubeMx_Init();
}
