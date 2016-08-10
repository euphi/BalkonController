/*
 * SensorNode.cpp
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#include "SensorNode.h"
#include <Homie.hpp>

SensorNode::SensorNode() :
	HomieNode("Sensor", "sensor_t_p",
		[](String property, String value) { return false; }),
	lastLoop8000ms(0) {

	subscribeToAll();
}

void SensorNode::setup() {
	Wire.begin();
	Sensors::initialize();
	char printbuf[50];
	snprintf(printbuf, sizeof(printbuf),
			"Initialized sensors at %x (Thermo), %x (Baro)",
			Sensors::getThermometer(), Sensors::getBarometer());
	Serial.println(printbuf);
}

void SensorNode::loop() {
	if (millis() - lastLoop8000ms >= 8000UL || lastLoop8000ms == 0) {
		float cur_temp = Sensors::getThermometer()->getTemperature();
		float cur_press = Sensors::getBarometer()->getSealevelPressure(320.0);
		lastLoop8000ms = millis();
		Homie.setNodeProperty(*this, "degrees", String(cur_temp));
		Homie.setNodeProperty(*this, "hPa", String(cur_press));
	}
}

