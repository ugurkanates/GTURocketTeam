/*
 * Sensors.cpp
 *
 *  Created on: Sep 9, 2018
 *      Author: sehriyar
 */

#include <Sensors.h>

#define DEBUG true
Sensors::Sensors():
gpsSerial(7,8),kalmanFilterX (0.15, 1, 0.01), kalmanFilterY (0.15, 1, 0.01),
	 kalmanFilterZ (0.15, 1, 0.01), kalmanFilterAlt (0.15, 1, 0.01)
 {
	// TODO Auto-generated constructor stub

}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}




bool Sensors::Initialize(){

  Serial.begin(9600);
  gpsSerial.begin(9600);//) {

 // Serial.println("bu"); // yoruma alcak
	pinMode(13,OUTPUT);
  if(!pressureBMP.begin()){
    Serial.println("AA");
    //Serial.print( "AltitudeError");
    return false;
   // rocketState = StartUpError;
  }
  basePresure = getPressureBase(); /*used for relative altitude*/


  if (!accelerometerMMA.begin()){
    //Serial.print( "AccelerometerError");
    return false;
    //rocketState = StartUpError;
  }


  //if(
//    Serial.print( "StartGpsError");
 //   rocketState = StartUpError;
  //}d

  accelerometerMMA.setRange(MMA8451_RANGE_2_G);
  Serial.println("AC"); // 2 sensors SUCCESFULY startrd

   /*initialize GPS SIMDILIK YORUMA ALINDI */


   sendData( "AT+CGNSPWR=1",100,DEBUG);
   sendData( "AT+CGNSSEQ=RMC",100,DEBUG);
   sendData("AT+CGPSPWR=1", 100, DEBUG);
   delay(1000);
   sendData("AT+CGPSSTATUS?", 100, DEBUG);
   

   //TODO:: return string should be parse if error occur reject start
   //if(error){ rocketState = StartUpError;}
  /////////////////////////////////////////////////////////////////
  float alt;
  getAltitude(alt);
  getAcceleration(alt);
  getGpsLocation();
  return true;
}

String Sensors::getGpsLocation(){
  sendData( "AT+CGPSINF=?",100,DEBUG);
	return sendData( "AT+CGPSINF",100,DEBUG);
}

	float Sensors::getX(){
	  accelerometerMMA.read();
	  sensors_event_t event;
  	accelerometerMMA.getEvent(&event);
  	return event.acceleration.x;
	}
	float Sensors::getY(){
		  accelerometerMMA.read();
	  sensors_event_t event;
  	accelerometerMMA.getEvent(&event);
  	return event.acceleration.y;
	}
	float Sensors::getZ(){
		  accelerometerMMA.read();
	  sensors_event_t event;
  	accelerometerMMA.getEvent(&event);
  	return event.acceleration.z;
	}
	float Sensors::getAlt(){
	double currentPressure;
  char status;
  double T,P,p0,a;
  float measured_Alt;

  status = pressureBMP.startTemperature();
  if (status != 0){
    delay(status);
    status = pressureBMP.getTemperature(T);
    if (status != 0){
      status = pressureBMP.startPressure(3);
      if (status != 0){
        delay(status);
        status = pressureBMP.getPressure(currentPressure,T);

        if (status == 0){
          Serial.println("error retrieving pressure measurement\n");
       //   rocketState = StartUpError;
          return false;
        }
      }
      else{
        Serial.println("error starting pressure measurement\n");
     //   rocketState = StartUpError;
        return false;
      }
    }
    else {
      Serial.println("error retrieving temperature measurement\n");
   //   rocketState = StartUpError;
      return false;
    }
  }
  else {
    Serial.println("error starting temperature measurement\n");
 //   rocketState = StartUpError;
    return false;
  }

	return (float)pressureBMP.altitude(currentPressure,basePresure);
 
	}


bool Sensors::getAcceleration(float& retVal ){
  accelerometerMMA.read();
  sensors_event_t event;
  accelerometerMMA.getEvent(&event);
  float estimated_X = kalmanFilterX.updateEstimate(event.acceleration.x);
  float estimated_Y = kalmanFilterY.updateEstimate(event.acceleration.y);
  float estimated_Z = kalmanFilterZ.updateEstimate(event.acceleration.z);
  
	Serial.print(event.acceleration.x); //estimated_X
	Serial.print("  ");
	Serial.print(event.acceleration.y); //estimated_Y
	Serial.print("  ");
	Serial.println(event.acceleration.z); //estimated_Z
	
  retVal = sqrt( estimated_X*estimated_X + estimated_Y*estimated_Y + estimated_Z*estimated_Z);
  
  Serial.println(retVal);
  return true;
}

bool Sensors::getAltitude(float& returnAlt){
  double currentPressure;
  char status;
  double T,P,p0,a;
  float measured_Alt;

  status = pressureBMP.startTemperature();
  if (status != 0){
    delay(status);
    status = pressureBMP.getTemperature(T);
    if (status != 0){
      status = pressureBMP.startPressure(3);
      if (status != 0){
        delay(status);
        status = pressureBMP.getPressure(currentPressure,T);

        if (status == 0){
          Serial.println("error retrieving pressure measurement\n");
          return false;
        }
      }
      else{
        Serial.println("error starting pressure measurement\n");
        return false;
      }
    }
    else {
      Serial.println("error retrieving temperature measurement\n");
      return false;
    }
  }
  else {
    Serial.println("error starting temperature measurement\n");
    return false;
  }

  measured_Alt = (float)pressureBMP.altitude(currentPressure,basePresure);
  float estimated_altitude = kalmanFilterAlt.updateEstimate(measured_Alt);
  returnAlt = estimated_altitude;
  Serial.print(measured_Alt,2);
  Serial.print("  ");
  Serial.println(estimated_altitude,2);
  
  return true;
}

String Sensors::sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    gpsSerial.println(command);
    long int time = millis();
    while( (time+timeout) > millis())
    { 
      if(gpsSerial.available())
      {
        //Serial.println("x");
        char c = gpsSerial.read();
        response+=c;
      }
    }
    if(debug)
    {
      Serial.print(response);
    }
    return response;
}

double Sensors::getPressureBase()
{
  char status;
  double T,P,p0,a;

  status = pressureBMP.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressureBMP.getTemperature(T);
    if (status != 0)
    {
      status = pressureBMP.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressureBMP.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("C");//Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("D");//("error starting pressure measurement\n");
    }
    else Serial.println("E");//("error retrieving temperature measurement\n");
  }
  else Serial.println("F");//("error starting temperature measurement\n");
}


void Sensors::heartBeat()
{
	digitalWrite(13, HIGH);
	delay(3000);
	digitalWrite(13, LOW);

}
