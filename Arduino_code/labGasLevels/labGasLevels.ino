#include <MQUnifiedsensor.h>
#include <SPI.h>
#include <SD.h>

// MQ-135 Definitions
#define PlacaMQ135 "Arduino UNO"
#define PinMQ135 A0
#define TypeMQ135 "MQ-135"
#define VoltageResolution 5
#define ADCBitResolution 10
#define RatioMQ135CleanAir 3.6

// MQ-4 Definitions
#define BoardMQ4 "Arduino UNO"
#define PinMQ4 A3 // Analog input A3 of your Arduino
#define TypeMQ4 "MQ-4"
#define RatioMQ4CleanAir 4.4

// MQ-8 Definitions
#define BoardMQ8 "Arduino UNO"
#define PinMQ8 A1 // Analog input A1 of your Arduino
#define TypeMQ8 "MQ-8"
#define RatioMQ8CleanAir 70
#define AdjustFactorMQ8 100.0 // Adjust factor for MQ-8 output

MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

#define CHIP_SELECT 4 // Define SD card chip select pin

const char *filename = "levels.csv"; // Use a shorter filename

unsigned long previousMillis = 0; // Store the last time measurement was made
int seconds = 0; // Initialize seconds counter

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  // Initialize the SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");

  // Create or open the file and write the header if it's newly created
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

  // MQ-135 Setup
  MQ135.setRegressionMethod(1);
  MQ135.setA(110.47); MQ135.setB(-2.862);
  MQ135.init();

  // MQ-4 Setup
  MQ4.setRegressionMethod(1);
  MQ4.setA(1012.7); MQ4.setB(-2.786);
  MQ4.init();

  // MQ-8 Setup
  MQ8.setRegressionMethod(1);
  MQ8.setA(976.97); MQ8.setB(-0.688);
  MQ8.init();
}

void loop() {
  // Measure gas levels every second
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    seconds++;

    // MQ-135 Reading
    MQ135.update();
    float CO2_PPM = MQ135.readSensor() + 400; // Adjust CO2 PPM to correct offset

    // MQ-4 Reading
    MQ4.update();
    float CH4_PPM = MQ4.readSensor();

    // MQ-8 Reading
    MQ8.update();
    float H2_PPM = MQ8.readSensor() / AdjustFactorMQ8; // Adjust H2 PPM to display correctly

    // Create a data string in CSV format
    String dataString = String(seconds) + "," + String(CO2_PPM) + "," + String(CH4_PPM) + "," + String(H2_PPM, 2);

    // Open the file
    File dataFile = SD.open(filename, FILE_WRITE);

    // If the file is available, write to it
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // Print to the serial port too
      Serial.println(dataString);
    } else {
      // If the file isn't open, pop up an error
      Serial.println("Error opening gas_levels.csv");
    }
  }
}
