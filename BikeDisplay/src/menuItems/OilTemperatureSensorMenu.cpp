/*
 * OilTemperatureSensorMenu.cpp
 *
 *  Created on: 29.01.2024
 *      Author: Tim
 */

#include "OilTemperatureSensorMenu.h"

//size 21x16
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
	int temp = sensor->readTemp();

	display->clearDisplay();
	display->setTextColor(SSD1306_WHITE);
	display->drawBitmap(0, 8, bitmap_oil_temp, 21, 16, 1);
	display->setTextSize(3);
	display->setCursor(26, 8);

	if( temp > 0 ) {
		if( temp < 100 ) {
			display->print(" ");
		}
		if( temp < 10 ) {
			display->print(" ");
		}
	} else {
		if( temp > -10 ) {
			display->print(" ");
		}
	}


	display->print(temp);
	display->print((char) 247);
	display->print("C   ");

	display->display();
}

MenuItem* OilTemperatureSensorMenu::shortButtonPress() {
	return nextMenuItem;
}

MenuItem* OilTemperatureSensorMenu::longButtonPress() {
	return this;
}


displayMode OilTemperatureSensorMenu::getId() {
	return OIL_TEMP;
}
