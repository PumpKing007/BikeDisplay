/*
 * Clock.cpp
 *
 *  Created on: 30.01.2024
 *      Author: Tim
 */

#include "Clock.h"
#include <TimeLib.h>
#include "RTClib.h"

RTC_DS3231  rtc;

time_t requestSync()
{
	if( !rtc.lostPower() ) {
		DateTime now = rtc.now();
		return now.unixtime(); // the time will be sent later in response to serial mesg
	} else {
		return 0;
	}
}

Clock::Clock() {
	if( !rtc.begin() ) {
		// TODO error handling
	}
	if( rtc.lostPower() ) {
		rtc.adjust(DateTime(2022, 12, 13, 0, 0, 0));
	}
	setTime(0);
	setSyncProvider( requestSync );
	setSyncInterval( 60 );
}

Clock::~Clock() {
}

void Clock::setClock(int hr,int min,int sec) {
	setTime(hr, min, sec, 1, 1, 0);
	rtc.adjust(DateTime(2022, 12, 13, hr, min, sec));
}
int Clock::getSeconds() {
	return second();
}
int Clock::getMinutes() {
	return minute();
}
int Clock::getHours() {
	return hour();
}



