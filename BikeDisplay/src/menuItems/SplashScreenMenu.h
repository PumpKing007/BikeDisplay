/*
 * SplashScreenMenu.h
 *
 *  Created on: 28.01.2024
 *      Author: Tim
 */

#ifndef SRC_MENUITEMS_SPLASHSCREENMENU_H_
#define SRC_MENUITEMS_SPLASHSCREENMENU_H_

#include "MenuItem.h"

class SplashScreenMenu: public MenuItem {

public:
	SplashScreenMenu(Display *d) {
				display = d;
	};

	virtual ~SplashScreenMenu() {

	}

	void draw() {
		display->drawSplashScreen();
	}

	MenuItem* shortButtonPress(){
		return nextMenuItem;
	}

	MenuItem* longButtonPress(){
		return this;
	}
};

#endif /* SRC_MENUITEMS_SPLASHSCREENMENU_H_ */
