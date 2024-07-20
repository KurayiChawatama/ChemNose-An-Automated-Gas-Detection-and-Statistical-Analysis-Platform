/**
 * @file MQsWSDCard.ino
 * @brief Gas Level Monitoring and Data Logging
 *
 * This sketch is designed for the ChemNose project to automate gas detection and analysis by collecting readings
 * from MQ-135, MQ-4, and MQ-8 sensors and saving the data to an SD card. It focuses on monitoring CO2, CH4, and H2
 * gas levels for environmental monitoring and analysis.
 *
 * @author Kurayi Chawatama
 * @date 2024-07-20
 *
 * @note This code is integral to the ChemNose project's objective of providing a comprehensive environmental
 * monitoring solution. It leverages the Arduino platform and specific gas sensors to gather and log data,
 * facilitating further analysis of gas concentrations in various environments.
 * - The MQ unified sensor library head file was edited to a load resistor of 1k ohms
 *
 * @see For detailed information on the MQUnifiedsensor library and sensor calibration, consult the official
 * documentation and GitHub repository of the MQUnifiedsensor project.
 */

#include <MQUnifiedsensor.h>
#include <SPI.h>
#include <SD.h>

// Sensor Definitions
// MQ-135 for detecting a wide range of gases, including CO2
#define PlacaMQ135 "Arduino UNO"
#define PinMQ135 A0
#define TypeMQ135 "MQ-135"
#define VoltageResolution 5
#define ADCBitResolution 10
#define RatioMQ135CleanAir 3.6

// MQ-4 for detecting methane (CH4) levels
#define BoardMQ4 "Arduino UNO"
#define PinMQ4 A3 // Analog input A3 of your Arduino
#define TypeMQ4 "MQ-4"
#define RatioMQ4CleanAir 4.4

// MQ-8 for detecting hydrogen (H2) gas
#define BoardMQ8 "Arduino UNO"
#define PinMQ8 A1 // Analog input A1 of your Arduino
#define TypeMQ8 "MQ-8"
#define RatioMQ8CleanAir 70
#define AdjustFactorMQ8 100.0 // Adjust factor for MQ-8 output

MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

#define CHIP_SELECT 4 // Define SD card chip select pin

const char *filename = "levels.csv"; // Use a shorter filename for compatibility

unsigned long previousMillis = 0; // Store the last time measurement was made
int seconds = 0; // Initialize seconds counter

void setup() {
  // Serial and SD Card Initialization
  // Initializes serial communication and the SD card module, creating a new CSV file if it doesn't exist.
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");

  if (!SD.exists(filename)) {
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
      dataFile.println("Seconds,CO2_PPM,CH4_PPM,H2_PPM");
      dataFile.close();
      Serial.println("CSV header written.");
    } else {
      Serial.println("Error opening gas_levels.csv to write header");
    }
  } else {
    Serial.println("CSV file already exists.");
  }

  // Sensor Initialization
  // Configures each gas sensor with specific calibration and regression settings.
  MQ135.setRegressionMethod(1); // Using linear regression
  MQ135.setA(110.47); MQ135.setB(-2.862);
  MQ135.init();

  MQ4.setRegressionMethod(1); // Using linear regression
  MQ4.setA(1012.7); MQ4.setB(-2.786);
  MQ4.init();

  MQ8.setRegressionMethod(1); // Using linear regression
  MQ8.setA(976.97); MQ8.setB(-0.688);
  MQ8.init();
}

void loop() {
  // Main Loop
  // Collects readings from each sensor every second, formats the data, and saves it to the SD card.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    seconds++;

    // Reading Gas Levels
    MQ135.update();
    float CO2_PPM = MQ135.readSensor() + 400; // Adjust CO2 PPM to correct offset

    MQ4.update();
    float CH4_PPM = MQ4.readSensor();