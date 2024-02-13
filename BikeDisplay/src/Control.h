/*
 * Control.h
 *
 *  Created on: 27.01.2024
 *      Author: Tim
 */

#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_

enum ButtonState {
				STATE_LOW = 0, STATE_HIGH = 1, STATE_LONG_HIGH = 2
			};

class Control
{
public:
	Control();

	void buttonPressed();

	void buttonReleased();

	ButtonState getButtonState();


};


#endif /* SRC_CONTROL_H_ */
