# GD32E230 Simple Digital Oscilloscope

这是一个基于 GD32E230C8 的简易数字示波器工程库，包含基础外设实验、屏幕显示、波形显示，以及整合后的最终 Demo。

## 目录结构

- `ProjectDemo/`：整理后的 Keil5 工程集合。
  - `ADCDemo`：ADC 采样实验。
  - `PWMDemo`：PWM 输出实验。
  - `InputCaptureDemo`：输入捕获/频率测量实验。
  - `LCDDemo`：LCD 屏幕显示实验。
  - `WaveDemo`：波形显示实验。
  - `FinalDemo`：整合 PWM、输入捕获、LCD、波形显示、ADC、按键、EC11 的最终工程。
- `Demo1-LED控制实验/` 至 `Demo11-屏幕显示实验(DMA)/`：原始分步实验工程。
- `Oscilloscope-V2.0/`、`简易示波器-最终案例/`：示波器完整案例工程。
- `Attachment/`：芯片、LCD、固件库等参考资料和示例源码，已排除安装程序、压缩包和编译产物。

## 推荐入口

最终整合工程：

```text
ProjectDemo/FinalDemo/Project/Template.uvprojx
```

使用 Keil5 打开该工程后，可直接编译生成 `FinalDemo.hex`。当前本地验证结果：

```text
FinalDemo: 0 Error(s), 0 Warning(s)
```

## FinalDemo 功能

- TIMER14 PWM 输出。
- TIMER2 输入捕获频率测量，串口打印频率。
- ADC 通道采样，每 500 ms 串口打印电压。
- LCD 初始化、填充显示和波形绘制。
- 按键控制 LED。
- EC11 旋转方向检测，并通过 LED 和串口反馈。

## 开发环境

- Keil uVision5
- ARM Compiler 6
- GigaDevice GD32E23x_DFP
- MCU：GD32E230C8

## 说明

仓库中保留源码、Keil 工程文件、固件库和必要资料；未提交 Keil 编译输出目录、`.axf/.hex/.o/.map` 等生成文件，也未提交安装程序和压缩包，避免仓库过大或包含机器本地状态。
