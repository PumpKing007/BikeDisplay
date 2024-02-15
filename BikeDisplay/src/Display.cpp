/*
 * Display.cpp
 *
 *  Created on: 24.01.2024
 *      Author: Tim
 */

#include "Display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

const unsigned char gsx1100g_bitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x7e, 0x3f, 0xe0, 0xff, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfd, 0xfe, 0xff, 0xf1, 0xff, 0xc0, 0x00, 0x00,
	0x01, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0x1f, 0xc7, 0xfb, 0xfc, 0xff, 0xf3, 0xff, 0xe0, 0xff, 0xfc,
	0x03, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xbf, 0x87, 0xfb, 0xfd, 0xfb, 0xf3, 0xf7, 0xe3, 0x80, 0x00,
	0x07, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xf7, 0xf9, 0xf3, 0xf7, 0xe7, 0xc7, 0x7f, 0xf8,
	0x0f, 0xf0, 0x03, 0xfc, 0x00, 0x7f, 0xfc, 0x07, 0xe3, 0xfb, 0xf7, 0xe7, 0xef, 0xc6, 0xe0, 0x00,
	0x0f, 0xf0, 0x03, 0xff, 0xf8, 0x3f, 0xf0, 0x07, 0xe3, 0xf3, 0xe7, 0xef, 0xcf, 0x8e, 0xc0, 0x00,
	0x1f, 0xe7, 0xf9, 0xff, 0xfc, 0x3f, 0xf0, 0x0f, 0xc7, 0xf7, 0xef, 0xcf, 0xdf, 0x8d, 0xc3, 0x60,
	0x1f, 0xef, 0xf0, 0x07, 0xfc, 0xff, 0xf8, 0x1f, 0xcf, 0xe7, 0xcf, 0xdf, 0x9f, 0x1d, 0x86, 0x60,
	0x3f, 0xef, 0xf0, 0x07, 0xf9, 0xff, 0xfc, 0x1f, 0x8f, 0xef, 0xdf, 0xbf, 0xbe, 0x1b, 0xce, 0xc0,
	0x3f, 0xff, 0xff, 0xff, 0xf7, 0xfb, 0xfc, 0x3f, 0x9f, 0xcf, 0xff, 0xbf, 0xfe, 0x1c, 0xfc, 0xc0,
	0x3f, 0xff, 0xff, 0xff, 0xcf, 0xe1, 0xfe, 0x3f, 0x1f, 0xcf, 0xff, 0x1f, 0xfc, 0x1e, 0x01, 0x80,
	0x1f, 0xff, 0xff, 0xff, 0x1f, 0xc1, 0xff, 0x7f, 0x3f, 0x87, 0xfe, 0x1f, 0xf8, 0x03, 0xfe, 0x00
};


const unsigned char bitmap_oil_temp[] PROGMEM = { 0x00, 0x40, 0x00, 0x00, 0xc0,
		0x00, 0x00, 0xf8, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xc0,
		0x00, 0x00, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x60, 0xc0, 0x00, 0xf8, 0xc0,
		0x30, 0xcc, 0xc3, 0xc0, 0x7c, 0xcc, 0x80, 0x08, 0x01, 0x08, 0x08, 0x03,
		0x18, 0x08, 0x06, 0x08, 0x0f, 0xfc, 0x00 };

Display::Display() {
	Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	currentDisplayedMode = 0;
}

Display::~Display(){

}

bool Display::begin() {
	return Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}


void Display::switchDisplayMode() {
	currentDisplayedMode = currentDisplayedMode++ % displayModesSize;
}

void Display::drawSplashScreen() {
	clearDisplay();

	drawBitmap(0, 9, gsx1100g_bitmap, 128, 13, 1);
	display();
}

void Display::drawTemperature() {
	clearDisplay();

	drawBitmap(0, 8, bitmap_oil_temp, 21, 16, 1);
	setTextSize(3);
	setTextColor(SSD1306_WHITE);
	setCursor(26, 8);
	print("528");
	print((char) 247);
	print("C   ");

	display();
}

void Display::drawClock() {
	clearDisplay();
	setTextColor(SSD1306_WHITE);
	setCursor(26, 0);
	print( "CLOCK");
	display();
}

void Display::drawTest() {
	clearDisplay();
	setTextColor(SSD1306_WHITE);
	setCursor(26, 0);
	print( "Test");
	display();
}

