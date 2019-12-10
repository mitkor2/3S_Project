#include <Wire.h>
#include "HX711.h" 
#include "SHTSensor.h"
extern "C" { 
  #include "utility/twi.h"}
#define TCAADDR 0x70
#define LOADCELL_DOUT_PIN_1 3  
#define LOADCELL_SCK_PIN_1 2   
#define LOADCELL_DOUT_PIN_2 5  
#define LOADCELL_SCK_PIN_2 4
#define LOADCELL_DOUT_PIN_3 7  
#define LOADCELL_SCK_PIN_3 6
#define LOADCELL_DOUT_PIN_4 9  
#define LOADCELL_SCK_PIN_4 8
#define LOADCELL_DOUT_PIN_5 11  
#define LOADCELL_SCK_PIN_5 10
#define LOADCELL_DOUT_PIN_6 13  
#define LOADCELL_SCK_PIN_6 12    
HX711 scale[6];
SHTSensor sht[7];
void tcaselect(uint8_t i); 
int reading_loadcell(int number);
void setupsht85(int index);
int temp(int index);
int hum(int index);
void setupscales(int index,int out, int sck);
float calibration_factor = -7050; //-7050 worked for my 440lb max scale setup
long reading_cell[6];
float  temp_s[7];
float  hum_s[7];
long zero_factor[6];
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  setupscales(0,LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN_1);
  setupscales(1,LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN_2);
  setupscales(2,LOADCELL_DOUT_PIN_3, LOADCELL_SCK_PIN_3);
  setupscales(3,LOADCELL_DOUT_PIN_4, LOADCELL_SCK_PIN_4);
  setupscales(4,LOADCELL_DOUT_PIN_5, LOADCELL_SCK_PIN_5);
  setupscales(5,LOADCELL_DOUT_PIN_6, LOADCELL_SCK_PIN_6);     
  setupsht85(0);
  setupsht85(1);
  setupsht85(2);
  setupsht85(3);
  setupsht85(4);
  setupsht85(5);
  setupsht85(6);
}

void loop() {
  for (int i = 0; i <= 6; i++)
  {
    if (sht[i].readSample())
      { 
        tcaselect(i);
        if(isnan(sht[i].getHumidity())){hum_s[i]=0;temp_s[i]=0;}
        else{hum_s[i]=sht[i].getHumidity();temp_s[i]=sht[i].getTemperature();}
      }
  }
  reading_cell[0] = reading_loadcell(0);
  reading_cell[1] = reading_loadcell(1);
  reading_cell[2] = reading_loadcell(2);
  reading_cell[3] = reading_loadcell(3);
  reading_cell[4] = reading_loadcell(4);
  reading_cell[5] = reading_loadcell(5);
//  if(isnan(sht[0].getHumidity())){hum_s[0]=0;temp_s[0]=0;}
//  else{hum_s[0]=sht[0].getHumidity();temp_s[0]=sht[0].getTemperature();}
//  if(isnan(sht[1].getHumidity())){hum_s[1]=0;temp_s[1]=0;}
//  else{hum_s[1]=sht[1].getHumidity();temp_s[1]=sht[1].getTemperature();}
//  if(isnan(sht[2].getHumidity())){hum_s[2]=0;temp_s[2]=0;}
//  else{hum_s[2]=sht[2].getHumidity();temp_s[2]=sht[2].getTemperature();}
//  if(isnan(sht[3].getHumidity())){hum_s[3]=0;temp_s[3]=0;}
//  else{hum_s[3]=sht[3].getHumidity();temp_s[3]=sht[3].getTemperature();}
//  if(isnan(sht[4].getHumidity())){hum_s[4]=0;temp_s[4]=0;}
//  else{hum_s[4]=sht[4].getHumidity();temp_s[4]=sht[4].getTemperature();}
//  if(isnan(sht[5].getHumidity())){hum_s[5]=0;temp_s[5]=0;}
//  else{hum_s[5]=sht[5].getHumidity();temp_s[5]=sht[5].getTemperature();}
//  if(isnan(sht[6].getHumidity())){hum_s[6]=0;temp_s[6]=0;}
//  else{hum_s[6]=sht[6].getHumidity();temp_s[6]=sht[6].getTemperature();}
  String H1 =  String(hum_s[0]); String W1 =  String(reading_cell[0]);String H2 =  String(hum_s[1]);
  String W2 =  String(reading_cell[1]);String H3 =  String(hum_s[2]);String W3 =  String(reading_cell[2]);
  String H4 =  String(hum_s[3]);String W4 =  String(reading_cell[3]);String H5 =  String(hum_s[4]);
  String W5 =  String(reading_cell[4]);String H6 =  String(hum_s[5]);String W6 =  String(reading_cell[5]);
  String TO =  String(temp_s[6]);
  String T1 =  String(temp_s[0]); String T2 =  String(temp_s[1]); String T3 =  String(temp_s[2]);
  String T4 =  String(temp_s[3]); String T5 =  String(temp_s[4]);String T6 =  String(temp_s[5]);
  Serial.println(H1+","+W1+","+H2+","+W2+","+H3+","+W3+","+H4+","+W4+","+H5+","+W5+","+H6+","+W6+","+TO+","+T1+","+T2+","+T3+","+T4+","+T5+","+T6);
  delay(300);
}

void tcaselect(uint8_t i) 
{
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
  }
} 
int reading_loadcell(int number)
{
  float value = 0;
  scale[number].set_scale(calibration_factor);
  value = (((scale[number].get_units()*4.5359237)/2));
  return value;                    
}
void setupscales(int index,int out, int sck)
{
  scale[index].begin(out, sck);
  scale[index].set_scale();
  scale[index].tare();
  zero_factor[index] = scale[index].read_average();
}
void setupsht85(int index)
{
  tcaselect(index);
  sht[index].setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);
  if (sht[index].init())
  { Serial.println(F("Yes it is connected"));
  }
  else
  { Serial.println(F("No it is not connected"));
  }
}
int temp(int index)
{
  long value_temp;
  tcaselect(index);
  if (sht[index].readSample())
  {
    value_temp = sht[index].getTemperature();
  }
  return value_temp;
}
int hum(int index)
{
  long value_hum;
  tcaselect(index);
  if (sht[index].readSample())
  {
    value_hum = sht[index].getHumidity();
  }
  return value_hum;
}
