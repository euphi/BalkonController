/*
 * ControllerNode.cpp
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#include "ControllerNode.h"
#include "Homie.hpp"

ControllerNode::ControllerNode(PCF8574& ioext) :
		HomieNode("Controller", "controller",
				[](String property, String value) {return false;},
				true), m_ioext(ioext), mode(Manual) {

}

void ControllerNode::loop() {
}

void ControllerNode::setup() {
}

bool ControllerNode::setMode(String& value) {
	uint_fast8_t i = 0;
	for (i = (uint_fast8_t)Modes::Manual; i < (uint_fast8_t)Modes::Last_Mode; i++)
		if (value[0] == mode_char[i])
			break;
	if (mode == Modes::Last_Mode)
		return false;
	mode = (Modes)i;
	Serial.printf("Mode set to %c [%x]", mode_char[i], i);
	return true;
}

bool ControllerNode::setPumpe(String& value) {
	if (mode == Modes::Manual) {
		bool on = (value == "true");
		pumpe = on;
		m_ioext.write(0, pumpe);
		if (m_ioext.lastError()==0) {
			Homie.setNodeProperty(*this, PropString[Properties::Pumpe], pumpe?"true":"false");
		}
	} else {
		Serial.printf("Setting Pumpe state not allowed in mode [%c].\n",
				mode_char[mode]);
	}
	return true;
}

bool ControllerNode::setMainValve(String& value) {
	if (mode == Modes::Manual) {
		bool on = (value == "true");
		valve = on;
		m_ioext.write(1, valve);
		if (m_ioext.lastError()==0) {
			Homie.setNodeProperty(*this, PropString[Properties::MainValve], valve?"true":"false");
		}
	} else {
		Serial.printf("Setting main valve state not allowed in mode [%c].\n",
				mode_char[mode]);
	}
	return true;
}

bool ControllerNode::InputHandler(String property, String value) {
	Serial.printf(
			"ControllerNode::InputHandler received  property %s (value=%s).\n",
			property.c_str(), value.c_str());
	uint_fast8_t i = 0;
	for (i = (uint_fast8_t )Properties::Mode; i < (uint_fast8_t )Properties::LAST_Prop; i++) {
		if (property.equals(PropString[i]))
			break;
	}
	switch ((Properties)i) {
	case Properties::Mode:
		return setMode(value);
	case Properties::State:
		Serial.print("ControllerNode: Setting state not permitted.");
		return true;
	case Properties::Pumpe:
		return setPumpe(value);
	case Properties::MainValve:
		return setMainValve(value);
	default:
		return false;
	}
}
