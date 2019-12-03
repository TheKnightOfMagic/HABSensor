// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

//sensor code
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();


void setup()
{
  while (!Serial) {
    delay(10);
  }
  Serial.begin(9600);
    Serial.println("Wire has started bish");

  Wire.begin(); // join i2c bus (address optional for master)
}

int x = 0;

void loop()
{
  String hum = "Humidity: ";
  String temp = " Temp: ";
  String dataCombo = String(hum + sensor.readHumidity() + temp + sensor.readTemperature());
  Serial.print("Humidity:    ");
  Serial.print(sensor.readHumidity(), 2);
  Serial.print("\tTemperature: ");
  Serial.println(sensor.readTemperature(), 2);
  Wire.beginTransmission(4); // transmit to device #4
  //Wire.write("Humidity | Temperature");        // sends five bytes
  Wire.write(String(dataCombo).c_str());   
  Wire.write(x);
  Wire.endTransmission();    // stop transmitting

  delay(100);
}

