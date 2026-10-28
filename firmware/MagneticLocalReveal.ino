#include <Arduino.h>

// KY-024 霍尔传感器
const int HALL_PIN = 34;

// KY-016 RGB LED 红色通道
const int LED_PIN = 25;

// KY-024 常见为低电平触发
// 如果检测结果相反，改成 HIGH
const int MAGNET_LEVEL = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(HALL_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Magnetic Sensor Ready");
}

void loop() {

  // 检测磁铁是否靠近
  bool magnetNear =
      digitalRead(HALL_PIN) == MAGNET_LEVEL;

  if (magnetNear) {

    // 磁铁靠近：LED变亮
    analogWrite(LED_PIN, 255);
    Serial.println("Magnet Detected");

  } else {

    // 磁铁离开：LED恢复暗光
    analogWrite(LED_PIN, 40);
    Serial.println("No Magnet");

  }

  delay(50);
}
