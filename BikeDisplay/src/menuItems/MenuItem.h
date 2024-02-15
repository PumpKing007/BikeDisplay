/*
 * MenuItem.h
 *
 *  Created on: 28.01.2024
 *      Author: Tim
 */

#ifndef SRC_MENUITEMS_MENUITEM_H_
#define SRC_MENUITEMS_MENUITEM_H_

#include "../Display.h"

enum displayMode {
	SPLASH_SCREEN = 0,
	OIL_TEMP = 1, CLOCK = 2
};

// command interface
class MenuItem {
protected:
	MenuItem* nextMenuItem;
public:
	Display* display;



//	MenuItem(Display *d ) {
//		display = d;
//	}

	void setNextMenuItem( MenuItem* nextMenuItem );

	virtual void draw();

	virtual MenuItem* shortButtonPress();

	virtual MenuItem* longButtonPress();

	virtual displayMode getId();
};


#endif /* SRC_MENUITEMS_MENUITEM_H_ */
