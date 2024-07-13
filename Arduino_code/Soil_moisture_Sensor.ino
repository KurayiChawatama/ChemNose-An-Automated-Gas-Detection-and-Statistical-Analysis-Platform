void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int rawMois = analogRead(A0);
  float percMois = 100.0 - (rawMois / 1023.0 * 100.0);
  Serial.print(percMois);
  Serial.print("% - ");

  if (rawMois >= 1000) {
    Serial.println("Sensor is not in the Soil or DISCONNECTED");
  } else if (rawMois < 1000 && rawMois >= 600) {
    Serial.println("Soil is DRY");
  } else if (rawMois < 600 && rawMois >= 370) {
    Serial.println("Soil is HUMID");
  } else if (rawMois < 370) {
    Serial.println("Sensor in WATER");
  }

  delay(2000);
}
