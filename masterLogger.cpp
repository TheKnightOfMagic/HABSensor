#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

const String LOGFILE = "COMBO.LOG";
const int PINCS = 10; // Pin 10
const int SLAVE_ADDR = 4;

File myFile;

String humidity;
String temp;

void receiveEvent(int howMany);

void setup() {
    Wire.begin(); // join i2c bus as the master muah ha ha
    Wire.onReceive(receiveEvent); // Register recieve event

    Serial.begin(9600); // Start serial for output

    // Writing to
    pinMode(PINCS, OUTPUT);

    // SD card initialization
    if (SD.begin()) {
        Serial.println("SD card is ready to use.");
    } else {
        Serial.println("SD card initialization failed.");

        return;
    }

    myFile = SD.open(LOGFILE.c_str(), FILE_WRITE); // Open the file or create it if it does not exist

    // Check if the file opened okay
    if (myFile) {
        // Yay it opened! now we write data to it
        Serial.println("Writing to file...");
        myFile.println("Data Logging....\nPressure and Temperature"); // Write to the file
        myFile.close(); // Close the file
        Serial.println("File closed.");
    } else {
        Serial.println("error opening " + LOGFILE);
    }
}

void loop() {
    Wire.requestFrom(14, SLAVE_ADDR); // request 15 bytes (two 7 char long numbers and one | seperator) from the slave at address SLAVE_ADDR
    delay(100); // check to see if any new data has been sent after a delay
}

// function that executes whenever data is received from a slave
void receiveEvent(int howMany) {
    char recievedBuff[15];
    int i = 0;

    myFile = SD.open(LOGFILE.c_str(), FILE_WRITE);
    
    while (Wire.available()) { // loop through the incoming data
        char c = Wire.read(); // receive byte as a character

        Serial.print(c); // print the character
        recievedBuff[i] = c; // put the character in the recieved buffer
        i++;
    }

    humidity = String(recievedBuff).substring(0,7);
    temp = String(recievedBuff).substring(8,15);

    myFile.println("Humidiy: " + humidity + " Temp: " + temp);
    myFile.close();
}
