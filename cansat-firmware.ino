#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <SD.h>
#define beepPin 5 // digitaler D-Pin 5 für Beeper
#define SERPERATOR ","
#define tempNTCPin A2 // ext. Sensor NTC (2 Beine)
// NTC-sensor variables
#define NTC_Grad 18.1699	// The gradiant value for the NTC sensor
#define NTC_Off 21.0	// The offset value for the NTC sensor
int HIH4030_Pin = A8; //analog pin 8
const int chipSelect = 27;
#define dustPin A9 // angeschlossen an Pin A9
#define dustLEDPin 4

#define GroundPressureTestCount 10

/*********************** Assign a unique ID to the sensors ****************************/
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Adafruit_10DOF                dof   = Adafruit_10DOF();
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
long lastGpsReadMillies = 0;
unsigned long  lastFullMillies = 0;
boolean doBeep = false;
unsigned long lastBeep = 0;

/**************************************************************************************/

void setup(){
  Serial.begin(19200);
  Serial1.begin(19200);
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
  
  Serial.println ("Secs,currentheight,accelx,accely,accelz,magx,magy,magz,gyrox,gyroy,gyroz,pressure,Temp,Dustdensity,Temp.ext,humidity,GPS"); 
  
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
    myFile.println("Secs,currentheight,pressure,Temp,Dustdensity,Temp.ext,humidity,GPS"); 
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("File couldnt be opened");
    return;
  }
  
  File my10DOFFile = SD.open("10dof.txt", FILE_WRITE);
  if (my10DOFFile) {
    Serial.print("File opened");
    my10DOFFile.println("-----------------------------------SNIP----------------------------------");
    my10DOFFile.println("accelx,accely,accelz,magx,magy,magz,gyrox,gyroy,gyroz,roll,pitch,heading"); 
    // close the file:
    my10DOFFile.close();
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
  read10dof();
  
  if (doBeep && lastBeep < millis()) {
      digitalWrite(beepPin, !digitalRead(beepPin));
      lastBeep = millis() + 200;
  }
//  Serial.print((lastFullMillies + 1000));
//  Serial.print(" ");
//  Serial.println(millis());
  if ((lastFullMillies + 1000) < millis()) {
    // read out all the sensor values
    sensors_event_t preshureEvent;
    float currentHeight;
    bmp.getEvent(&preshureEvent); // get pressure
    float temperature; // Temp
    bmp.getTemperature(&temperature); // write temp into float
    float pressure = preshureEvent.pressure; // write current pressure to float
    dustDensity = readDustSensor();// read dust value from sensor
  
    float externalTemperature = getTemperatureExtern(tempNTCPin);// read NTC
    float humidity = getHumidity(temperature);// read humiditySensor

    // calculate the current height
    currentHeight = bmp.pressureToAltitude(groundPressure,preshureEvent.pressure); // calculating the altitude from pressure
    if (!wasAbove50m && currentHeight > 50) {
      wasAbove50m = true;   
    }
    // check if passed the boarder and switch on beeping if passed
    if (wasAbove50m && currentHeight < 50) {
      doBeep = true;
    }
  
    // read out gps data
    String gpsString = "";
    if ((millis() - lastGpsReadMillies) > 1000) {
      String temp = "";
      if (!readGPS) {
        temp = GetGGA();
        lastGpsReadMillies = millis();
        if (!temp.equals("")) {
          gpsString += temp;
        }
      }
    }
    // save all the values
    saveData(currentHeight, preshureEvent.pressure, temperature, dustDensity, externalTemperature, humidity, gpsString);
    lastFullMillies = millis();
  }
  delay(100);

}

void read10dof () {
// read out all the sensor values
  sensors_event_t accEvent; 
  accel.getEvent(&accEvent);// get acceleration data
  sensors_event_t magEvent;
  mag.getEvent(&magEvent); // get magnetic vector values
  sensors_event_t gyroEvent;
  gyro.getEvent(&gyroEvent); // get gyrocope values
  sensors_event_t preshureEvent;


  File my10DOFFile = SD.open("10dof.txt", FILE_WRITE);
  if (my10DOFFile) {
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(accEvent.acceleration.x);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(accEvent.acceleration.y);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(accEvent.acceleration.z);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(magEvent.magnetic.x);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(magEvent.magnetic.y);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(magEvent.magnetic.z);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(gyroEvent.gyro.x);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(gyroEvent.gyro.y);
    my10DOFFile.print(SERPERATOR);
    my10DOFFile.print(gyroEvent.gyro.z);
    my10DOFFile.print(SERPERATOR);
    sensors_vec_t   orientation;
    if (dof.fusionGetOrientation(&accEvent, &magEvent, &orientation))
    {
      my10DOFFile.print(orientation.roll);
      my10DOFFile.print(SERPERATOR);
      my10DOFFile.print(orientation.pitch);
      my10DOFFile.print(SERPERATOR);
      my10DOFFile.print(orientation.heading);
      my10DOFFile.print(SERPERATOR);
    } else {
      // if not print empty
      my10DOFFile.print(SERPERATOR);
      my10DOFFile.print(SERPERATOR);
      my10DOFFile.print(SERPERATOR);
      
    }
    
    
    my10DOFFile.println();
    my10DOFFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("10DOF file couldn't be opened");
    return;
  }
  


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


void saveData(float currentHeight, float pressure, float temperature, float dustDensity, float externalTemp, float humidity, String gpsString) {

  // open file on SD card              
  File myFile = SD.open("data.txt", FILE_WRITE);
              
  // print all the data to each channel
  printData(millis()/1000, myFile);
  printData(SERPERATOR, myFile);
  printData(currentHeight, myFile);
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

float getTemperatureExtern(int pin){
  float volt = Bit2Volt(pin); // liest pin ein
  float Temp=NTC_Grad*volt-NTC_Off; // umrechnen Volt nach Grad Celcius
  return Temp; // zurueckgeben
}

float Bit2Volt(int n){ // Funktion zum Lesen und umwandeln
  int raw = analogRead(n); // Messdaten von pin 'n' lesen
  float volt = (float)raw*5.000/1023; // Umrechnung für Volt
  return volt; // zurückgeben der Voltzahl
}

float getHumidity(float degreesCelsius){
  //caculate relative humidity
  float supplyVolt = 5.0;

  // read the value from the sensor:
  int HIH4030_Value = analogRead(HIH4030_Pin);
  float voltage = HIH4030_Value/1023. * supplyVolt; // convert to voltage value
  //voltage = 1.8;
  // convert the voltage to a relative humidity
  // - the equation is derived from the HIH-4030/31 datasheet
  // - it is not calibrated to your individual sensor
  //  Table 2 of the sheet shows the may deviate from this line
  float sensorRH = 161.0 * voltage / supplyVolt - 25.8;
  float trueRH = sensorRH / (1.0546 - 0.0026 * degreesCelsius); //temperature adjustment 
  return trueRH;
}

