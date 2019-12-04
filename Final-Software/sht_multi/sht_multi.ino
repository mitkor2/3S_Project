#include <Wire.h>
#include "SHTSensor.h"
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
SHTSensor sht_1;
//SHTSensor sht_2;
#define TCAADDR 0x70
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

  Serial.println(F("##############################"));            
  Serial.println(F("Starting Initialization"));
  Serial.println(F("##############################"));       
 

  //*************INITIALIZING FIRST SENSOR*******************************   
  tcaselect(0);

  sht_1.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x

  if (sht_1.init())
  { Serial.print(F("BME280 Nr.1 detected?\t")); Serial.println(F("Ye"));}
  else
  { Serial.print(F("BME280 Nr.1 detected?\t")); Serial.println(F("No"));}
//  tcaselect(1);
//  sht_2.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x
//
//  if (sht_2.init())
//  { Serial.print(F("BME280 Nr.1 detected?\t")); Serial.println(F("No"));}
//  else
//  { Serial.print(F("BME280 Nr.1 detected?\t")); Serial.println(F("Yes"));}
}

void loop() {
//   put your main code here, to run repeatedly:
  tcaselect(0);
  if (sht_1.readSample()) {
      Serial.print("SHT1:\n");
      Serial.print("  RH1: ");
      Serial.print(sht_1.getHumidity(), 2);
      Serial.print("\n");
      Serial.print("  T1:  ");
      Serial.print(sht_1.getTemperature(), 2);
      Serial.print("\n");
  } else {
      Serial.print("Error in readSample()\n");
  }
// tcaselect(1);
//   if (sht_2.readSample()) {
//      Serial.print("SHT2:\n");
//      Serial.print("  RH2: ");
//      Serial.print(sht_2.getHumidity(), 2);
//      Serial.print("\n");
//      Serial.print("  T2:  ");
//      Serial.print(sht_2.getTemperature(), 2);
//      Serial.print("\n");
//  } else {
//      Serial.print("Error in readSample()\n");
//  }
  delay(1000);
}
