/*
 * BewaesserungFSM.cpp
 *
 *  Created on: 12.05.2016
 *      Author: ian
 */

#include "BewaesserungFSM.h"

#include "ControllerNode.h"
#include "ValveNode.h"
#include "ConfigurationNode.h"
#include "LoggerNode.h"
#include "StreamLog.h"

#include <EEPROM.h>

BewaesserungFSM::BewaesserungFSM()
{
	//class_label ="ABLAUF";
	//timer.begin(this,ATM_COUNTER_OFF);
	timer.set(ATM_COUNTER_OFF);
}

uint16_t BewaesserungFSM::state_duration[S4] = {5000, 2000, 6000, 3000};


BewaesserungFSM& BewaesserungFSM::begin(ControllerNode& controller, ValveNode& valves) {
	const static state_t state_table[] PROGMEM = {
	/*            ON_ENTER    ON_LOOP  ON_EXIT   EV_START	EV_TIMER	ELSE */
	/* AUS  */		ACT_OFF,	-1,		-1,			S1,		-1,			-1,
	/* S1   */		ACT_S1,		-1,		ACT_S1_OFF,	-1,		S2,			-1,
	/* S2   */		ACT_S2,		-1,		ACT_S2_OFF,	-1,		S3,			-1,
	/* S3   */		ACT_S3, 	-1,		ACT_S3_OFF, -1,		S4,			-1,
	/* S4   */		ACT_S4,		-1,		ACT_S4_OFF,	-1,		AUS,		-1, };

	uint16_t width = ELSE + 2 + ATM_ON_EXIT;
	for (uint_fast8_t i = S1; i <= S4; i++) {
		uint16_t duration = 0;
		EEPROM.get(i-1, duration);
		duration+=500;
		Serial.printf("Read EEPROM for state %x duration: %is\n.", i, duration);
		state_duration[i-1] = duration;
	}

	Machine::begin(state_table, ELSE);
	mp_ctrl = &controller;
	mp_valves = &valves;

	return *this;
}

int BewaesserungFSM::event(int id) {
	switch (id) {
	case EV_TIMER:
		return timer.expired(this);
	}
	return 0;
}

void BewaesserungFSM::action(int id) {
	uint16_t duration = 0;
	switch (id) {
	case ACT_S1:
		duration = state_duration[S1-1];
		mp_ctrl->PumpeOn();
		if (duration > 0) mp_valves->On(1);
		timer.set(duration);
		break;
	case ACT_S2:
		duration = state_duration[S2-1];
		if (duration > 0) mp_valves->On(2);
		timer.set(duration);
		break;
	case ACT_S3:
		duration = state_duration[S3-1];
		if (duration > 0) mp_valves->On(3);
		timer.set(duration);
		break;
	case ACT_S4:
		duration = state_duration[S4-1];
		if (duration > 0) mp_valves->On(4);
		timer.set(duration);
		break;
	case ACT_S1_OFF:
		mp_valves->Off(1);
		break;
	case ACT_S2_OFF:
		mp_valves->Off(2);
		break;
	case ACT_S3_OFF:
		mp_valves->Off(3);
		break;
	case ACT_S4_OFF:
		mp_valves->Off(4);
		break;
	case ACT_OFF:
		mp_valves->AllOff();
		mp_ctrl->PumpeOff();
		timer.set(ATM_COUNTER_OFF);
		break;
	case ATM_NOP:
	case ATM_SLEEP:
	case ATM_ON_SWITCH:
		return; // NOP/SLEEP/ON_SWITCH: No action
	default:
		LN.logf(__PRETTY_FUNCTION__, LoggerNode::ERROR,"Invalid id %x", id);
		return;
	}
}

BewaesserungFSM& BewaesserungFSM::onSwitch() {
	  Machine::setTrace(&sLog, atm_serial_debug::trace, "Ablaufsteuerung\0EV_START\0EV_TIMER\0ELSE\0AUS\0S1\0S2\0S3\0S4" );
	  return *this;
}



BewaesserungFSM bew_fsm;
