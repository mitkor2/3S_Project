/*
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND 
*/
#include <Wire.h>
#include "SHTSensor.h"
SHTSensor sht;

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN  = 2;

HX711 scale1,scale2,scale3,scale4,scale5,scale6;
int reading_loadcell(int number);
int setup_loadcell(int dout,int sck, int number);
float calibration_factor = -7050; //-7050 worked for my 440lb max scale setup
float reading_cell1 = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (sht.init()) {
      Serial.print("init(): success\n");
  } else {
      Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x
//  Serial.print("data");
  setup_loadcell(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN,1);
}

void loop() {
//if (sht.readSample()) {
//      Serial.print("SHT:\n");
//      Serial.print("  RH: ");
//      Serial.print(sht.getHumidity(), 2);
//      Serial.print("\n");
//      Serial.print("  T:  ");
//      Serial.print(sht.getTemperature(), 2);
//      Serial.print("\n");
//  } else {
//      Serial.print("Error in readSample()\n");
//  }
//  delay(200);
if (sht.readSample()) {
    reading_cell1 = reading_loadcell(1);
    String H1 =  String(sht.getHumidity()); String W1 =  String(reading_cell1);String H2 =  String(sht.getHumidity());
    String W2 =  String(reading_cell1);String H3 =  String(sht.getHumidity());String W3 =  String(reading_cell1);
    String H4 =  String(sht.getHumidity());String W4 =  String(reading_cell1);String H5 =  String(sht.getHumidity());
    String W5 =  String(reading_cell1);String H6 =  String(sht.getHumidity());String W6 =  String(reading_cell1);
    String TO =  String(sht.getTemperature());
    String T1 =  String(sht.getTemperature()); String T2 =  String(sht.getTemperature()); String T3 =  String(sht.getTemperature());
    String T4 =  String(sht.getTemperature()); String T5 =  String(sht.getTemperature());String T6 =  String(sht.getTemperature());
    Serial.println(H1+";"+W1+";"+H2+";"+W2+";"+H3+";"+W3+";"+H4+";"+W4+";"+H5+";"+W5+";"+H6+";"+W6+";"+TO+";"+T1+";"+T2+";"+T3+";"+T4+";"+T5+";"+T6);
  }
  else {
      Serial.print("Error in readSample()\n");
  }
  delay(200);
}

int setup_loadcell(int dout,int sck,int number)
{
  switch (number)
  {
  case 1:
    scale1.begin(dout, sck);
    scale1.set_scale();
    scale1.tare(); //Reset the scale to 0
    long zero_factor1 = scale1.read_average(); //Get a baseline reading} 
    break;
  case 2:
    scale2.begin(dout, sck);
    scale2.set_scale();
    scale2.tare(); //Reset the scale to 0
    long zero_factor2 = scale2.read_average(); //Get a baseline reading} 
    break;
  case 3:
    scale3.begin(dout, sck);
    scale3.set_scale();
    scale3.tare(); //Reset the scale to 0
    long zero_factor3 = scale3.read_average(); //Get a baseline reading} 
    break;
  case 4:
    scale4.begin(dout, sck);
    scale4.set_scale();
    scale4.tare(); //Reset the scale to 0
    long zero_factor4 = scale4.read_average(); //Get a baseline reading} 
    break;
  case 5:
    scale5.begin(dout, sck);
    scale5.set_scale();
    scale5.tare(); //Reset the scale to 0
    long zero_factor5 = scale5.read_average(); //Get a baseline reading} 
    break;
  case 6:
    scale6.begin(dout, sck);
    scale6.set_scale();
    scale6.tare(); //Reset the scale to 0
    long zero_factor6 = scale6.read_average(); //Get a baseline reading} 
    break;  
  } 
}
int reading_loadcell(int number)
{
  float value1,value2,value3,value4,value5,value6 = 0;
  switch (number)
  {
  case 1:
    scale1.set_scale(calibration_factor); //Adjust to this calibration factor
    value1 = (((scale1.get_units()*4.5359237)/2));
    return value1;                               
    break;
  case 2:
    scale2.set_scale(calibration_factor); //Adjust to this calibration factor
    value2 = (((scale2.get_units()*4.5359237)/2));
    return value2;
    break;
  case 3:
    scale3.set_scale(calibration_factor); //Adjust to this calibration factor
    value3 = (((scale3.get_units()*4.5359237)/2));
    return value3;  
    break;
  case 4:
    scale4.set_scale(calibration_factor); //Adjust to this calibration factor
    value4 = (((scale4.get_units()*4.5359237)/2));
    return value4;
    break;
  case 5:
    scale5.set_scale(calibration_factor); //Adjust to this calibration factor
    value5 = (((scale5.get_units()*4.5359237)/2));
    return value5;  
    break;
  case 6:
    scale6.set_scale(calibration_factor); //Adjust to this calibration factor
    value6 = (((scale6.get_units()*4.5359237)/2));
    return value6;  
    break;                    
  } 
}
                         
