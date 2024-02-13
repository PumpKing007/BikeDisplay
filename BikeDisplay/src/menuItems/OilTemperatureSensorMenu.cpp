/*
 * OilTemperatureSensorMenu.cpp
 *
 *  Created on: 29.01.2024
 *      Author: Tim
 */

#include "OilTemperatureSensorMenu.h"

const unsigned char bitmap_oil_temp[] PROGMEM = { 0x00, 0x40, 0x00, 0x00, 0xc0,
		0x00, 0x00, 0xf8, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xc0,
		0x00, 0x00, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x60, 0xc0, 0x00, 0xf8, 0xc0,
		0x30, 0xcc, 0xc3, 0xc0, 0x7c, 0xcc, 0x80, 0x08, 0x01, 0x08, 0x08, 0x03,
		0x18, 0x08, 0x06, 0x08, 0x0f, 0xfc, 0x00 };

OilTemperatureSensorMenu::OilTemperatureSensorMenu(Display *d, OilTemperatureSensor *sensor) :
			sensor(sensor) {
		display = d;
	};


void OilTemperatureSensorMenu::draw() {
	// measure 10 times and calculate the average
	long reading = 0;
	for (byte i = 0; i < 100; i++) {
		reading += sensor->readTemp();
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

//	Serial.print("a: ");
//	Serial.print(a);
//	Serial.print(", b: ");
//	Serial.print(bb);
//	Serial.print(", logg: ");
//	Serial.print(logg);
//	Serial.print(", temp: ");
//	Serial.print(temp);
//	Serial.print("\n");


	//display->drawTemperature();

	display->clearDisplay();
	display->setTextColor(SSD1306_WHITE);
	display->drawBitmap(0, 8, bitmap_oil_temp, 21, 16, 1);
	display->setTextSize(1); //TODO 3
	display->setCursor(26, 8);
	display->print(resistance);

	display->setCursor(26, 25);
	display->print(temp);

	display->setCursor(80, 25);
	display->print(tempC);

//	display->print(sensor->readTemp());
//	display->print((char) 247);
//	display->print("C   ");

	display->display();
}

MenuItem* OilTemperatureSensorMenu::shortButtonPress() {
	return nextMenuItem;
}

MenuItem* OilTemperatureSensorMenu::longButtonPress() {
	return this;
}

