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


## Hardware

- ESP32 development board
- Linear (analog-output) Hall sensor
- One LED, or one channel of an RGB LED module
- Current-limiting resistor (typically 220–1kΩ for a single LED)
- Small permanent magnet
- Breadboard and jumper wires

## Pin map

| Function | ESP32 pin |
| --- | ---: |
| Hall sensor analog output | GPIO34 |
| LED PWM output | GPIO25 |
| Sensor and LED ground | GND |
| Sensor supply | 3V3 (check your sensor datasheet) |

GPIO34 is input-only, which makes it suitable for an analog sensor. GPIO25 is used as the PWM output for the LED.

## Run the test

1. Open `firmware/MagneticLocalReveal.ino` in Arduino IDE or PlatformIO.
2. Select an ESP32 board and upload the sketch.
3. Open Serial Monitor at **115200 baud**.
4. Record `Hall` values with the magnet far away, at a middle distance, and very close.
5. Replace `hallFar` and `hallNear` in the sketch with the measured endpoints.
6. Upload again and record a short video: **magnet far → dim**, **magnet close → brighter**, **magnet leaves → dim**.

The code keeps a small baseline glow (`MIN_BRIGHTNESS`) so the LED never disappears completely. If moving the magnet makes the value go down instead of up, swap the `hallFar` and `hallNear` values (or reverse the magnet orientation).

## Expected result

The LED should change continuously as the magnet moves. The useful validation is a repeatable local response, not a precise distance measurement. Different Hall sensors, magnets, supply voltages, and orientations produce different raw ADC ranges, so calibration is required for each physical setup.

## Next step

After this behavior is stable, combine it with the separate `Computational-Respiration` experiment:

```text
Thermal State -> Base LED State
Magnetic proximity -> Local brightness amplification
```

That integration belongs in a later prototype.
