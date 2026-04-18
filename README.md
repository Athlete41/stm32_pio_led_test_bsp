# PIO IDE STM32 BSP 工程模板

## 简介

一个非常简单的 STM32 BSP 工程模板，用于裸机开发。

## 适用环境

| 项目 | 版本/型号 |
|------|-----------|
| 支持芯片 | STM32F103RC、STM32F407ZG |
| IDE | VSCode 1.115.0 + PlatformIO IDE v3.3.4 |
| 辅助工具 | STM32CubeMX 6.17.0 |

> ⚠️ **注意**：
- 仅适用于 CubeMX 生成的裸机工程，不适用于 FreeRTOS 等 RTOS。  
- 关于硬件的初始化在 `BSP/bsp_init.c` 中定义, 其中使用了 __attribute__((constructor)), 确保编译器支持。


## 工作原理

通过脚本处理 CubeMX 生成的代码，将 `Core/**` 目录下的代码解耦分离出初始化代码（复制到同级 `CubeMx_Init` 目录，并做去入口化处理）。

## 默认配置（STM32F407ZG）

| 外设 | 引脚 | 配置 |
|------|------|------|
| LED | PC13 | 推挽输出 |
| 按键 | PA15 | 上拉输入，下降沿中断 |
| 下载器 | PA12 & PA11 | USB DFU |

## 项目目录结构

```
.
├── boards/               # 板级目录
│   └── xxxx/             # 具体板级目录
│       ├── BSP/          # BSP目录 
│       ├── Core/         # CubeMX 生成的代码目录
│       └── CubeMx_Init/  # （临时、编译用）CubeMX 生成的代码目录
├── src/                  # 源代码目录
├── include/              # 头文件目录
├── lib/                  # 库文件目录
├── scripts/              # PlatformIO 脚本目录
└── test/                 # 测试目录
```

## 快速开始
- 使用 CubeMX 配置一个 LED 引脚以及一个按键引脚。
- 修改 `boards/stm32f407zgt6/BSP/bsp_led_test.c` 中的LED引脚为自己配置的引脚。  
- 修改 `boards/stm32f407zgt6/BSP/bsp_init.c` 将中断线改为自己按键对应的。

## 注意事项

- 在使用stm32f407zgt6环境时, 若是保留了跳转DFU功能且使用了看门狗, 则需自行添加关闭看门狗的逻辑防止在模拟拔阶段被狗咬。

