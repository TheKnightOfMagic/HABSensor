#include <Adafruit_BMP280.h>



//File Var and imports
#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 10; // Pin 10 on Arduino Uno
//sensor code

Adafruit_BMP280 bmp = Adafruit_BMP280();

void setup()
{
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
  }  // Create/Open file 
  myFile = SD.open("testData.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Data Logging....");
    myFile.println("Pressure and Temperature");

    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 
  //Example Sensor
   String pressure = "Pressure: ";
  String temp = " Temp: ";
  String totalData = String(pressure + bmp.readPressure() + temp + bmp.readTemperature());
  Serial.print("Pressure:    ");
  Serial.print(bmp.readPressure(), 2);
  Serial.print("\tTemperature: ");
  Serial.println(bmp.readTemperature(), 2);
  myFile = SD.open("testData.txt", FILE_WRITE);

  
  myFile.println(totalData);
  myFile.close();
}
