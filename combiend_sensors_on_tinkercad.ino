// Define the pins for sensors
const int irSensorPin = 9;     
const int tempSensorPin = A0;  
const int gasSensorPin = A1;   
const int moistureSensorPin = A2; 
int seconds = 0;

void setup() {
  pinMode(irSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read temperature sensor
  float temperatureSensorValue = analogRead(tempSensorPin);
  float tempVoltage = temperatureSensorValue * (5.0 / 1023.0);
  float temperature = tempVoltage * 100.0;
  
  // Read gas sensor
  float gasSensorValue = analogRead(gasSensorPin);
  float gasVoltage = gasSensorValue * (5.0 / 1023.0);
  float gasPpm = gasVoltage * 200.0;
  
  // Read moisture sensor
  float moistureSensorValue = analogRead(moistureSensorPin);
  float moistureVoltage = moistureSensorValue * (5.0 / 1023.0);
  float moisture = moistureVoltage * 200.0;
  
  // Read IR sensor
  int irSensorValue = digitalRead(irSensorPin);
  
  // Print data in CSV format
  Serial.print(seconds);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(gasPpm);
  Serial.print(",");
  Serial.print(moisture);
  Serial.print(",");
  Serial.println(irSensorValue);

  // Add for the next second
  seconds = seconds + 1;

  delay(1000); // Delay for 1 second between readings
}
