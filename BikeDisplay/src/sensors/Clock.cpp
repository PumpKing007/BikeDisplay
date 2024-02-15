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
bool rtcActive = false;

time_t requestSync()
{
	if( rtcActive && !rtc.lostPower() ) {
		DateTime now = rtc.now();
		return now.unixtime(); // the time will be sent later in response to serial mesg
	} else {
		return 0;
	}
}

Clock::Clock() {
	setTime(0);

	if (!rtc.begin()) {
		rtcActive = false;
		// TODO error handling
	} else {
		rtcActive = true;
		if (rtc.lostPower()) {
			rtc.adjust(DateTime(2022, 12, 13, 0, 0, 0));
		}

		setSyncProvider(requestSync);
		setSyncInterval(60);
	}

}

Clock::~Clock() {
}

void Clock::setClock(int hr,int min,int sec) {
	setTime(hr, min, sec, 1, 1, 0);

	if( rtcActive ) {
		rtc.adjust(DateTime(2022, 12, 13, hr, min, sec));
	}
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



