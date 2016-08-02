/*
 * ConfigurationNode.cpp
 *
 *  Created on: 11.06.2016
 *      Author: ian
 */

#include "ConfigurationNode.h"
#include "Homie.hpp"

#include <EEPROM.h>

ConfigurationNode::ConfigurationNode() : m_loglevel(INFO),
		HomieNode("Config", "cfg") {
	_subscribeToAll = true;

}

String ConfigurationNode::levelstring[4] = {"DEBUG", "INFO", "ERROR", "CRITICAL"};

void ConfigurationNode::setup() {
	Serial.println("ConfigurationNode::setup()");
}

void ConfigurationNode::writeToEEPROM() {
}

void ConfigurationNode::readFromEEPROM() {
}

void ConfigurationNode::log(const String function, const E_Loglevel level, const String text) {
	if (!config.loglevel(level)) return;

	Serial.printf("MQTT-Logger %s: %s: %s\n", function.c_str(), levelstring[level].c_str(), text.c_str());
	String mqtt_path(function);
	mqtt_path.concat(':');
	mqtt_path.concat(levelstring[level]);
    Homie.setNodeProperty(config, mqtt_path, text, false);


}

void ConfigurationNode::logf(const String function, const E_Loglevel level,	const char* format, ...) {
	if (!config.loglevel(level)) return;
	va_list arg;
	va_start(arg, format);
	char temp[100];
	char* buffer = temp;
	size_t len = vsnprintf(temp, sizeof(temp), format, arg);
	va_end(arg);
	log(function, level, temp);
}

ConfigurationNode config;
