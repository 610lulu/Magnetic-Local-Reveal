#include <Arduino.h>

// Linear Hall sensor analog output and one LED PWM output.
const int HALL_PIN = 34;
const int LED_PIN = 25;

// Replace these two values after observing the real sensor in Serial Monitor.
int hallFar = 2000;
int hallNear = 3000;

const int MIN_BRIGHTNESS = 30;
const int MAX_BRIGHTNESS = 255;

void setup() {
  Serial.begin(115200);

  pinMode(HALL_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // ESP32 Arduino ADC default is 12-bit (0–4095). Keeping this explicit makes
  // the calibration values easier to interpret when the board is changed.
  analogReadResolution(12);

  Serial.println("Magnetic Local Reveal Test");
  Serial.println("Move the magnet through far, middle, and near positions.");
}

void loop() {
  const int hallValue = analogRead(HALL_PIN);

  // Map the calibrated Hall range to a dim baseline and full brightness.
  int brightness = map(
      hallValue,
      hallFar,
      hallNear,
      MIN_BRIGHTNESS,
      MAX_BRIGHTNESS);

  brightness = constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  analogWrite(LED_PIN, brightness);

  Serial.print("Hall: ");
  Serial.print(hallValue);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(20);
}
