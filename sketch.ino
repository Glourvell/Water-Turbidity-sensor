// ESP32 Turbidity Sensor Test
// Sensor AOUT -> GPIO34

const int turbidityPin = 34;

void setup() {
  Serial.begin(115200);

  // Set ADC resolution to 12-bit (0 - 4095)
  analogReadResolution(12);

  Serial.println("ESP32 Turbidity Sensor Test");
  Serial.println("---------------------------");
}

void loop() {
  int sensorValue = analogRead(turbidityPin);

  // Convert ADC reading to voltage
  float voltage = sensorValue * (3.3 / 4095.0);

  Serial.print("Raw ADC: ");
  Serial.print(sensorValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V");

  Serial.print(" | Water: ");

  if (sensorValue > 3000) {
    Serial.println("Clear");
  }
  else if (sensorValue > 2000) {
    Serial.println("Slightly Cloudy");
  }
  else if (sensorValue > 1000) {
    Serial.println("Cloudy");
  }
  else {
    Serial.println("Very Dirty");
  }

  delay(1000);
}
