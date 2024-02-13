/*
 * Clock.h
 *
 *  Created on: 30.01.2024
 *      Author: Tim
 */

#ifndef SRC_SENSORS_CLOCK_H_
#define SRC_SENSORS_CLOCK_H_

class Clock {
public:
	Clock();
	virtual ~Clock();

	void setClock(int hr,int min,int sec);
	int getSeconds();
	int getMinutes();
	int getHours();
};

#endif /* SRC_SENSORS_CLOCK_H_ */
