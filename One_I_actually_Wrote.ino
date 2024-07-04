int led =  11; // define the LED 's pin number for variable manipulaiton
int brightness = 0; // define the LED's brightness value for variable manipulation
int fadeAmount = 5; // Define how much you want the LED to fade by for the same as above

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;

  if(brightness <=0 || brightness >= 255){
    fadeAmount = -fadeAmount;
  }
  delay(30);
}
