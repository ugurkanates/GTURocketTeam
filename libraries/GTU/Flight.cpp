/*
 * Flight.cpp
 *
 *  Created on: Sep 9, 2018
 *      Ugurkan Ates & Mustafa Sehriyar
		Main software for Avianoic system inside Rocket
		This software initialize sensors,controls flight,when to open chutes(2 chute)
		and tracks GPS data to find rocket after launch

 */

#include <Flight.h>


Flight::Flight():
rocketState(JustStarted)
{

}
void Flight::init(){
 	/*
 	Rocket has states indicating what position it is currently
 	Main loop behaves according to state changes

 	*/
	rocketState = JustStarted;
	basePresure = 0 ;
	previousAltitude = 0;
	pendingApogee = false;
	apogeeCountdownStart = 0;
	safetyApogeeCountdownStart = 0;
	freeFallAltitudeInRange = 0;
	//my sensor() ?

	pinMode(FIRST_FIRE_GND, OUTPUT);
	pinMode(SECOND_FIRE_GND, OUTPUT);

	digitalWrite(FIRST_FIRE_GND, LOW);
	digitalWrite(SECOND_FIRE_GND, LOW);
	
	if(mySensor.Initialize()){
		rocketState = Standby;
	}
	else {
		rocketState = StartUpError;
	}

	pendingApogee = false;
	delay(1000); // SENSORLER kendine gelsin -> sensors cooldown

}

		//Serial.begin(9600);

/*1
	//Serial.begin(9600);
		delay(1000); // SENSORLER kendine gelsin -> sensors cooldown
	if(mySensor.Initialize()){
		rocketState = Standby;
		Serial.println("ee");
	}
	else {
		//rocketState = StartUpError;
	}
	Serial.println("er1");//Serial.println("error");

	pendingApogee = false;

	Serial.println("er2");//Serial.println("error");
	*/



Flight::~Flight() {
	// TODO Auto-generated destructor stub
}

//main loop is here 

void Flight::koop(){
	//mySensor.heartBeat();
	float acc = 0;
	float alt = 0;

	
	/*if(!mySensor.getAcceleration(acc)){
		Serial.println("CA");//Serial.println("error");
		return;
	}

	if(!mySensor.getAltitude(alt)){
		Serial.println("CB");//Serial.println("error");
		return;
	}
	*/
	Serial.println("Accelemator DATA ");
	mySensor.getAcceleration(acc);
	Serial.println("Altitude DATA ");
  	mySensor.getAltitude(alt);
 	Serial.println("GPS DATA ");
	mySensor.getGpsLocation();

	switch(rocketState) {

	case StartUpError:
		StartupErrorF(); // ac kapa -> yap
		break;

	case Standby:
		StandbyF(acc);
		break;
	case RiseWithMotor:
		RiseWithMotorF(acc);
		break;
	case RiseAfterMotorStops:    //expect apogee
		RiseAfterMotorStopsF(acc, alt);
		break;
	case Drogue:
		DrogueF(alt);
		break;
	case Landing:
		LandingF();
		break;
	default:
		break;
	}
	previousAltitude = alt;
}


// MAIN SETUP  - ARDUINO



void Flight::fireFirst(){
	pinMode(FIRST_FIRE_GND, INPUT); 
	pinMode(FIRST_FIRE_VCC, OUTPUT); 
	digitalWrite(FIRST_FIRE_VCC, LOW);


	delay(FIRE_DURATION); //fitil patlama ms

	pinMode(FIRST_FIRE_GND, INPUT);
	pinMode(FIRST_FIRE_VCC, INPUT);


	apogeeCountdownStart = 0;
	safetyApogeeCountdownStart = 0;
	pendingApogee = false;
	rocketState = Drogue;
}

void Flight::fireSecond(){

	pinMode(SECOND_FIRE_GND, INPUT); 
	pinMode(SECOND_FIRE_VCC, OUTPUT); 
	digitalWrite(SECOND_FIRE_VCC, LOW);


	delay(FIRE_DURATION);

	pinMode(SECOND_FIRE_GND, INPUT);
	pinMode(SECOND_FIRE_VCC, INPUT);

	rocketState = Landing;

}



void Flight::LandingF(){
	Serial.print(mySensor.getGpsLocation());
}


int Flight::isInFreeFall(float altitude) {
	if(previousAltitude - altitude > FREE_FALL_ALTITUDE_DELTA) {
		freeFallAltitudeInRange++;
	}

	return (freeFallAltitudeInRange >= FREE_FALL_ALTITUDE_LIMIT);
}

void Flight::DrogueF(float alt){
	if(isInFreeFall(alt)) {
		fireFirst();
		fireSecond();
	}
	if (alt < SECOND_FIRE_ALTITUDE)
	{
		fireSecond();
	}
}

void Flight::RiseAfterMotorStopsF(float acc, float alt){
	if(pendingApogee) {
		if(previousAltitude - alt > APOGEE_ALTITUDE_DELTA) {
			fireFirst();
		}
	}

	// If the apogee countdown is finished, fire it
	// It has 4 SECURITY CHECK TO OPEN PARACHUTES
	//one is time check others based on accelatrion sensor
	//if its lower than 2.94 it will try to open parachutes surely
	//it lower than 1.47 it will lower the time requires for it
	//if its lower than 0.5 it will try to fire parachute immediately
	// this security checks done for ensuring even if Arduino get sensor data slowly it will fire chutes
	
	int apogeeCountdownCheck = checkApogeeCountdowns();
	if(apogeeCountdownCheck > 0) {
		fireFirst();
		return;
	}

	if(acc< 0.5){
		fireFirst();
		return;
	}
	if(acc < 1.47) {  //APOGEE_IDEAL 9.8 CARP
		pendingApogee = true;

		if(apogeeCountdownStart == 0) {
			apogeeCountdownStart = millis();
		}
		return;
	}


	if(acc < 2.94) {
	
		if(safetyApogeeCountdownStart == 0) {
			safetyApogeeCountdownStart = millis();
		}
		return;
	}

}


void Flight::RiseWithMotorF(float acceleration){
	if(acceleration <= 7.35) {  //COAST_ACCELERATION G ile carpildidegistirdim 
		rocketState = RiseAfterMotorStops;
		return;
	}
}

void Flight::StandbyF(float acceleration){
	// G ile carpildi  9.8

	if(acceleration >= 12.25) {  //Boost acceleration
		rocketState = RiseWithMotor;
		return;
	}
	// 7.35 < x 12.25 arası standby

	if(acceleration <= 7.35) {  //COAST_ACCELERATION
		rocketState = RiseAfterMotorStops;
		return;
	}

}


void Flight::StartupErrorF(){
	digitalWrite(13, HIGH);
	while(true){
		delay(1000);
	}
}
bool Flight::checkApogeeCountdowns(){
	if(apogeeCountdownStart > 0 && abs(apogeeCountdownStart - millis()) >= APOGEE_COUNTDOWN) {
		return true;
	}


	if(safetyApogeeCountdownStart > 0 && abs(safetyApogeeCountdownStart -millis()) >= SAFETY_APOGEE_COUNTDOWN) {
		return true;
	}
	return false;
}

