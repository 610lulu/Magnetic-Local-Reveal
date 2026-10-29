# Magnetic Local Reveal

Minimal physical validation for one question:

> Can magnetic proximity produce a clear local light reveal?

接上一个实验（LED实验），README仅展示V2仓库【测试磁性揭示状态是否成功】这一实验的过程：

## 一、KY-024 霍尔传感器接线（3根）

| KY-024引脚 | 连接ESP32 |
| -------- | ------- |
| VCC / +  | 3V3     |
| GND / G  | GND     |
| DO / D0  | GPIO 34 |
| AO       | 不接      |

## 二、原来的KY-016 LED接线（4根）

这部分不用修改：

| KY-016引脚 | 连接ESP32 |
| -------- | ------- |
| R（红）     | GPIO 25 |
| G（绿）     | GPIO 26 |
| B（蓝）     | GPIO 27 |
| GND（−）   | GND     |

如果KY-016已经内置合适的限流电阻，就不用额外添加电阻。

## 三、完整连接关系

<img width="892" height="638" alt="{49FA5030-23CB-445F-B697-E013BA2570D8}" src="https://github.com/user-attachments/assets/adaca3d1-6ab1-4765-9baa-3694deca18d0" />


## 四、接好后的运行

1. 接好线后，用USB连接ESP32和电脑。
2. 在 Arduino IDE 中上传上面的程序。
3. 打开串口监视器，设置为 115200。
4. 用小磁铁靠近KY-024模块。
5. 观察LED是否从暗光变为亮光，移开是否恢复。
如果亮暗反过来了，把代码中的 MAGNET_LEVEL = LOW 改成 HIGH；如果一直不触发，尝试调节KY-024的蓝色电位器，并检查DO信号。
