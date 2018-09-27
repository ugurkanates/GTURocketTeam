/*
 * Flight.h
 *
 *  Created on: Sep 9, 2018
 *      Ugurkan Ates - Mustafa Sehriyar
 		Gebze Technical University 
 		Aerospace and Aviation Community
 		GTU Rocket Team
 		Rocket name is LAGARI
 		please contact me via any platform if anything you want to ask
 		thanks
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_
#include <Sensors.h>
#include <Logger.h>

#define NUM_EVENTS 2 
#define FIRE_DURATION 300 // ms
#define DEFAULT_MAIN_ALTITUDE 152.4f // meter -> this should be calibrated to your own
#define APOGEE -1

#define APOGEE_PIN 5
#define MAIN_PIN 6

#define EVENT_APOGEE 0
#define EVENT_MAIN 1

#define APOGEE_CAUSE_NONE 0
#define APOGEE_CAUSE_ALTITUDE 1
#define APOGEE_CAUSE_COUNTDOWN 2
#define APOGEE_CAUSE_SAFETY_COUNTDOWN 3
#define APOGEE_CAUSE_FREE_FALL 4
#define APOGEE_CAUSE_MANUAL 5

#define APOGEE_COUNTDOWN 6 // seconds
#define SAFETY_APOGEE_COUNTDOWN 12 // seconds
#define BOOST_ACCELERATION 1.25 // g
#define COAST_ACCELERATION 0.75 // g
#define APOGEE_IDEAL 0.15 // g
#define APOGEE_OKAY 0.3 // g
#define APOGEE_ALTITUDE_DELTA 1 // meters
#define FREE_FALL_ALTITUDE_DELTA 10 // meters
#define FREE_FALL_ALTITUDE_LIMIT 3
#define LANDED_ALTITUDE_DELTA 1.5 // meters
#define LANDED_ALTITUDE_LIMIT 5

#define FIRST_FIRE_GND 2
#define FIRST_FIRE_VCC 3
#define SECOND_FIRE_GND 4
#define SECOND_FIRE_VCC 5
#define SECOND_FIRE_ALTITUDE 500

#define    JustStarted 0
#define    StartUpError 1
#define    Standby 2
#define    RiseWithMotor 3
#define    RiseAfterMotorStops 4
#define    Drogue 5
#define    Landing 6
  

class Flight {
public:
	Flight();
	virtual ~Flight();
	void koop();

	void init();


	void LandingF();
	void DrogueF(float);
	void RiseAfterMotorStopsF(float acc, float alt);
	void RiseWithMotorF(float acceleration);
	void StandbyF(float acceleration);
	void StartupErrorF();


	bool checkApogeeCountdowns();
	void fireFirst();
	void fireSecond();
	int isInFreeFall(float altitude);
private:
	int rocketState;
	Sensors mySensor;
	Logger mLogger;
	float basePresure; // baseline pressure

	float previousAltitude;
	bool pendingApogee;
    long int apogeeCountdownStart;
    long int safetyApogeeCountdownStart;
    int freeFallAltitudeInRange;
};

#endif /* FLIGHT_H_ */
