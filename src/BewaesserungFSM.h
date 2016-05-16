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

class BewaesserungFSM: public Machine {
public:
	BewaesserungFSM(PCF8574& _extio);

	virtual ~BewaesserungFSM();

	atm_timer_millis timer;

	enum {
		AUS, S1, S2, S3, S4
	}; // STATES
	enum {
		EV_START, EV_TIMER, ELSE
	}; // EVENTS

	enum { ACT_S1, ACT_S2, ACT_S3, ACT_S4, ACT_OFF }; // ACTIONS

	PCF8574& extio;


	BewaesserungFSM& begin(PCF8574& extio);
	int event(int id);
	void action(int id);

};

#endif /* SRC_BEWAESSERUNGFSM_H_ */
