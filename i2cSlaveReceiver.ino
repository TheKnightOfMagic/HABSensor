// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//I2C
#include <Wire.h>

//File Var and imports
#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 10; // Pin 10 on Arduino Uno

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  
  //Writing to
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("testData.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Data Logging....");
    myFile.println("Temperature, Pressure, Altitude");

    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  String totalData = "";
  myFile = SD.open("testData.txt", FILE_WRITE);
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    totalData = totalData + c;
  
  }
  
  byte x = Wire.read();    // receive byte as an integer
  Serial.println(x);
  myFile.println(totalData);
  myFile.close();
}
