/*
 * OilTemperatureSensor.cpp
 *
 *  Created on: 29.01.2024
 *      Author: Tim
 */

#include "OilTemperatureSensor.h"
#include <Arduino.h>

const uint8_t sensorPin = A0;

OilTemperatureSensor::OilTemperatureSensor()
{

}

int OilTemperatureSensor::readTemp()
{
	// measure 10 times and calculate the average
	long reading = 0;
	for (byte i = 0; i < 100; i++) {
		reading += analogRead(sensorPin);
	}
	reading = (long)(reading / 100);

	float voltageR1 = (5.0 / 1023.0) * reading;
	float resistance = 1000 * (voltageR1 / (5.0 - voltageR1));

	float tr = 423.15;
	float b = 3740.5;
	float rr = 24.0;
	float rt = resistance;


	float a = 0.11; //(tr/b);
	float bb = rr / rt;
	float logg = log(bb);

	float temp = tr / ( 1.0 - a * logg );
	float tempC = temp - 273.15;

	return (int)tempC;
}
