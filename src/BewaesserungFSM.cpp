/*
 * BewaesserungFSM.cpp
 *
 *  Created on: 12.05.2016
 *      Author: ian
 */

#include "BewaesserungFSM.h"

BewaesserungFSM::BewaesserungFSM(PCF8574& _extio):	extio(_extio)
{
	class_label ="ABLAUF";
}

BewaesserungFSM::~BewaesserungFSM() {
	// TODO Auto-generated destructor stub
}

BewaesserungFSM& BewaesserungFSM::begin(PCF8574& extio) {
	const static state_t state_table[] PROGMEM = {
	/*            ON_ENTER    ON_LOOP  ON_EXIT   EV_START	EV_TIMER	ELSE */
	/* AUS  */		ACT_OFF,	-1,		-1,			S1,		-1,			-1,
	/* S1   */		ACT_S1,		-1,		-1,			-1,		S2,			-1,
	/* S2   */		ACT_S2,		-1,		-1,			-1,		S3,			-1,
	/* S3   */		ACT_S3, 	-1,		-1,			-1,		S4,			-1,
	/* S4   */		ACT_S4,		-1,		-1,			-1,		AUS,		-1, };

	Machine::begin(state_table, ELSE);

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
	{
		uint8_t value = extio.read8();
		value &= 0xFC;
		switch (id) {
		case ACT_S1:
			value |= 1 << 2;
			break;
		case ACT_S2:
			value |= 1 << 3;
			break;
		case ACT_S3:
			value |= 1 << 4;
			break;
		case ACT_S4:
			value |= 1 << 5;
			break;
		case ACT_OFF:
			break;
		}
		extio.write8(value);
	}

}
