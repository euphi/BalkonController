/*
 * Safety.cpp
 *
 *  Created on: 15.05.2016
 *      Author: ian
 */

#include "Safety.h"

Safety::Safety(PCF8574& io): ioext(io), initialized(false), m_last(0) {
	// TODO Auto-generated constructor stub

}


void Safety::init() {
	Serial.println("Safety initialized.");
}

void Safety::loop() {
	uint16_t now = millis();
	if (now - m_last > 1000)
	{
		Serial.print("Safety Check: ");

		m_last = now;
		Serial.println("not yet implemented");
	}
}

