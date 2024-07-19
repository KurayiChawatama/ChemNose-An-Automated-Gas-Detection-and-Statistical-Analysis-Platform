void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);   // Set analog pin A0 as input for moisture sensor
}

void loop() {
  int rawMois = analogRead(A0);  // Read analog input from moisture sensor (0-1023)
  
  // Convert raw sensor reading to percentage moisture
  float percMois = 100.0 - (rawMois / 1023.0 * 100.0);
  
  // Print moisture percentage to serial monitor
  Serial.print(percMois);
  Serial.print("% - ");

  // Determine soil moisture level based on raw sensor reading
  if (rawMois >= 1000) {
    Serial.println("Sensor is not in the Soil or DISCONNECTED");
  } else if (rawMois < 1000 && rawMois >= 600) {
    Serial.println("Soil is DRY");
  } else if (rawMois < 600 && rawMois >= 370) {
    Serial.println("Soil is HUMID");
  } else if (rawMois < 370) {
    Serial.println("Sensor in WATER");
  }

  delay(2000);  // Delay for 2 seconds before taking next reading
}
