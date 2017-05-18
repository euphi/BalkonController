/*
 * ControllerNode.cpp
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#include "ControllerNode.h"
#include "Homie.hpp"
#include "BewaesserungFSM.h"
#include "ConfigurationNode.h"
#include "LoggerNode.h"

ControllerNode::ControllerNode(PCF8574& ioext) :
		HomieNode("Controller", "controller"),
		m_ioext(ioext), mode(Modes::Manual), mode_1run_saved_state(Modes::Invalid),
		pumpe(false), valve(false) {
	for (int i = 0; i < LAST_Prop; i++) {
		advertise(PropString[i].c_str()).settable();
	}
}


void ControllerNode::loop() {
	if (mode_1run_saved_state) { // 1run läuft
		if (bew_fsm.state() == BewaesserungFSM::ACT_OFF) {
			Serial.println("OneRun finished()");
			mode = mode_1run_saved_state;
			mode_1run_saved_state = Modes::Invalid;
			setProperty(PropString[State]).send(String(mode_char[mode]));
		}
	}
}

void ControllerNode::setup() {

}

bool ControllerNode::startOneRun() {
	mode_1run_saved_state = mode;
	bew_fsm.trigger(BewaesserungFSM::EV_START);
	return true;
}


bool ControllerNode::setMode(String const & value) {
	int_fast8_t i = 0;
	for (i = (int_fast8_t)Modes::Manual; i < (int_fast8_t)Modes::Last_Mode; i++)
		if (value[0] == mode_char[i])
			break;
	if (i == Modes::Last_Mode)
		return false;
	if (i == Modes::OneRun)
	{
		startOneRun();
	}
	mode = (Modes)i;
	setProperty(PropString[State]).send(String(mode_char[mode]));
	Serial.printf("Mode set to %c [%x].\n", mode_char[i], i);
	return true;
}

bool ControllerNode::setPumpe(String const & value) {
	if (mode == Modes::Manual) {
		bool on = (value == "true");
		PumpeSet(on);
	} else {
		Serial.printf("Setting Pumpe state not allowed in mode [%c].\n",
				mode_char[mode]);
	}
	return true;
}

bool ControllerNode::setMainValve(String const & value) {
	if (mode == Modes::Manual) {
		bool on = (value == "true");
		valve = on;
		ValveSet(on);
	} else {
		Serial.printf("Setting main valve state not allowed in mode [%c].\n",
				mode_char[mode]);
	}
	return true;
}
bool ControllerNode::handleInput(const String  &property, const HomieRange& range, const String &value) {
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
		Serial.println("ControllerNode: Setting state not permitted.");
		return true;
	case Properties::Pumpe:
		return setPumpe(value);
	case Properties::MainValve:
		return setMainValve(value);
	default:
		return false;
	}
}

void ControllerNode::PumpeSet(bool on) {
	m_ioext.write(0, !on); // Ausgang invertiert
	int rc = m_ioext.lastError();
	if (rc==0) {
		setProperty(PropString[Properties::Pumpe]).send(on?"true":"false");
	}
	else {
		LN.logf(__PRETTY_FUNCTION__, LoggerNode::ERROR,"Error %x", rc );
	}

}

void ControllerNode::ValveSet(bool on) {
	m_ioext.write(1, on);
	int rc = m_ioext.lastError();
	if (rc==0) {
		setProperty(PropString[Properties::MainValve]).send(on?"true":"false");
	}
	else {
		Serial.printf("ERROR writing MainValve on IO extension (%x)", rc);
	}
}

void ControllerNode::PumpeOn() {
	Serial.println("ControllerNode::PumpeOn()");
	PumpeSet(true);
}

void ControllerNode::PumpeOff() {
	Serial.println("ControllerNode::PumpeOff()");
	PumpeSet(false);
}

void ControllerNode::ValveOn() {
	Serial.println("ControllerNode::ValveOn()");
	ValveSet(true);
}

void ControllerNode::ValveOff() {
	Serial.println("ControllerNode::ValveOff()");
	ValveSet(false);
}
