/*
 * Safety.h
 *
 *  Created on: 15.05.2016
 *      Author: ian
 *
 *      Purpose: Monitor values of valves and pump independently and apply safe action in case of violations
 *      E.g.:
 *        - Pump on too long
 *        - Pump on, but no valve open
 *        - Future Ideas: Add relay to switch on power supply for pump / valves only if Application is fully running.
 *
 *        - TODO: PCF8574 is not reset together with ESP8266
 */

#ifndef SRC_SAFETY_H_
#define SRC_SAFETY_H_

#include "pcf8574.h"
#include "Automaton.h"

class Safety {
private:
	PCF8574& ioext;
	bool initialized;
	Atm_timer timer;



public:
	Safety(PCF8574& io);
	void init();
	void loop();
};

#endif /* SRC_SAFETY_H_ */
