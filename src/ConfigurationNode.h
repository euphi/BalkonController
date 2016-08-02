/*
 * ConfigurationNode.h
 *
 *  Created on: 11.06.2016
 *      Author: ian
 */

#ifndef SRC_CONFIGURATIONNODE_H_
#define SRC_CONFIGURATIONNODE_H_

#include "HomieNode.hpp"

class ConfigurationNode: public HomieNode {
public:
	ConfigurationNode();
	virtual void setup();
	//void loop(); // loop() not necessary

	uint16_t getValveDuration(uint_fast8_t v) const {
		return valveONduration[v];
	};

	enum E_Loglevel {DEBUG, INFO, ERROR, CRITICAL};

	static void log(const String function, const E_Loglevel level, const String text);
	static void logf(const String function, const E_Loglevel level, const char *format, ...);

	bool loglevel (E_Loglevel l) const { return ((uint_fast8_t) l >= (uint_fast8_t) m_loglevel);};



private:
	uint16_t valveONduration[4];
	E_Loglevel m_loglevel;

	void writeToEEPROM();
	void readFromEEPROM();


	static String levelstring[4];




};

extern ConfigurationNode config;

#endif /* SRC_CONFIGURATIONNODE_H_ */
