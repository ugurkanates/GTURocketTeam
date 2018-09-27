/*
 * Sensors.h
 *
 *  Created on: Sep 9, 2018
 *      Author: sehriyar
 */

#ifndef SENSORS_H_
#define SENSORS_H_
//#include <Wire.h>

//#include <stdio.h>
//#include <string.h>

#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SimpleKalmanFilter.h>
//#include <SoftwareSerial.h>
#include <SFE_BMP180.h>
#include <math.h>
#include "NeoSWSerial.h"
class Sensors {
public:
	Sensors();
	virtual ~Sensors();
	bool Initialize();
	String getGpsLocation();
	bool getAcceleration(float& retVal);
	bool getAltitude(float& returnAlt);

	float getX();
	float getY();
	float getZ();
	float getAlt();	

	void heartBeat();

	Adafruit_MMA8451 accelerometerMMA;
	SFE_BMP180 pressureBMP;
	//SoftwareSerial gpsSerial;
	NeoSWSerial gpsSerial;
	SimpleKalmanFilter kalmanFilterX;
	SimpleKalmanFilter kalmanFilterY ;
	SimpleKalmanFilter kalmanFilterZ ;
	SimpleKalmanFilter kalmanFilterAlt ;

	String sendData(String command, const int timeout, boolean debug);
	double getPressureBase();

	double basePresure;


};

#endif /* SENSORS_H_ */
