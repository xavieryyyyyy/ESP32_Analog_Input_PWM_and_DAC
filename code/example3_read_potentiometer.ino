#include <Arduino.h>

const uint8_t POT_PIN = 4;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
}

void loop() {
  int total = 0;

  // Take 10 readings and add them together
  for (int i = 0; i < 10; i++) {
    total += analogRead(POT_PIN);
    delay(5);
  }

  // Get the average ADC value
  int raw = total / 10;

  // Read voltage in millivolts
  uint32_t millivolts = analogReadMilliVolts(POT_PIN);

  Serial.print("Raw: ");
  Serial.print(raw);

  Serial.print("\tMillivolts: ");
  Serial.println(millivolts);

  delay(300);
}