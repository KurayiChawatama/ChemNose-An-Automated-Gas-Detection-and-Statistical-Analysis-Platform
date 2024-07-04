void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Set the LED pins as outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // Turn on the LEDs
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}

void loop() {
  // Read the input on analog pin A0 and A1
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);

  // Convert the analog readings (which go from 0 - 1023) to voltage (0 - 5V)
  float voltage1 = sensorValue1 * (5.0 / 1023.0);
  float voltage2 = sensorValue2 * (5.0 / 1023.0);

  // Print out the voltage readings
  Serial.print("Voltage across LED 1: ");
  Serial.print(voltage1);
  Serial.println(" V");

  Serial.print("Voltage across LED 2: ");
  Serial.print(voltage2);
  Serial.println(" V");

  // Wait for a bit before the next loop
  delay(1000);
}
