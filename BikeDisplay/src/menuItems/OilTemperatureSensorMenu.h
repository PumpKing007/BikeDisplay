/*
 * OilTemperatureSensorMenu.h
 *
 *  Created on: 28.01.2024
 *      Author: Tim
 */

#ifndef SRC_MENUITEMS_OILTEMPERATURESENSORMENU_H_
#define SRC_MENUITEMS_OILTEMPERATURESENSORMENU_H_

#include "../sensors/OilTemperatureSensor.h"
#include "MenuItem.h"

class OilTemperatureSensorMenu: public MenuItem {
private:
	OilTemperatureSensor* sensor;

public:
	OilTemperatureSensorMenu(Display *d, OilTemperatureSensor *sensor);

	void draw();

	MenuItem* shortButtonPress();

	MenuItem* longButtonPress();

	displayMode getId();
};

#endif /* SRC_MENUITEMS_OILTEMPERATURESENSORMENU_H_ */
