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

uint16_t OilTemperatureSensor::readTemp()
{
	return analogRead(sensorPin);
}
