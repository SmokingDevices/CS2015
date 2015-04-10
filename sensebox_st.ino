
/*******************************************************************************************
 * Programm für die Aufzeichung von Sensebox Sensoren auf eine SD Karte                    *
 * Autor: Steffen Janke (Zuarbeit Hersteller)                                              *
 * Version: 1.10                                                                           *
 * Datum letzte Änderung: 23.07.2014                                                       *
 *******************************************************************************************/
 
//libraries to include
#include <SD.h>
#include <Wire.h>
#include <DHT.h>
#include <Barometer.h>

#define serialBaud 9600

//SD Card Pin
#define SDCARD_CS 4

//Define analog ports used by sensors
#define LightData A1    // parameters for Light Sensor
#define SoundData A0    // parameters for Sound-Sensor
#define DHTPIN A2       // parameters for DHT-Sensor

// enable/disable sensors
#define dhtEnabled true
#define LightEnabled true
#define SoundEnabled true
#define csvColumns "Zeit in s;Druck;Hoehe; Temperatur (p); Temperatur (t);Luftfeuchte;Licht;Licht (K);Lautstaerke"

// first time variable
boolean firstTime = true;
float pressu;
float altim;

File sdfile;


//Sensor instances
DHT dht(DHTPIN, DHT11);
Barometer myBarometer;

//Variables for time sync and upload intervall
const unsigned long postingInterval = 1000; //1 sek
long int lastConnected = 0;
boolean uploadSuccess = false;

void setup()
{
  //Start serial port
  Serial.begin(serialBaud);
  Serial.println("Initialisiere SD Karte...");
  if (!SD.begin(SDCARD_CS)) 
  {
    Serial.println("Initialisierung fehlgeschlagen!");
    return;
  }
  Serial.println("Initialisierung gelaufen.");
  if (SD.exists("WETTER.CSV")) 
  {
    Serial.print("WETTER.CSV existiert->wird geloescht!");
    do 
    { // solange versuchen zu löschen, bis weg ist
      Serial.print("."); 
      SD.remove("WETTER.CSV");
      delay(100);
    } while (SD.exists("WETTER.CSV"));
    Serial.println(); 
  }  
  Serial.println("Oeffne Wetter.txt zum Schreiben"); 
  sdfile = SD.open("WETTER.CSV", O_CREAT | O_WRITE | O_APPEND);
  if (sdfile) 
  {
    Serial.println("WETTER.CSV offen");
  } else 
  {
    Serial.println("Fehler beim Oeffnen der WETTER.CSV");
  }
  //initialize barometer and DHT sensors
  myBarometer.init();
  dht.begin();
}

void loop()
{
  String output = "";
//  if((millis() - lastConnected > postingInterval)) 
  if(sdfile && (millis() - lastConnected >= postingInterval)) 
  {
    lastConnected = millis();
    char time[20];
    dtostrf(lastConnected/1000, 0, 0, time);
    char humidity[20];
    dtostrf(dht.readHumidity(), 0, 2, humidity);
    char temperature[20];
    dtostrf(dht.readTemperature(), 0, 2, temperature);
    char temperature2[20];
    dtostrf(myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()), 0, 2, temperature2);
    char pressure[20];
    pressu = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());
    dtostrf(pressu, 0, 2, pressure);
    altim = myBarometer.calcAltitude(pressu);
    char hoehe[20];
    dtostrf(altim, 0, 1, hoehe);

    // build one csv output string
    output += time;
    output += ";";
    output += pressure;
    output += ";";
    output += hoehe;
    output += ";";
    output += temperature2;
    output += ";";
    
    if (dhtEnabled) 
    {
       output += temperature;
       output += ";";
       output += humidity;
    } else { output += "-;-"; }
    output += ";";
    if (LightEnabled) 
    {
      int sensorValue = analogRead(0); 
      float Rsensor;
      sensorValue = analogRead(LightData);
      Rsensor=(float)(1023-sensorValue)*10/sensorValue;
      char rs[20];
      dtostrf(Rsensor, 0, 2, rs);
      output += sensorValue;
      output += ";";
      output += rs;
    }else { output += "-"; }
    output += ";";
    if (SoundEnabled) 
    {  
      output += analogRead(SoundData);
    } else { output += "-"; }
    output += ";";

    postData(output);
  }
}

//Method for posting a measurement to OSM server
void postData(String txt)
{  
  if (firstTime) 
  {
   // set the first time variable to false
    firstTime = false;
    // serial output
    Serial.println(csvColumns);
    // sd card output
    sdfile.println(csvColumns);
  }

  Serial.println(txt);
  sdfile.println(txt);
  sdfile.flush();
}

