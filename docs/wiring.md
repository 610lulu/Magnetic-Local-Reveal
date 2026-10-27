# Wiring

This wiring is for a single analog Hall sensor and one LED on an ESP32.

## Hall sensor

Check the pin labels and voltage requirements on the exact sensor module before powering it.

| Sensor pin | ESP32 |
| --- | --- |
| VCC | 3V3 (unless the datasheet specifies another safe supply) |
| GND | GND |
| AO / OUT | GPIO34 |

Use the sensor's **analog output**. A digital-only Hall switch gives only an on/off signal and cannot demonstrate a gradual brightness response.

## LED

For a bare LED:

```text
GPIO25 ---- resistor (220–1kΩ) ---- LED anode (+)
GND -------------------------------- LED cathode (-)
```

If using an RGB LED module, connect GPIO25 through the resistor to one color channel and connect the module's common pin according to its datasheet. Start with one channel only.

## Calibration procedure

1. Upload the sketch with the example `hallFar` and `hallNear` values.
2. Open Serial Monitor at 115200 baud.
3. Hold the magnet far away and note the stable `Hall` value.
4. Move it to a middle distance and note the value.
5. Hold it close and note the stable value.
6. Set `hallFar` to the far reading and `hallNear` to the close reading.
7. If the close reading is lower than the far reading, swap the two constants or reverse the magnet orientation.

The values are sensor- and orientation-specific; the example numbers are placeholders only.
