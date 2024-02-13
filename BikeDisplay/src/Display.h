/*
 * DSisplay.h
 *
 *  Created on: 24.01.2024
 *      Author: Tim
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <Adafruit_SSD1306.h>
#include <stdint.h>

class Display: public Adafruit_SSD1306
{
private:

	uint8_t currentDisplayedMode;

	enum displayModes {
		SPLASH_SCREEN = 0,
		OIL_TEMP = 1
	};
	uint8_t displayModesSize = 2;

public:
	Display();

	virtual ~Display();

	bool begin();

	void switchDisplayMode();

	void drawSplashScreen();

	void drawTemperature();

	void drawClock();

	void drawTest();


};

#endif /* SRC_DISPLAY_H_ */
