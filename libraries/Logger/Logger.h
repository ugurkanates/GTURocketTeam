/*
 * Logger.h
 *
 *  Created on: Sep 9, 2018
 *      Author: sehriyar
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <EEPROM.h>

#define RAW_DATA_SIZE 20
struct Logdata{
	unsigned int time;
	float accx;
	float accy;
	float accz;
	float alt;
};
union RawlogData{
	Logdata data;
	unsigned char rawData[RAW_DATA_SIZE];
};


class Logger {
public:
	Logger();
	virtual ~Logger();
	void writeLog(const RawlogData&);
	int addr;
};

#endif /* LOGGER_H_ */
