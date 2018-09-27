/*
 * Logger.cpp
 *
 *  Created on: Sep 9, 2018
 *      Author: sehriyar
 */

#include <Logger.h>

Logger::Logger()
:addr(0)
{


}

Logger::~Logger() {

}


void Logger::writeLog(const RawlogData& log)
{
	for(int i=0; i<RAW_DATA_SIZE; i++){
		EEPROM.write(addr, log.rawData[i]);
		addr++;
	}
	if (addr >= 1000) {
		addr = 0;
	}
}
