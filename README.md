# Magnetic Local Reveal

Minimal physical validation for one question:

> Can magnetic proximity produce a clear local light reveal?

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
