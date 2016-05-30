/*
 * BewaesserungFSM.h
 *
 *  Created on: 12.05.2016
 *      Author: ian
 */

#ifndef SRC_BEWAESSERUNGFSM_H_
#define SRC_BEWAESSERUNGFSM_H_

#include "pcf8574.h"
#include <Automaton.h>

class ControllerNode;
class ValveNode;

class BewaesserungFSM: public Machine {
private:
	ControllerNode* mp_ctrl;
	ValveNode*	mp_valves;
public:
	BewaesserungFSM();

	atm_timer_millis timer;

	enum {
		AUS, S1, S2, S3, S4
	}; // STATES
	enum {
		EV_START, EV_TIMER, ELSE
	}; // EVENTS

	enum { ACT_S1, ACT_S2, ACT_S3, ACT_S4, ACT_S1_OFF, ACT_S2_OFF, ACT_S3_OFF, ACT_S4_OFF, ACT_OFF }; // ACTIONS

	BewaesserungFSM& begin(ControllerNode& controller, ValveNode& valves);
	int event(int id);
	void action(int id);

	BewaesserungFSM& onSwitch(swcb_sym_t switch_callback);

};

extern BewaesserungFSM bew_fsm;


#endif /* SRC_BEWAESSERUNGFSM_H_ */
