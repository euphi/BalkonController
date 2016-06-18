/*
 * ConfigurationNode.cpp
 *
 *  Created on: 11.06.2016
 *      Author: ian
 */

#include "ConfigurationNode.h"

#include <EEPROM.h>

ConfigurationNode::ConfigurationNode(): HomieNode("Config", "cfg") {
	_subscribeToAll = true;

}

void ConfigurationNode::writeToEEPROM() {
}

void ConfigurationNode::readFromEEPROM() {
}

