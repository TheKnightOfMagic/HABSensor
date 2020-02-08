#include <Arduino.h>
#include <Adafruit_Si7021.h>
#include <Wire.h>

const int SLAVE_ADDR = 4;

Adafruit_Si7021 sensor = Adafruit_Si7021();

char humidityBuff[7];
char tempBuff[7];

void requestSensorData();

void setup() {
    Wire.begin(4); // Join i2c bus as a slave at address 4 (7 bit unsigned integer)
    Wire.onRequest(requestSensorData); // Handle a request for the sensor data

    Serial.begin(9600); // Start serial for output
    Serial.println("Wire has started bish");
}

void loop() {
    delay(100);
}

void requestSensorData() {
    // read temperature and humidity and convert them into ascii chars
    dtostrf(sensor.readHumidity(), 7, 2, humidityBuff);
    dtostrf(sensor.readTemperature(), 7, 2, tempBuff);
    
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(humidityBuff);
    Wire.write("|");
    Wire.write(tempBuff);
    Wire.endTransmission();
}
