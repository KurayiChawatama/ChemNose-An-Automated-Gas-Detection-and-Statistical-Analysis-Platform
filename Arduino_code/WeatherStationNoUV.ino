#include <MQUnifiedsensor.h>
#include <SPI.h>
#include <SD.h>
#include <Bonezegei_DHT11.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

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
#define AdjustFactorMQ8 100.0 // Adjust factor for MQ-8 output

MQUnifiedsensor MQ135(PlacaMQ135, VoltageResolution, ADCBitResolution, PinMQ135, TypeMQ135);
MQUnifiedsensor MQ4(BoardMQ4, VoltageResolution, ADCBitResolution, PinMQ4, TypeMQ4);
MQUnifiedsensor MQ8(BoardMQ8, VoltageResolution, ADCBitResolution, PinMQ8, TypeMQ8);

#define DHT_PIN 2 // Define DHT11 signal pin
#define CHIP_SELECT 4 // Define SD card chip select pin

Bonezegei_DHT11 dht(DHT_PIN);
ThreeWire myWire(6, 7, 8); // Changed to IO 6, SCLK 7, CE 8
RtcDS1302<ThreeWire> Rtc(myWire);

const char *filename = "day2.csv"; // Use a shorter filename

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize the DHT11 sensor
  dht.begin();
  
  // Initialize the RTC module
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);

  // Initialize the SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  // Create or open the file and write the header if it's newly created
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
  // Get current date and time from RTC
  RtcDateTime now = Rtc.GetDateTime();
  String datetime = getDateTimeString(now);

  // Get data from DHT11 sensor
  if (dht.getData()) { // Get all data from DHT11
    float tempDeg = dht.getTemperature(); // Return temperature in Celsius
    int hum = dht.getHumidity(); // Return humidity

    // MQ-135 Reading
    MQ135.update();
    float CO2_PPM = MQ135.readSensor() + 400; // Adjust CO2 PPM to correct offset

    // MQ-4 Reading
    MQ4.update();
    float CH4_PPM = MQ4.readSensor();

    // MQ-8 Reading
    MQ8.update();
    float H2_PPM = MQ8.readSensor() / AdjustFactorMQ8; // Adjust H2 PPM to display as 0.55 instead of 55

    // Create a data string in CSV format
    String dataString = datetime + "," + String(tempDeg) + "," + String(hum) + "," + String(CO2_PPM) + "," + String(CH4_PPM) + "," + String(H2_PPM, 2);

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
      Serial.println("error opening weather.csv");
    }
  } else {
    // Print an error message if data is not read correctly
    Serial.println(datetime + ",Error reading data from DHT11");
  }

  delay(2000); // Delay at least 2 seconds for DHT11 to read the data
}

String getDateTimeString(const RtcDateTime& dt) {
  char datestring[20];
  snprintf(datestring, sizeof(datestring), "%02u/%02u/%04u %02u:%02u:%02u",
           dt.Month(), dt.Day(), dt.Year(),
           dt.Hour(), dt.Minute(), dt.Second());
  return String(datestring);
}
