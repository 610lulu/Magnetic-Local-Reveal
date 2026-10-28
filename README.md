# Magnetic Local Reveal

Minimal physical validation for one question:

> Can magnetic proximity produce a clear local light reveal?

#接上一个实验
## 一、KY-024 霍尔传感器接线（3根）

[KY-024 Linearer, magnetischer Hall-Sensor | Joy-IT](https://images.openai.com/static-rsc-4/KqlX6Eu6Kp1mjB0EO69RHK0R3yiow4-uUKvCflT88fGVjo5qr7I0ZPBChDTrVTTzNHd7TUdFz3nWA89pzVPtFPJKNO0aRtdbNN9U0wZUx0DrAWQ4xuwh8bksWE2ksVvuuiEToCErakGiLegP4KdEr5SlJ0swoPsBQraDSes5Wwk?purpose=inline)

| KY-024引脚 | 连接ESP32 |
| -------- | ------- |
| VCC / +  | 3V3     |
| GND / G  | GND     |
| DO / D0  | GPIO 34 |
| AO       | 不接      |

注意：按照模块实际印刷的引脚名称连接，不要根据照片猜测引脚顺序。

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

逻辑连接示意，不代表真实板上的引脚物理位置。两块模块共用ESP32的GND。

## 四、接好后怎么运行？

1. 断开USB电源，按上面的表格接好线。
2. 检查没有接错3V3和GND，再连接USB。
3. Arduino IDE上传上一条给你的简化版数字霍尔程序。
4. 用一块小磁铁靠近KY-024，观察LED是否变亮，移开后是否变暗。

特别提醒：你 [Magnetic-Local-Reveal 仓库](https://github.com/610lulu/Magnetic-Local-Reveal?utm_source=chatgpt.com)里目前还是读取 `analogRead()` 的旧程序。使用KY-024的DO引脚时，要换成上一条的 `digitalRead()` 简化代码。

如果磁铁靠近后没有反应，先调节KY-024上的蓝色小旋钮，并检查数字触发电平是否需要从 `HIGH` 改成 `LOW`。

最终效果：磁铁远离 → LED暗；磁铁靠近 → LED亮。 这就完成你的第二阶段磁感应触发验证。
The test maps a **linear Hall sensor** reading to the brightness of one LED:

```text
magnet far away  ->  lower Hall reading  ->  dim baseline
magnet approaches ->  stronger reading    ->  brighter LED
magnet leaves     ->  LED returns to dim baseline
```

This repository intentionally tests only **magnetic proximity → LED brightness**. It does not include Thermal State, multiple LEDs, or spatial propagation. Those can be integrated after this single-channel behavior is physically verified.

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
