/**
 * @file weatherStationNoUv.ino
 * @brief Weather Station Data Collection and Analysis without UV Sensor
 *
 * This sketch is part of the ChemNose project, designed to collect environmental data including temperature, humidity,
 * CO2, CH4, and H2 levels using various sensors. The data is logged to an SD card with timestamps for further analysis.
 * This setup aims to monitor and analyze environmental conditions for scientific research and educational purposes.
 *
 * @author Kurayi Chawatama
 * @date 2024-07-20
 *
 * @note This code is a component of the ChemNose project, aimed at creating a versatile and modular environmental
 * monitoring platform. It supports the project's goals by providing detailed environmental data crucial for
 * analyzing gas presence and environmental conditions in various settings.
 * - The MQ unified sensor library head file was edited to a load resistor of 1k ohms

 *
 * @see For more information on the sensors and libraries used, refer to the respective manufacturer's documentation
 * and the GitHub repositories for the MQUnifiedsensor, Bonezegei_DHT11, and RtcDS1302 libraries.
 */

#include <MQUnifiedsensor.h>
#include <SPI.h>
#include <SD.h>
#include <Bonezegei_DHT11.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// Sensor Definitions
// MQ-135 for CO2, MQ-4 for CH4, MQ-8 for H2, DHT11 for temperature and humidity
#define PlacaMQ135 "Arduino UNO"
#define PinMQ135 A0
#define TypeMQ135 "MQ-135"
#define VoltageResolution 5
#define ADCBitResolution 10
#define RatioMQ135CleanAir 3.6

#define BoardMQ4 "Arduino UNO"
#define PinMQ4 A3
#define TypeMQ4 "MQ-4"
#define RatioMQ4CleanAir 4.4

#define BoardMQ8 "Arduino UNO"
#define PinMQ8 A1
#define TypeMQ8 "MQ-8"
#define RatioMQ8CleanAir 70
#define AdjustFactorMQ8 100.0

MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

#define DHT_PIN 2
#define CHIP_SELECT 4

Bonezegei_DHT11 dht(DHT_PIN);
ThreeWire myWire(6, 7, 8);
RtcDS1302<ThreeWire> Rtc(myWire);

const char *filename = "day2.csv";

void setup() {
  // Initialize serial communication, sensors, RTC, and SD card
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Sensor Initialization
  // DHT11 for temperature and humidity
  dht.begin();

  // RTC module for timekeeping
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);

  // SD card for data logging
  Serial.print("Initializing SD card...");
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  if (!SD.exists(filename)) {
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
      dataFile.println("datetime,temperature,humidity,CO2_PPM,CH4_PPM,H2_PPM");
      dataFile.close();
      Serial.println("CSV header written.");
    } else {
      Serial.println("error opening weather.csv to write header");
    }
  } else {
    Serial.println("CSV file already exists.");
  }

  // Gas sensors setup with specific calibration and regression settings