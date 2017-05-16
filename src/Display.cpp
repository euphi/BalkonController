/*
 * Display.cpp
 *
 *  Created on: 13.08.2016
 *      Author: ian
 */

#include "Display.h"

Display::Display(): m_display(0x3c, SDA, SCL), m_msg_idx(0), m_ui(&m_display) {

}

void Display::setup() {
	 // Initialising the UI will init the display too.
	  m_display.init();

	  m_display.flipScreenVertically();
	  m_display.setFont(ArialMT_Plain_10);

}

void Display::loop() {
	static uint8_t loop_count = 0;
	static uint32_t last = 0;

	loop_count++;
	m_display.clear();
	m_display.setFont(ArialMT_Plain_10);
	m_display.drawStringMaxWidth(1, 1, 128, "Das Pferd frisst keinen Gurkensalat!");
	uint8_t fps = 1000 / (millis()- last);
	//m_display.setFont(ArialMT_Plain_10);
	String time_string(millis());
	time_string.concat(':');
	time_string.concat(loop_count);
	time_string.concat(':');
	time_string.concat(fps);
	m_display.drawString(1,52, time_string);
	m_display.display();
	last = millis();

}

uint8_t Display::showMessage() {
	uint8_t idx = m_msg_idx;
	return idx;
}

void Display::deleteMessage(uint8_t idx) {
}

Display disp;
