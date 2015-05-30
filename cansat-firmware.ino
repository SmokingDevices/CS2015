#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "DHT.h"
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <SD.h>
#define DHTPIN 8
#define DHTTYPE DHT11
#define beepPin 5 // digitaler D-Pin 5 für Beeper
#define SERPERATOR ","
const int chipSelect = 27;
#define dustPin A9 // angeschlossen an Pin A9
#define dustLEDPin 2
/*********************** Assign a unique ID to the sensors ****************************/
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
/**************************************************************************************/
/*****************************Global Defines ******************************************/
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
float x2 = 0;
float x1 = 0;
float accelX;
float accelY;
float accelZ;
float magX;
float magY;
float magZ;
float gyroX;
float gyroY;
float gyroZ;
float pressureGlobal;
float temp;
float realhight;
boolean ermittleGPS = false;
// Dustsensor (2)
int dustValue = 0; // Wert der vom Dust Sensor kommt
float voltage = 0; // errechnete Voltzahl
float dustDensity = 0; // letztendliche Staubkonzentration
/**************************************************************************************/
DHT dht(DHTPIN, DHTTYPE);

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

  dht.begin();
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
    //return;
  }
  
  Serial.println("Card initialised");
  digitalWrite(23, LOW);
  delay (500);
  
  digitalWrite(beepPin, HIGH);
  delay (500);
  
  digitalWrite(beepPin, LOW);  
  
  // switch off all the led to save energy
  for (int i= 16; i < 24; i++) {
    digitalWrite(i, HIGH);
  }
  
}

  
void loop() {
  
  sensors_event_t accEvent; 
  accel.getEvent(&accEvent);// get acceleration data
  sensors_event_t magEvent;
  mag.getEvent(&magEvent); // get magnetic vector values
  sensors_event_t gyroEvent;
  gyro.getEvent(&gyroEvent); // get gyrocope values
  sensors_event_t preshureEvent;
  bmp.getEvent(&preshureEvent); // get pressure
  float temperature; // Temp



  bmp.getTemperature(&temperature); // write temp into float
  float pressure = preshureEvent.pressure; // write current pressure to float

  
  if(x1 == 0) { // get the pressure at the ground for calculating the altitude and setting this value to zero.
    x1 = bmp.pressureToAltitude(seaLevelPressure,preshureEvent.pressure,temperature); // calculating the altitude from pressure
  }

  float x2 = bmp.pressureToAltitude(seaLevelPressure,preshureEvent.pressure,temperature); // calculating altitude during flight
  float realhight = x2 - x1; // calculating altitude over ground

  //float startTime = millis();
  
  float dht_humidity = dht.readHumidity();
  float dht_temperature = dht.readTemperature();

  //float endTime = millis() - startTime;
  
  
  //Serial.println();
  //Serial.println(endTime);
  //Serial.println();

  // writing the values of the sensor to global floats
  //acceleration :
  
  digitalWrite(dustLEDPin, LOW); // LED anschalten
  delayMicroseconds (280);
  dustValue=analogRead(dustPin); // Staubsensor auslesen
  delayMicroseconds (40);
  digitalWrite(dustLEDPin, HIGH); // LED ausschalten
  delayMicroseconds (9680); // Abklingen, vermutlich nicht nötig
  voltage = dustValue *0.0048875; // umrechnen der ausgelesenen Daten zu Volt
  if (voltage <= 3.5) { // nicht Linearität des Sensors beachten
    dustDensity = voltage /7.5;
  } else {
    dustDensity = (voltage-3.5)*2 +0.4;
  }
  
  String gpsString = "";
  String temp = "";
  if (!ermittleGPS) {
    temp = GetGGA();
    if (!temp.equals("")) {
      gpsString += temp;
    }
  }
  saveData(accEvent.acceleration.x, accEvent.acceleration.y, accEvent.acceleration.z, magEvent.magnetic.x, magEvent.magnetic.y, magEvent.magnetic.z,
           gyroEvent.gyro.x, gyroEvent.gyro.y, gyroEvent.gyro.z, preshureEvent.pressure, temperature, dht_humidity, dht_temperature, dustDensity, gpsString);

}

String GetGGA() {
  //Serial.println("ermittle gga");
  String gps_output = "";
  boolean GGAready = false;
  boolean start = false;
  int inByte = 0;
  char inChar;
  ermittleGPS = true;
  while (!GGAready) {
    // Serial.println(millis());
    if (Serial3.available()) {
      inChar = Serial3.read();
      inByte = int(inChar);
      //Serial.print(inChar); // Debug Ausgabe
      //Serial.print(inByte); // Debug Ausgabe
      //Serial.print(", "); // Debug Ausgabe
      if (start) {
        if (inByte==13) { // Abbruch Bedingung erreicht
          GGAready=true;
        } else {
        gps_output += inChar;
        }
      } else { // warten auf 10 im Stream, also Ende der Zeile
        if (inByte==10) {
          start = true;
        }
      }// Ende if (start)
    } // Ende if (available)
  }// Ende while
  ermittleGPS = false;
  return(gps_output);
}


void saveData(float accelX, float accelY, float accelZ, float magX, float magY, float magZ, float gyroX, float gyroY, float gyroZ,
              float pressure, float temperature, float dht_humidity, float dht_temperature,float dustDensity, String gpsString) {
  Serial.print(accelX);
  Serial.print(SERPERATOR);
  Serial.print(accelY);
  Serial.print(SERPERATOR);
  Serial.print(accelZ);
  Serial.print(SERPERATOR);
  Serial.print(magX);
  Serial.print(SERPERATOR);
  Serial.print(magY);
  Serial.print(SERPERATOR);
  Serial.print(magZ);
  Serial.print(SERPERATOR);
  Serial.print(gyroX);
  Serial.print(SERPERATOR);
  Serial.print(gyroY);
  Serial.print(SERPERATOR);
  Serial.print(gyroZ);
  Serial.print(SERPERATOR);
  Serial.print(pressure);
  Serial.print(SERPERATOR);
  Serial.print(temperature);
  Serial.print(SERPERATOR);
  Serial.print(dht_humidity);  
  Serial.print(SERPERATOR);
  Serial.print(dht_temperature);
  Serial.print(SERPERATOR);
  Serial.print(dustDensity);
  Serial.print(SERPERATOR);
  Serial.print(gpsString);  
  
  Serial.println();
  
}

