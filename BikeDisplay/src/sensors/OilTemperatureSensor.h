/*
 * OilTemperatureSensor.h
 *
 *  Created on: 28.01.2024
 *      Author: Tim
 */

#ifndef SRC_SENSORS_OILTEMPERATURESENSOR_H_
#define SRC_SENSORS_OILTEMPERATURESENSOR_H_

#include<stdint.h>

class OilTemperatureSensor {

public:
	OilTemperatureSensor();

	int readTemp();


};



#endif /* SRC_SENSORS_OILTEMPERATURESENSOR_H_ */
