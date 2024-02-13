/*
 * Clock.cpp
 *
 *  Created on: 30.01.2024
 *      Author: Tim
 */

#include "Clock.h"
#include <TimeLib.h>

Clock::Clock() {
	setTime(1705963214);

}

Clock::~Clock() {
}

void Clock::setClock(int hr,int min,int sec) {
	setTime(hr, min, sec, 1, 1, 0);
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

