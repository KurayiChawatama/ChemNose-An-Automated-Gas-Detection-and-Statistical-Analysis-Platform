const int mq6Pin = A0;
const int mq2Pin = A1;
int seconds = 0;

void setup() {
  Serial.begin(9600);
  // Print CSV header titles once at the start
  Serial.println("seconds,mq6sensorValue,mq2sensorValue");
}

void loop() {
  int mq6sensorValue = analogRead(mq6Pin);
  int mq2sensorValue = analogRead(mq2Pin);

  Serial.print(seconds);
  Serial.print(",");
  Serial.print(mq6sensorValue);
  Serial.print(",");
  Serial.println(mq2sensorValue);

  seconds = seconds + 1;
  delay(1000);
}
