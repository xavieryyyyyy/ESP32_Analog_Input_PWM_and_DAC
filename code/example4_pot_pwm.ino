#include <Arduino.h>

const uint8_t POT_PIN = 4;
const uint8_t PWM_LED_PIN = 5;

bool pwmReady = false;

void setup() {
  Serial.begin(115200);

  // Set ADC resolution to 12 bits
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);

  // Setup LED pin for PWM
  pinMode(PWM_LED_PIN, OUTPUT);
  digitalWrite(PWM_LED_PIN, LOW);

  // Set PWM frequency to 5000 Hz and 8-bit resolution
  pwmReady = ledcAttach(PWM_LED_PIN, 5000, 8);

  if (pwmReady) {
    ledcWrite(PWM_LED_PIN, 0);
  } else {
    Serial.println("PWM setup failed.");
  }
}

void loop() {
  if (!pwmReady) {
    return;
  }

  // Read potentiometer
  int raw = analogRead(POT_PIN);

  // Convert ADC value 0-4095 to PWM value 0-255
  int duty = constrain(map(raw, 0, 4095, 0, 255), 0L, 255L);

  // Change LED brightness
  ledcWrite(PWM_LED_PIN, duty);

  // Display values in Serial Monitor
  Serial.print("Raw: ");
  Serial.print(raw);

  Serial.print("\tPWM Duty: ");
  Serial.println(duty);

  delay(100);
}