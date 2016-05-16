/*
 * ControllerNode.h
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#ifndef SRC_CONTROLLERNODE_H_
#define SRC_CONTROLLERNODE_H_

#include <HomieNode.hpp>
#include "pcf8574.h"

class ControllerNode: public HomieNode {

	enum Properties {Mode, State, Pumpe, MainValve, LAST_Prop};
	const String PropString[LAST_Prop] = {"Mode", "State", "Pumpe", "MainValve"};

	enum Modes {Manual, Full_Auto, Off, Last_Mode};
	const char mode_char[Last_Mode] = { 'm', 'a', '0' };





private:
	Modes mode;
	bool pumpe;
	bool valve;

	PCF8574& m_ioext;

	bool setMode(String& value);
	bool setPumpe(String& value);
	bool setMainValve(String& value);

public:
	ControllerNode(PCF8574& ioext);

	virtual void loop();
	virtual void setup();
    virtual bool InputHandler(String property, String value);


};

#endif /* SRC_CONTROLLERNODE_H_ */
