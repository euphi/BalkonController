/*
 * Safety.cpp
 *
 *  Created on: 15.05.2016
 *      Author: ian
 */

#include "Safety.h"

Safety::Safety(PCF8574& io): ioext(io), initialized(false) {
	// TODO Auto-generated constructor stub

}


void Safety::init() {
	Serial.println("Safety initialized.");
	timer.begin(5000,-1);
	int i = 1;
	//timer.onTimer([] ( int idx, int v, int up ) {Serial.print("Lambda!");}, 0);
	timer.onTimer([this] ( int idx, int v, int up ) {this->loop();}, 0);



}


	initialized = true;
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

