#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <SD.h>
#define beepPin 5 // digitaler D-Pin 5 für Beeper
#define SERPERATOR ","
const int chipSelect = 27;
#define dustPin A9 // angeschlossen an Pin A9
#define dustLEDPin 4

#define GroundPressureTestCount 10

/*********************** Assign a unique ID to the sensors ****************************/
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
/**************************************************************************************/
/*****************************Global Defines ******************************************/
float groundPressure = 0;
boolean wasAbove50m = false;
float accelX;
float accelY;
float accelZ;
float magX;
float magY;
float magZ;
float gyroX;
float gyroY;
float gyroZ;
float temp;
boolean readGPS = false;
// Dustsensor (2)
int dustValue = 0; // Wert der vom Dust Sensor kommt
float voltage = 0; // errechnete Voltzahl
float dustDensity = 0; // letztendliche Staubkonzentration

/**************************************************************************************/

void setup(){
  Serial.begin(19200);
  for (int i= 16; i < 24; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(beepPin, OUTPUT);
  
  digitalWrite(16, LOW);
  delay (500);
  /* Initialise the sensors */
  if(!accel.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  
  digitalWrite(17, LOW);
  delay (500);
  if(!mag.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  digitalWrite(18, LOW);
  delay (500);
  if(!bmp.begin()) {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  digitalWrite(19, LOW);
  delay (500);
  if(!gyro.begin()) {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  digitalWrite(20, LOW);
  delay (500);
  
  float pressureSum = 0;
  for (int i = 0; i < GroundPressureTestCount; i++) {
    sensors_event_t preshureEvent;
    bmp.getEvent(&preshureEvent); 
    pressureSum += preshureEvent.pressure;
    Serial.print("groundpreshure = ");
    Serial.println (preshureEvent.pressure);
    delay(1000);
  }
  
  groundPressure = pressureSum / GroundPressureTestCount;
  Serial.print("GroundPressure=");
  Serial.println(groundPressure);

  digitalWrite(21, LOW);
  delay (500);
  
  Serial3.begin(9600); // init GPS on Serial3
  Serial3.println("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"); // only CGA output

  digitalWrite(22, LOW);
  delay (500);
  
  
  pinMode(chipSelect, OUTPUT);
  Serial.println("init card");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  File myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("File opened");
    myFile.println("-----------------------------------SNIP----------------------------------");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("File couldnt be opened");
    return;
  }
  
  Serial.println("Card initialised");
  digitalWrite(23, LOW);
  delay (500);
  
  pinMode(dustLEDPin, OUTPUT);
  
  digitalWrite(beepPin, HIGH);
  delay (500);
  
  digitalWrite(beepPin, LOW);  
  
  // switch off all the led to save energy
  for (int i= 16; i < 24; i++) {
    digitalWrite(i, HIGH);
  }
  
}

  
void loop() {
  
  // read out all the sensor values
  sensors_event_t accEvent; 
  accel.getEvent(&accEvent);// get acceleration data
  sensors_event_t magEvent;
  mag.getEvent(&magEvent); // get magnetic vector values
  sensors_event_t gyroEvent;
  gyro.getEvent(&gyroEvent); // get gyrocope values
  sensors_event_t preshureEvent;
  float currentHeight;
  bmp.getEvent(&preshureEvent); // get pressure
  float temperature; // Temp
  bmp.getTemperature(&temperature); // write temp into float
  float pressure = preshureEvent.pressure; // write current pressure to float
  dustDensity = readDustSensor();// read dust value from sensor
  
  float externalTemperature = 99;// read NTC
  float humidity = 111;// read humiditySensor

  // calculate the current height
  currentHeight = bmp.pressureToAltitude(groundPressure,preshureEvent.pressure); // calculating the altitude from pressure
  if (!wasAbove50m && currentHeight > 50) {
    wasAbove50m = true;   
  }
  // check if passed the boarder and switch on beeping if passed
  if (wasAbove50m && currentHeight < 50) {
    digitalWrite(beepPin, HIGH);
    delay (200);
    digitalWrite(beepPin, LOW);  
  }
  
  // read out gps data
  String gpsString = "";
  String temp = "";
  if (!readGPS) {
    temp = GetGGA();
    if (!temp.equals("")) {
      gpsString += temp;
    }
  }
  
  // save all the values
  saveData(currentHeight, accEvent.acceleration.x, accEvent.acceleration.y, accEvent.acceleration.z, magEvent.magnetic.x, magEvent.magnetic.y, magEvent.magnetic.z,
           gyroEvent.gyro.x, gyroEvent.gyro.y, gyroEvent.gyro.z, preshureEvent.pressure, temperature, dustDensity, externalTemperature, humidity, gpsString);

}

float readDustSensor() {
  float currentDustDensity;
  digitalWrite(dustLEDPin, LOW); // switch dust-LED on
  delayMicroseconds (280);
  dustValue=analogRead(dustPin); // read dust value
  delayMicroseconds (40);
  digitalWrite(dustLEDPin, HIGH); // switch dust-LED off
  delayMicroseconds (9680); // cooldown
  voltage = dustValue *0.0048875; // convert Volt to dustValue
  if (voltage <= 3.5) { // nicht Linearität des Sensors beachten
    currentDustDensity = voltage /7.5;
  } else {
    currentDustDensity = (voltage-3.5)*2 +0.4;
  }
  return currentDustDensity;
}

String GetGGA() {
  String gps_output = "";
  boolean GGAready = false;
  boolean start = false;
  int inByte = 0;
  char inChar;
  readGPS = true;
  while (!GGAready) {
    // Serial.println(millis());
    if (Serial3.available()) {
      inChar = Serial3.read();
      inByte = int(inChar);
      //Serial.print(inChar); // Debug Ausgabe
      //Serial.print(inByte); // Debug Ausgabe
      //Serial.print(", "); // Debug Ausgabe
      if (start) {
        if (inByte==13) { 
          GGAready=true;
        } else {
        gps_output += inChar;
        }
      } else { 
        if (inByte==10) {
          start = true;
        }
      }// Ende if (start)
    } // Ende if (available)
  }// Ende while
  readGPS = false;
  return(gps_output);
}


void saveData(float currentHeight, float accelX, float accelY, float accelZ, float magX, float magY, float magZ, float gyroX, float gyroY, float gyroZ,
              float pressure, float temperature, float dustDensity, float externalTemp, float humidity, String gpsString) {

  // open file on SD card              
  File myFile = SD.open("data.txt", FILE_WRITE);
              
  // print all the data to each channel
  printData(currentHeight, myFile);
  printData(SERPERATOR, myFile);
  printData(accelX, myFile);
  printData(SERPERATOR, myFile);
  printData(accelY, myFile);
  printData(SERPERATOR, myFile);
  printData(accelZ, myFile);
  printData(SERPERATOR, myFile);
  printData(magX, myFile);
  printData(SERPERATOR, myFile);
  printData(magY, myFile);
  printData(SERPERATOR, myFile);
  printData(magZ, myFile);
  printData(SERPERATOR, myFile);
  printData(gyroX, myFile);
  printData(SERPERATOR, myFile);
  printData(gyroY, myFile);
  printData(SERPERATOR, myFile);
  printData(gyroZ, myFile);
  printData(SERPERATOR, myFile);
  printData(pressure, myFile);
  printData(SERPERATOR, myFile);
  printData(temperature, myFile);
  printData(SERPERATOR, myFile);
  printData(dustDensity, myFile);
  printData(SERPERATOR, myFile);
  printData(externalTemp, myFile);
  printData(SERPERATOR, myFile);
  printData(humidity, myFile);
  printData(SERPERATOR, myFile);
  printData(gpsString, myFile);  
  endLine(myFile);
  
  // close the file and if ther is a problem report it
  if (myFile) {
    myFile.close();
  } else {
    Serial.println("File couldnt be opened");
    Serial1.println("File couldnt be opened");
  }
}

// print a String to each channel
void printData (String data, File myFile) {
  Serial.print(data);
  Serial1.print(data);
  if (myFile) {
    myFile.print(data);
  }
}

// print a float to each channel
void printData (float data, File myFile) {
  Serial.print(data);
  Serial1.print(data);
  if (myFile) {
    myFile.print(data);
  }
}

// print carriage return to each channel
void endLine (File myFile) {
  Serial.println();
  Serial1.println();
  if (myFile) {
    myFile.println();
  }
}
