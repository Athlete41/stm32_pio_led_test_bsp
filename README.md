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


## CubeMX 与 PIO IDE 的配合

通过脚本处理 CubeMX 生成的代码，将 `Core/**` 目录下的代码解耦分离出初始化代码（复制到同级 `CubeMX_Init` 目录，并做去入口化处理）。

## 默认配置（STM32F407ZG）

| 外设 | 引脚 | 配置 |
|------|------|------|
| LED | PC13 | 推挽输出 |
| 按键 | PA15 | 上拉输入，下降沿中断 |
| USB OTG | PA12、PA11 | 默认全速 |


RCC 配置：使用HSE、LSE，无源晶振，具体配置在 `boards\stm32f407zgt6\stm32f407zgt6.ioc` 中。

## 项目目录结构

```
.
├── boards/               # 板级目录
│   └── xxxx/             # 具体板级目录
│       ├── Core/         # CubeMX 生成的代码目录
│       └── CubeMX_Init/  # （临时、编译用）CubeMX 生成的代码目录
│       └── xxx/          # 其他目录
├── src/                  # 源代码目录
├── include/              # 头文件目录
├── lib/                  # 库文件目录
├── scripts/              # PlatformIO 脚本目录
└── test/                 # 测试目录
```
- 这里规定根目录的src、include、lib目录放置业务代码、模块。
- 板级目录下，除了Core、CubeMX_Init等固定目录，其他目录随便，用于提供业务代码、模块所需的接口或是具体硬件初始化代码。
- 这里有一些不足之处，比如有个环境需要一个和业务无关的特殊功能，而这个特殊功能由于硬件架构的原因必须在业务的main中调用，这就需要提供一个全局表，我们在板级目录就可以将其插入表中，这里没有，就用编译宏吧。

## 快速开始
- 使用 CubeMX 配置一个 LED 引脚以及一个按键引脚。
- 修改 `boards/stm32f407zgt6/BSP/bsp_led_test.c` 中的LED引脚为自己配置的引脚。  
- 修改 `boards/stm32f407zgt6/BSP/bsp_init.c` 将中断线改为自己按键对应的。


