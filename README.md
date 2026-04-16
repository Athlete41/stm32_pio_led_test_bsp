# 简介
非常简单的STM32 BSP工程模板  

# 适用环境  
Boards: STM32F103RC、STM32F407ZG  
IDE: vscode 1.115.0 + PIO IDE v3.3.4
其他软件: STM32CubeMX 6.17.0

注意: 仅使用于cubeMX生成的裸机工程，不适用于FreeRTOS等

# 原理
通过脚本将cubeMX生成的代码进行处理，将Core/**目录下的代码解耦分离出初始化代码。(复制到同级Init并且做去入口化处理)