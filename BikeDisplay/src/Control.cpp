/*
 * Control.cpp
 *
 *  Created on: 27.01.2024
 *      Author: Tim
 */


#include "Control.h"
#include <Arduino.h>


unsigned long startPressed;    // the moment the button was pressed
unsigned long endPressed;      // the moment the button was released
volatile bool pressed = false;
volatile bool released = false;

ButtonState lastButtonState;


Control::Control() {
	lastButtonState = STATE_LOW; // previous state of the button
	startPressed=0;
	endPressed=0;
}

void Control::buttonPressed() {
	startPressed = millis();
	pressed = true;
}

void Control::buttonReleased() {
	released = true;
//	endPressed = millis();
//	unsigned long holdTime = endPressed - startPressed;
//
//	if( holdTime > 500 )
//	{
//		lastButtonState = STATE_LONG_HIGH;
//	} else {
//		lastButtonState = STATE_HIGH;
//	}
}

ButtonState Control::getButtonState() {
	endPressed = millis();
	unsigned long holdTime = endPressed - startPressed;
	if( pressed == true && released == false ) {
		if( holdTime > 500 )
		{
			lastButtonState = STATE_LONG_HIGH;
			pressed = false;
		}
	}

	if( pressed == true && released == true ) {
		if( holdTime < 100 ) {
			// the button push was just a fluke introduced trough noise and is ignored.
			lastButtonState = STATE_LOW;
		} else {
			lastButtonState = STATE_HIGH;
		}
		pressed=false;
		released=false;

	}

	if( pressed == false ) {
		released = false;
	}


	ButtonState stateToRetrun = lastButtonState;
	lastButtonState = STATE_LOW;
	return stateToRetrun;
}
