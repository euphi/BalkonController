/*
 * Display.h
 *
 *  Created on: 13.08.2016
 *      Author: ian
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include "SSD1306.h"
#include "OLEDDisplayUi.h"


class Display {
public:
	Display();

	void setup();
	void loop();

	uint8_t showMessage();
	void deleteMessage(uint8_t idx);

private:
	SSD1306  m_display;
	OLEDDisplayUi m_ui;
	String m_msgs[4];
	uint8_t m_msg_idx;
};


extern Display disp;
#endif /* SRC_DISPLAY_H_ */
