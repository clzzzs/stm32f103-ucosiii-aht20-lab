# STM32F103C8T6 移植 uC/OS-III：多任务点灯与 AHT20 温湿度采集

本仓库是实验四“uC/OS-III 移植与 AHT20 温湿度采集”的完整工程与报告。

GitHub 仓库：<https://github.com/clzzzs/stm32f103-ucosiii-aht20-lab>  
博客地址：<https://blog.csdn.net/2401_89763261/article/details/169743384>

## 项目内容

```text
projects/
├── example_task1/     # 任务一：uC/OS-III + 3 个任务
└── example_task2/     # 任务二：任务一 + AHT20 温湿度采集
report/
├── 实验报告.md
├── 实验报告.pdf
└── images/            # 报告中按出现顺序编号的 19 张图片
LICENSES/              # uC/OS-III、uC/CPU、uC/LIB 的许可证
```

### 任务一

- `led1_task`：优先级 4，每 1 s 翻转 PA5；
- `led2_task`：优先级 5，每 3 s 翻转 PA6；
- `uart_task`：优先级 6，每 2 s 通过 USART1 发送指定字符串。

### 任务二

保留两个 LED 任务，把第 3 个任务改成 `aht20_task`：使用 PB6/PB7 软件 I2C，每 2 s 读取一次 AHT20，并通过 USART1 输出温度和湿度。

## 硬件接线

任务一：

- PA5 → 330 Ω → LED1 → GND；
- PA6 → 330 Ω → LED2 → GND；
- PA9 → USB-TTL RXD，PA10 → USB-TTL TXD；
- ST-Link：3.3V、GND、SWDIO→PA13、SWCLK→PA14；
- ST-Link 与 USB-TTL 的 3.3V 只能接一个，所有 GND 共地。

任务二增加 AHT20：

- 1 脚 VDD → 3.3V；
- 2 脚 SDA → PB7；
- 3 脚 GND → GND；
- 4 脚 SCL → PB6；
- SDA/SCL 若模块没有上拉，各接 4.7 kΩ 到 3.3V。

## 编译

- Keil MDK 5.38；
- ARM Compiler 5.06 update 6（ARMCC 5）；
- STM32F1 HAL V1.8.7；
- uC/OS-III V3.08.02。

打开对应工程：

```text
projects/example_task1/MDK-ARM/example_task1.uvprojx
projects/example_task2/MDK-ARM/example_task2.uvprojx
```

直接 `Build` 即可。仓库中也保留了已编译的 HEX：

```text
projects/example_task1/MDK-ARM/example_task1/example_task1.hex
projects/example_task2/MDK-ARM/example_task2/example_task2.hex
```

## 说明

- 任务一串口字符串使用 GBK 编码，Windows 串口助手可直接显示中文；
- 任务二 AHT20 的 7 位 I2C 地址为 `0x38`，写地址 `0x70`，读地址 `0x71`；
- AHT20 初始化命令为 `0xBE 0x08 0x00`，触发测量命令为 `0xAC 0x33 0x00`；
- uC/OS-III、uC/CPU、uC/LIB 的许可证见 `LICENSES/`。

## 许可证

本仓库中的 uC/OS-III 相关源码遵循其原始 Apache-2.0 许可证；其余实验代码仅用于课程学习。
