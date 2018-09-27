#include <Adafruit_MMA8451.h>

#define FIRST_FIRE_GND 2
#define FIRST_FIRE_VCC 3
#define FIRE_DURATION 3000
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_MMA8451.h>
#include <SimpleKalmanFilter.h>
//#include <SoftwareSerial.h>
#include <SFE_BMP180.h>
#include <EEPROM.h>
#include <Logger.h>
#include <Sensors.h>
#include <Flight.h>
#include <math.h>
#include <NeoSWSerial.h>
/*
 * the Arduino setup- for Rocket Compet 2018 GTU AEROSPACE HAVACILIK 
 * team LAGARI rocket LAGARI
 */
   Flight theObject;

void setup(){
  theObject.init();


}
/*  
   pinMode(FIRST_FIRE_GND, OUTPUT);

  digitalWrite(FIRST_FIRE_GND, LOW);
  delay(FIRE_DURATION);

  pinMode(FIRST_FIRE_GND, INPUT); 
  pinMode(FIRST_FIRE_VCC, OUTPUT); 
  digitalWrite(FIRST_FIRE_VCC, LOW);


  delay(FIRE_DURATION);
  pinMode(FIRST_FIRE_GND, INPUT);  
  pinMode(FIRST_FIRE_VCC, INPUT);
 */   
  

void loop(){
  theObject.koop();
  //  delay(10); // FİNAL 10 yap deddi




}
