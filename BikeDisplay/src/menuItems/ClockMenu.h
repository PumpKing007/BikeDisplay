/*
 * ClockMenu.h
 *
 *  Created on: 30.01.2024
 *      Author: Tim
 */

#ifndef SRC_MENUITEMS_CLOCKMENU_H_
#define SRC_MENUITEMS_CLOCKMENU_H_

#include "MenuItem.h"
#include "../sensors/Clock.h"

class ClockMenu: public MenuItem {
private:
	Clock* clock;

	void blinkNumber( int number , bool blink );

public:
	ClockMenu(Display *d, Clock *clock);
	virtual ~ClockMenu();

	void draw();

	MenuItem* shortButtonPress();

	MenuItem* longButtonPress();

	displayMode getId();
};

#endif /* SRC_MENUITEMS_CLOCKMENU_H_ */
