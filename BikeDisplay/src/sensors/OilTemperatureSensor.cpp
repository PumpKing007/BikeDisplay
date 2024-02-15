/*
 * OilTemperatureSensor.cpp
 *
 *  Created on: 29.01.2024
 *      Author: Tim
 */

#include "OilTemperatureSensor.h"
#include <Arduino.h>

const uint8_t sensorPin = A0;

const int numReadings = 10;

int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
long total = 0;              // the running total
int averageReading = 0;            // the average

OilTemperatureSensor::OilTemperatureSensor()
{

}

void OilTemperatureSensor::readAdc() {
	long currentReading = 0;
	for (byte i = 0; i < 100; i++) {
		currentReading += analogRead(sensorPin);
	}
	currentReading = (long)(currentReading / 100);


	// subtract the last reading:
	total = total - readings[readIndex];
	// read from the sensor:
	readings[readIndex] = currentReading;
	// add the currentReading to the total:
	total = total + readings[readIndex];
	// advance to the next position in the array:
	readIndex = readIndex + 1;

	// if we're at the end of the array...
	if (readIndex >= numReadings) {
		// ...wrap around to the beginning:
		readIndex = 0;
	}

	// calculate the average:
	averageReading = total / numReadings;
}

int OilTemperatureSensor::readTemp()
{
	float voltageR1 = (5.0 / 1023.0) * averageReading;
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
