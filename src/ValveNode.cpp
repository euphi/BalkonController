/*
 * ValveNode.cpp
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#include "ValveNode.h"
#include "Homie.hpp"

ValveNode::ValveNode(PCF8574& ioext): HomieNode("Ventil", "4Rel"), m_ioext(ioext), updateNeccessary(false) {
	_subscribeToAll = true;

}

bool ValveNode::InputHandler(String property, String value) {
	Serial.printf("ValveNode::InputHandler received  property %s (value=%s).\n", property.c_str(), value.c_str());
	bool value_bool = value.equals("true");

	uint_fast8_t id = property[0]-'1'; // Number valves from 1 to 4
	if (id >= 0 && id <= 3)
	{
		m_valves[id] = value_bool;
	}
	else
	{
		return false;
	}
	updateValves();
	PublishState(id+1);
	return true;

}

void ValveNode::PublishStates() const
{
	for (uint_fast8_t id=1; id<=4; id++)
		PublishState(id);
}

void ValveNode::PublishState(uint8_t id) const
{
	if (id<1 || id > 4) return;
	String id_string(id);
	Homie.setNodeProperty(*this, id_string, m_valves[id-1] ? "true":"false",true);
}


void ValveNode::updateValves() {
	Serial.print("Update Valves [1 2 3 4]: ");
	uint8_t port = m_ioext.read8();
	if (m_ioext.lastError())
	{
		Serial.println("updateValves: read8() failed.");
	}
	Serial.print(port,16);
	for (uint_fast8_t i=0;i<4;i++)
	{
		if (m_valves[i])
		{
			port |= (1 << (i+2));
		} else {
			port &= ~(1 << (i+2));
		}
		Serial.print(m_valves[i]? "x ": "- ");
	}
	Serial.println(port,16);
	m_ioext.write8(port);
	if (m_ioext.lastError())
	{
		Serial.println("updateValves: write8() failed.");
	}

}

void ValveNode::setup() {
	updateValves();
	PublishStates();
}

void ValveNode::loop() {
	if (updateNeccessary) {
		updateValves();
		updateNeccessary=false;
	}
}

void ValveNode::On(uint8_t id) {
	id--;
	if (id < sizeof(m_valves) )
	{
		m_valves[id] = true;
		updateNeccessary = true;
	}
	else
	{
		Serial.println("ValveNode::On: Invalid id");
	}
}

void ValveNode::Off(uint8_t id) {
	id--;
	if (id < sizeof(m_valves) )
	{
		m_valves[id] = false;
		updateNeccessary = true;
	}
	else
	{
		Serial.println("ValveNode::On: Invalid id");
	}
}

void ValveNode::AllOff() {
	Serial.println("ValveNode::AllOff()");
	for (uint_fast8_t i; i < sizeof(m_valves); i++) {
		m_valves[i] = false;
		updateValves();
	}

}
