#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <SD.h>
#include <SPI.h>

const String TEMPFILE = "TEMP.LOG"; // Name for the temperature sensor log file
const int PINCS = 10; // Pin 10

File myFile;
Adafruit_BMP280 bmp = Adafruit_BMP280();

float pressure;
float temp;

void setup() {
    Serial.begin(9600); // Start serial for output

    pinMode(PINCS, OUTPUT); // Set pinCS as an output pin (SD card data output)

    // SD card initialization
    if (SD.begin()) {
        Serial.println("SD card is ready to use.");
    } else {
        Serial.println("SD card initialization failed.");

        return;
    }

    myFile = SD.open(TEMPFILE.c_str(), FILE_WRITE); // Open the file or create it if it does not exist

    // Check if the file opened okay
    if (myFile) {
        // Yay it opened! now we write data to it
        Serial.println("Writing to file...");
        myFile.println("Data Logging....\nPressure and Temperature"); // Write to the file
        myFile.close(); // Close the file
        Serial.println("File closed.");
    } else {
        Serial.println("error opening " + TEMPFILE);
    }
}

void loop() {
    pressure = bmp.readPressure();
    temp = bmp.readTemperature();

    String formattedOutput = "Pressure: " +  String(pressure) + " Temp: " + String(temp);
    Serial.println(formattedOutput);

    myFile = SD.open(TEMPFILE.c_str(), FILE_WRITE); // We write the data to the SD card
    myFile.println(formattedOutput);

    myFile.close();
    delay(1000);
}
