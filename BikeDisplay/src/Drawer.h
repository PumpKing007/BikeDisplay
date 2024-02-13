/*
 * Drawer.h
 *
 *  Created on: 28.01.2024
 *      Author: Tim
 */

#include "Display.h"
#ifndef SRC_DRAWER_H_
#define SRC_DRAWER_H_

class Drawer
{
private:
	Display* display;

	public:
	Drawer()
	{

	}
	Drawer( Display *d ) {
		display = d;
	}

	void draw(){
		display->drawSplashScreen();
	}
};



#endif /* SRC_DRAWER_H_ */
