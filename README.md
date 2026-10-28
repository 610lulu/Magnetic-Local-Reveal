# Magnetic Local Reveal

Minimal physical validation for one question:

> Can magnetic proximity produce a clear local light reveal?

#接上一个实验
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


## 四、接好后怎么运行？

1. 断开USB电源，按上面的表格接好线。
2. 检查没有接错3V3和GND，再连接USB。
3. Arduino IDE上传上一条给你的简化版数字霍尔程序。
4. 用一块小磁铁靠近KY-024，观察LED是否变亮，移开后是否变暗。
