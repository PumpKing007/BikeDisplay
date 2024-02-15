/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <Arduino.h>
#include "src/Display.h"
#include "src/Control.h"

#include "src/menuItems/MenuItem.h"
#include "src/menuItems/SplashScreenMenu.h"
#include "src/menuItems/ClockMenu.h"
#include "src/menuItems/OilTemperatureSensorMenu.h"

#include <TimeLib.h>

Display display;

Control buttonController;


uint8_t currentDisplayedMode;

enum displayModes {
	SPLASH_SCREEN = 0,
	OIL_TEMP = 1, CLOCK = 2
};
uint8_t displayModesSize = 3;

// only 2 or 3 is possible, since these are the only dedicated isr ports without vector
#define buttonPin 2

void buttonPressedISR() {
	if( digitalRead(buttonPin) == HIGH ) {
		buttonController.buttonPressed();
	} else {
		buttonController.buttonReleased();
	}
}

void setup() {

	// init
	currentDisplayedMode = 0;

	// set PB5 (led) as output
	DDRB |= _BV(DDB5);

	// set A1 -> PC1 as input
	//DDRC &= ~_BV(DDC1);

	// led on:
	PORTB |= _BV(PORTB5);

	//adc read:
	//analogRead(1);

	//Serial.begin(9600);

	// setup mode button and interrupt
	pinMode(buttonPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressedISR, CHANGE);



	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin()) {
		for (;;)
			; // Don't proceed, loop forever
	}

	display.drawStarupScreen();

	delay(1000);

	//led off
	PORTB &= ~_BV(PORTB5);


	display.drawAnimationAfterStartup();


	OilTemperatureSensor oilTempSensor;
	// ----------------
	MenuItem* splashScreen = new SplashScreenMenu(&display);

	MenuItem* oilTemperatureMenu = new OilTemperatureSensorMenu(&display, &oilTempSensor);

	MenuItem* clock = new ClockMenu(&display, new Clock());

	splashScreen->setNextMenuItem(oilTemperatureMenu);

	oilTemperatureMenu->setNextMenuItem(clock);

	clock->setNextMenuItem(splashScreen);


	MenuItem* currentMenuItem = splashScreen;




	ButtonState currentButtonState;

	for (;;) {
		// toggle led
		PINB = _BV(PINB5);

		currentButtonState = buttonController.getButtonState();



		if( currentButtonState==STATE_HIGH ) {
			currentMenuItem = currentMenuItem->shortButtonPress();
			Serial.print("shortPress");

		} else if ( currentButtonState==STATE_LONG_HIGH ) {
			currentMenuItem = currentMenuItem->longButtonPress();
			Serial.print("longPress");
		}


		oilTempSensor.readAdc();
		currentMenuItem-> draw();


		delay(100);
	}
}


void switchDisplayMode() {
	currentDisplayedMode = currentDisplayedMode +1;
	currentDisplayedMode = currentDisplayedMode % displayModesSize;
}

void loop() {

}

void drawWithDisplay( Display &d )
{
	d.drawSplashScreen();
}


