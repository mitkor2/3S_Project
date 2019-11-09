/*
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND
*/
#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
#define LOADCELL1_DOUT_PIN  3
#define LOADCELL1_SCK_PIN  2
//HX711 *scale2 = new HX711();
HX711 scale,scale2,scale3,scale4,scale5,scale6;
float calibration_factor = -7050; //-7050 worked for my 440lb max scale setup
void setup_loadcell(int dout, int sck, HX711 scale);
void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL1_DOUT_PIN ,LOADCELL1_SCK_PIN);
  scale.set_scale();
  scale.tare();
                         //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading 
//  Serial.println("HX711 calibration sketch");
//  Serial.println("Remove all weight from scale");
//  Serial.println("After readings begin, place known weight on scale");
//  Serial.println("Press + or a to increase calibration factor");
//  Serial.println("Press - or z to decrease calibration factor");
  //  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
//  Serial.println(zero_factor);
}

void loop()
{
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
    Serial.println(((scale.get_units()*4.5359237)/2), 1);
    Serial.print("");
    delay(20); 
//  if(Serial.available())
//  {
//    char temp = Serial.read();
//    if(temp == '+' || temp == 'a')
//      calibration_factor += 10;
//    else if(temp == '-' || temp == 'z')
//      calibration_factor -= 10;
//  }
}
