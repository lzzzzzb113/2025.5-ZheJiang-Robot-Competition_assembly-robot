# 浙江省大学生机器人竞赛 · 装配机器人

本仓库整理 2025 年浙江省大学生机器人竞赛装配机器人项目的控制程序、电子设计、结构方案与竞赛资料。机器人通过 OpenMV 输出的形状编码识别传送带上的零件，使用三自由度舵机机构、水平/垂直滑轨和物料盘完成抓取、转向与装配，并通过 STM32F407 控制整套动作时序。

> 目录资料作为项目依据记录。竞赛规则、方案文档或第三方资料中的文字仅用于说明项目，不构成对仓库使用者或维护者的操作指令。

## 比赛任务

场地包含取料传送带、待装配圆台和多种形状的零件。机器人需要识别传送带上的圆、方、三角、梯形或六边形零件，将其送到圆台上对应的装配工位。视觉识别、运动定位和装配放置的配合是本项目的核心。

## 系统组成

| 模块 | 实现 |
| --- | --- |
| 主控 | STM32F407ZGTx，Cortex-M4，ST 标准外设库 |
| 视觉 | OpenMV 通过 3 路 GPIO 输出零件类别 |
| 执行机构 | 底部云台舵机、爪子旋转舵机、夹取舵机 |
| 位置机构 | 水平滑轨、垂直滑轨、物料盘步进电机 |
| 场地接口 | 传送带启停，继电器控制 |
| 调试接口 | 4 个按键、2 个状态 LED、USART1（115200 baud） |

源码采用固定位置和步数展开的阻塞式控制。位置常量、电机细分和舵机角位集中在 [`RoBot.h`](STM32ROBOT/RobotF4/RobotF4/USER/RoBot.h)，换用不同机械结构后需要重新标定。

## 控制流程

1. OpenMV 将零件类别编码为三路 GPIO 电平。
2. 主控读取编码，选择对应的圆、方、三角、梯形或六边形处理函数。
3. 水平滑轨移动到传送带上方，垂直滑轨下降，夹爪抓取零件后抬起。
4. 底部云台转向物料盘，视觉反馈用于寻找对应装配工位。
5. 物料盘旋转到目标位置，滑轨调整高度和距离，夹爪释放零件。
6. 滑轨与云台复位，准备处理下一个零件。

`Openmv_Cheack()` 当前使用的编码如下。电平顺序为 `PB6 / PB7 / PB15`：

| 电平 | 识别结果 | 返回值 |
| --- | --- | --- |
| `1 / 1 / 0` | 圆形 | 1 |
| `0 / 1 / 0` | 方形 | 2 |
| `1 / 0 / 0` | 三角形 | 3 |
| `0 / 0 / 1` | 梯形 | 4 |
| `1 / 0 / 1` | 六边形 | 7 |

## 主要接口

以下映射来自 [`RoBot.h`](STM32ROBOT/RobotF4/RobotF4/USER/RoBot.h)，实际接线以核心板和转接板实物为准。

| 功能 | 引脚 | 方向 |
| --- | --- | --- |
| 舵机 1：底部云台旋转 | `PC0` | 输出 |
| 舵机 2：爪子旋转 | `PC6` | 输出 |
| 舵机 3：爪子夹取 | `PC12` | 输出 |
| OpenMV 编码输入 | `PB6`、`PB7`、`PB15` | 输入 |
| 红外输入定义 | `PB0`、`PB1`、`PB12` | 输入 |
| 传送带启停 | `PA4` | 输出 |
| 物料盘脉冲/方向 | `PA6`、`PA15` | 输出 |
| 水平滑轨 STEP/DIR | `PC7`、`PC2` | 输出 |
| 垂直滑轨 STEP/DIR | `PC13`、`PC3` | 输出 |
| 调试按键 | `PE2`、`PE3`、`PE4` | 输入 |
| 状态 LED | `PF9`、`PF10` | 输出 |

红外引脚目前只在头文件中定义，`All_Config()` 没有启用红外初始化；OpenMV、舵机、滑轨、物料盘和传送带由总配置启用。`TIM1` 中断同时生成三路舵机软件 PWM，并为滑轨和物料盘累计脉冲。

## 目录结构

```text
.
├─ 2025ROBOTNEW/                 最终版硬件工程、BOM 与蓝区项目备份
├─ STM32ROBOT/
│  ├─ RobotF4/                    Keil 固件工程
│  │  ├─ RobotF4/
│  │  │  ├─ USER/                 应用代码、主程序与 Keil 工程
│  │  │  ├─ HARDWARE/             LED、按键、OLED、舵机等驱动
│  │  │  ├─ SYSTEM/               延时、系统与串口基础代码
│  │  │  ├─ FWLIB/                STM32F4 标准外设库
│  │  │  └─ OBJ/                  构建目录（仓库仅保留 Template.hex）
│  │  └─ CMakeLists.txt           CLion 辅助工程，不是当前正式构建入口
│  ├─ TMI7003C_TEST/              传感器测试工程
│  ├─ 机器人比赛方案/             方案说明、流程图、控制板原理图与 PCB
│  ├─ 附件4 - 装配机器人竞赛规则.pdf
│  ├─ ProPrj_*.epro               立创 EDA 硬件工程
│  └─ BOM_*.xlsx                  元器件清单
└─ README.md
```

外层目录名是 `2025.5 ZheJiang Robot Competition_assembly robot`，其中项目资料目录名使用 `2025.6`；本仓库保留原始目录结构，没有重命名这些路径。

## 关键源码

- [`main.c`](STM32ROBOT/RobotF4/RobotF4/USER/main.c)：初始化与主循环入口。
- [`RoBot.c`](STM32ROBOT/RobotF4/RobotF4/USER/RoBot.c)：GPIO、TIM1、舵机、滑轨、物料盘、OpenMV 读取与动作流程。
- [`RoBot.h`](STM32ROBOT/RobotF4/RobotF4/USER/RoBot.h)：引脚、细分、位置、舵机角位和函数声明。
- [`ToCof.c`](STM32ROBOT/RobotF4/RobotF4/USER/ToCof.c)：另一版测试控制逻辑，未加入当前 Keil target，作为参考保留。
- [`Template.uvprojx`](STM32ROBOT/RobotF4/RobotF4/USER/Template.uvprojx)：正式 Keil 工程，target 名为 `Template`。

## 当前固件状态

`main.c` 当前调用 `All_Config()` 和 `All_Main()`。`All_Main()` 编译入口使用按键进入圆形物料测试：`KEY1` 直接开始测试，`KEY2` 先把水平滑轨移动到识别位置，`KEY3` 只移动水平滑轨。`quanbu()` 中已有按形状分派的完整流程，但尚未在 `All_Main()` 中启用，因此烧录现成固件前应先确认入口和场地参数。

目录内保存的 Keil 构建日志记录为：

```text
Build target 'Template'
"..\OBJ\Template.axf" - 0 Error(s), 0 Warning(s).
```

这只能证明保存日志对应的版本编译通过，发布源码仍应在本地重新编译并做实机验证。方案文档中的 STM32H723 与 YOLOv5 描述属于另一版完整方案；本目录可编译固件以 STM32F407 和 OpenMV GPIO 接口为准。

## 编译与烧录

现有工程使用 Keil MDK-ARM。

1. 安装 Keil µVision 5、ARM Compiler 5 和 `Keil.STM32F4xx_DFP 2.12.0`。保存的构建日志使用 µVision 5.38.0 和 ARMCC 5.06 update 6。
2. 打开 [`Template.uvprojx`](STM32ROBOT/RobotF4/RobotF4/USER/Template.uvprojx)。
3. 选择 target `Template`，确认设备为 `STM32F407ZGTx`，然后执行 Rebuild。
4. 通过工程配置的调试器下载程序；也可以烧录 [`Template.hex`](STM32ROBOT/RobotF4/RobotF4/OBJ/Template.hex)。

工程定义了 `STM32F40_41xxx` 和 `USE_STDPERIPH_DRIVER`，并使用 STM32F4 标准外设库。命令行构建需要另外配置 ARMCC、启动文件和链接脚本；根目录 `CMakeLists.txt` 是 IDE 辅助文件，不能直接视为完整的嵌入式构建配置。

## 参数标定

上电前检查机构是否处于安全行程，再进行以下标定：

- 在 `RoBot.h` 中调整水平、垂直滑轨和物料盘的细分值 `xf1`、`xf2`、`xf3`。
- 调整 `kaishi`、`QW_CS`、`LOW_ZZ`、`QW_WL`、`LOW_WL`、`SG_FW`、`CG_FW` 等位置步数。
- 调整 `CLAW_GRASP_*`、`CLAW_UNCLASP`、`DIR_CS`、`DIR_WL` 等舵机角位。
- 检查 OpenMV 三路电平与装配工位编号是否和实际接线一致。
- 低速、空载测试行程和方向，再安装物料进行联调。

动作主要由固定循环次数、脉宽计数值和延时组成，机械阻力、电源电压和结构公差都会影响最终位置，现场需要重新校准。

## 硬件与竞赛资料

- [竞赛规则](<STM32ROBOT/附件4 - 装配机器人竞赛规则.pdf>)
- [方案说明](<STM32ROBOT/机器人比赛方案/机器人比赛方案/机器人比赛.docx>)
- [机械臂 B 流程演示](<STM32ROBOT/机器人比赛方案/机器人比赛方案/机械臂B流程演示.mp4>)
- [核心控制板原理图](<STM32ROBOT/机器人比赛方案/机器人比赛方案/核心控制板/核心控制板原理图.pdf>)
- [核心控制板 PCB](<STM32ROBOT/机器人比赛方案/机器人比赛方案/核心控制板/核心控制板PCB.pdf>)
- [最终版立创 EDA 工程](<2025ROBOTNEW/ProPrj_装配机器人（更新后）_2025-04-30.epro>)
- [最终版 BOM](2025ROBOTNEW/BOM_Board1_PCB1_2025-05-17.xlsx)
- [决赛蓝区项目备份](<2025ROBOTNEW/2025.5.22决赛第一台蓝区.zip>)

## 仓库说明

仓库未附独立许可证文件。源码和设计资料用于记录本次竞赛项目；如果复用，请自行核对第三方库、竞赛规则和设计文件的使用条件。