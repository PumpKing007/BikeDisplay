/*
 * ClockMenu.cpp
 *
 *  Created on: 30.01.2024
 *      Author: Tim
 */

#include "ClockMenu.h"

enum SubMenu{
	SHOW = 0, SET_MINUTES = 1, SET_HOURS = 2
};


SubMenu currentSubMenu = SHOW;

int hours;
int minutes;


ClockMenu::ClockMenu(Display *d, Clock *clock) : clock(clock) {
	display = d;
	hours = clock->getHours();
	minutes = clock->getMinutes();
}

ClockMenu::~ClockMenu() {
	// TODO Auto-generated destructor stub
}

void ClockMenu::blinkNumber( int number , bool blink ) {
	if( blink ) {
		if( (millis() % 100) > 50 ) {
			if( number < 10 ) {
				display->print(0);
			}
			display->print(number);
		} else {
			display->print("  ");
		}
	} else {
		if( number < 10 ) {
			display->print(0);
		}
		display->print(number);
	}
}

void ClockMenu::draw() {

	if (currentSubMenu == SHOW) {
		hours = clock->getHours();
		minutes = clock->getMinutes();

	}

	display->clearDisplay();
	display->setTextSize(3);
	display->setTextColor(SSD1306_WHITE);


	display->setCursor(19, 12);
	//display->setCursor(0, 12);
	blinkNumber(hours, currentSubMenu==SET_HOURS );
	display->print(":");
	blinkNumber(minutes, currentSubMenu==SET_MINUTES );

//	display->print(":");
//	display->print(clock->getSeconds());
	display->display();
}

MenuItem* ClockMenu::shortButtonPress() {
	switch (currentSubMenu) {
	case SHOW:
		return nextMenuItem;
		break;
	case SET_MINUTES:
		minutes = ++minutes % 60;
		return this;
		break;
	case SET_HOURS:
		hours = ++hours % 24;
		return this;
		break;
	default:
		return nextMenuItem;
		break;
	}
}

MenuItem* ClockMenu::longButtonPress() {
	switch( currentSubMenu ) {
		case SHOW:
			currentSubMenu = SET_MINUTES;
				break;
		case SET_MINUTES:
			currentSubMenu = SET_HOURS;
			break;
		case SET_HOURS:
			clock->setClock(hours, minutes, 0);
			currentSubMenu = SHOW;
			break;
		default:
			currentSubMenu = SHOW;
			break;
	}

	return this;
}
