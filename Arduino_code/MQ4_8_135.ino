#include <MQUnifiedsensor.h>

// MQ-135 Definitions
#define PlacaMQ135 "Arduino UNO"
#define PinMQ135 A0
#define TypeMQ135 "MQ-135"
#define VoltageResolution 5
#define ADCBitResolution 10
#define RatioMQ135CleanAir 3.6

// MQ-4 Definitions (Changed Pin to A3)
#define BoardMQ4 "Arduino UNO"
#define PinMQ4 A3 // Analog input A3 of your Arduino
#define TypeMQ4 "MQ-4"
#define RatioMQ4CleanAir 4.4

// MQ-8 Definitions
#define BoardMQ8 "Arduino UNO"
#define PinMQ8 A1 // Analog input A1 of your Arduino
#define TypeMQ8 "MQ-8"
#define RatioMQ8CleanAir 70

MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

void setup() {
  Serial.begin(9600);
  Serial.println("Seconds,CO2_PPM,CH4_PPM,H2_PPM");

  // MQ-135 Setup
  MQ135.setRegressionMethod(1);
  MQ135.setA(110.47); MQ135.setB(-2.862);
  MQ135.init();

  float calcR0MQ135 = 0;
  for (int i = 0; i < 10; i++) {
    MQ135.update();
    calcR0MQ135 += MQ135.calibrate(RatioMQ135CleanAir);
  }
  MQ135.setR0(calcR0MQ135 / 10);

  // MQ-4 Setup
  MQ4.setRegressionMethod(1);
  MQ4.setA(1012.7); MQ4.setB(-2.786);
  MQ4.init();

  float calcR0MQ4 = 0;
  for (int i = 0; i < 10; i++) {
    MQ4.update();
    calcR0MQ4 += MQ4.calibrate(RatioMQ4CleanAir);
  }
  MQ4.setR0(calcR0MQ4 / 10);

  // MQ-8 Setup
  MQ8.setRegressionMethod(1);
  MQ8.setA(976.97); MQ8.setB(-0.688);
  MQ8.init();

  float calcR0MQ8 = 0;
  for (int i = 0; i < 10; i++) {
    MQ8.update();
    calcR0MQ8 += MQ8.calibrate(RatioMQ8CleanAir);
  }
  MQ8.setR0(calcR0MQ8 / 10);
}

void loop() {
  // MQ-135 Reading
  MQ135.update();
  float CO2_PPM = MQ135.readSensor();

  // MQ-4 Reading
  MQ4.update();
  float CH4_PPM = MQ4.readSensor();

  // MQ-8 Reading
  MQ8.update();
  float H2_PPM = MQ8.readSensor();

  Serial.print(millis() / 1000); // Print seconds elapsed
  Serial.print(",");
  Serial.print(CO2_PPM + 400); // Adjust CO2 PPM to correct offset
  Serial.print(",");
  Serial.print(CH4_PPM);
  Serial.print(",");
  Serial.println(H2_PPM / 100);

  delay(2000); // Sampling frequency
}
