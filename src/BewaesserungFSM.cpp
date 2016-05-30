/*
 * BewaesserungFSM.cpp
 *
 *  Created on: 12.05.2016
 *      Author: ian
 */

#include "BewaesserungFSM.h"

#include "ControllerNode.h"
#include "ValveNode.h"


BewaesserungFSM::BewaesserungFSM()
{
	class_label ="ABLAUF";
	timer.begin(this,ATM_COUNTER_OFF);
}

BewaesserungFSM& BewaesserungFSM::begin(ControllerNode& controller, ValveNode& valves) {
	const static state_t state_table[] PROGMEM = {
	/*            ON_ENTER    ON_LOOP  ON_EXIT   EV_START	EV_TIMER	ELSE */
	/* AUS  */		ACT_OFF,	-1,		-1,			S1,		-1,			-1,
	/* S1   */		ACT_S1,		-1,		ACT_S1_OFF,	-1,		S2,			-1,
	/* S2   */		ACT_S2,		-1,		ACT_S2_OFF,	-1,		S3,			-1,
	/* S3   */		ACT_S3, 	-1,		ACT_S3_OFF, -1,		S4,			-1,
	/* S4   */		ACT_S4,		-1,		ACT_S4_OFF,	-1,		AUS,		-1, };

	Machine::begin(state_table, ELSE);
	mp_ctrl = &controller;
	mp_valves = &valves;

	return *this;
}

int BewaesserungFSM::event(int id) {
	switch (id) {
	case EV_TIMER:
		return timer.expired();
	}
	return 0;
}

void BewaesserungFSM::action(int id) {
	switch (id) {
	case ACT_S1:
		mp_valves->On(1);
		mp_ctrl->PumpeOn();
		timer.set(2000);
		break;
	case ACT_S2:
		mp_valves->On(2);
		timer.set(2000);
		break;
	case ACT_S3:
		mp_valves->On(3);
		timer.set(2000);
		break;
	case ACT_S4:
		mp_valves->On(4);
		timer.set(2000);
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
	default:
		Serial.printf("BewaesserungFSM::action: Invalid id %x\n", id);
	}
}

BewaesserungFSM& BewaesserungFSM::onSwitch(swcb_sym_t switch_callback) {
	  Machine::onSwitch( switch_callback, "AUS\0S1\0S2\0S3\0S4", "EV_START\0EV_TIMER\0ELSE" );
	  return *this;
}



BewaesserungFSM bew_fsm;
