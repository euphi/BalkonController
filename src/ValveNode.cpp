/*
 * ValveNode.cpp
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#include "ValveNode.h"

ValveNode::ValveNode() {
	// TODO Auto-generated constructor stub

}

ValveNode::~ValveNode() {
	// TODO Auto-generated destructor stub
}


bool ValveNode::InputHandler(String property, String value) {
	Serial.printf("ValveNode::InputHandler received  property %s (value=%s).\n", property.c_str(), value.c_str());
	bool value_bool = value.equals("true");

	switch (property[0]) {
	case '1':
		valves[0] = value_bool;
		break;

	case '2':
		valves[1] = value_bool;
		break;

	case '3':
		valves[2] = value_bool;
		break;

	case '4':
		valves[3] = value_bool;
		break;
	default:
		return false;
	}
	updateValves();
	return true;

}

void ValveNode::updateValves() {
	Serial.print("Update Valves [1 2 3 4]: ");
	uint8_t port = ioext.read8();
	if (ioext.lastError())
	{
		Serial.println("updateValves: read8() failed.");
	}
	Serial.print(port,16);
	for (uint_fast8_t i=0;i<4;i++)
	{
		if (valves[i])
		{
			port |= (1 << (i+2));
		} else {
			port &= ~(1 << (i+2));
		}
		Serial.print(valves[i]? "x ": "- ");
	}
	Serial.println(port,16);
	ioext.write8(port);
	if (ioext.lastError())
	{
		Serial.println("updateValves: write8() failed.");
	}

}
