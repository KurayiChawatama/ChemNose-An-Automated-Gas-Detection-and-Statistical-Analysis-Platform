/**
 * @file noSdMqSensors.ino
 * @brief Gas Concentration Monitoring without SD Card Logging
 *
 * This sketch is designed for the ChemNose project to monitor gas concentrations from MQ-135, MQ-4, and MQ-8 sensors
 * and display the readings of CO2, CH4, and H2 gases on the serial monitor. It operates without the need for an SD card,
 * making it suitable for real-time monitoring or integration into larger systems where data logging is handled elsewhere.
 *
 * The readings are adjusted for offsets and displayed in parts per million (PPM), providing immediate insights into
 * the environmental conditions being monitored. This setup is optimized for quick deployment and testing, offering
 * a streamlined approach to gas detection with the ChemNose project's sensor array.
 *

 * @author Kurayi Chawatama
 * @date 2024-07-20
 *
 * @note This code is a simplified version of the ChemNose project's environmental monitoring suite, focusing on
 * gas concentration measurements without data logging capabilities. It demonstrates the flexibility of the project's
 * hardware and software design, allowing for various configurations based on specific research or operational needs.
 * - The MQ unified sensor library head file was edited to a load resistor of 1k ohms
 * @see For more information on the MQUnifiedsensor library and sensor calibration, consult the official documentation
 * and GitHub repository of the MQUnifiedsensor project.
 */

#include <MQUnifiedsensor.h>

// Sensor Definitions
// MQ-135 for CO2 detection
#define PlacaMQ135 "Arduino UNO"
#define PinMQ135 A0
#define TypeMQ135 "MQ-135"
#define VoltageResolution 5
#define ADCBitResolution 10
#define RatioMQ135CleanAir 3.6

// MQ-4 for CH4 (methane) detection
#define BoardMQ4 "Arduino UNO"
#define PinMQ4 A3 // Analog input A3 of your Arduino
#define TypeMQ4 "MQ-4"
#define RatioMQ4CleanAir 4.4

// MQ-8 for H2 (hydrogen) detection
#define BoardMQ8 "Arduino UNO"
#define PinMQ8 A1 // Analog input A1 of your Arduino
#define TypeMQ8 "MQ-8"
#define RatioMQ8CleanAir 70

// Sensor initialization
MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

void setup() {
  Serial.begin(9600);
  Serial.println("Seconds,CO2_PPM,CH4_PPM,H2_PPM");

  // Sensor setup and calibration
  // MQ-135 Setup
  MQ135.setRegressionMethod(1); // Set linear regression method for more accurate readings
  MQ135.setA(110.47); // Set 'A' parameter of the equation
  MQ135.setB(-2.862); // Set 'B' parameter of the equation
  MQ135.init(); // Initialize the sensor

  // Calibrate MQ-135 and calculate R0 value
  float calcR0MQ135 = 0;
  for (int i = 0; i < 10; i++) {
    MQ135.update(); // Update sensor value
    calcR0MQ135 += MQ135.calibrate(RatioMQ135CleanAir); // Calibrate with clean air ratio
  }
  MQ135.setR0(calcR0MQ135 / 10); // Set the calculated R0

  // Repeat setup and calibration for MQ-4 and MQ-8 sensors
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