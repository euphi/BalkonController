/*
 * SerialLog.cpp
 *
 *  Created on: 03.08.2016
 *      Author: ian
 */

#include "StreamLog.h"
#include "Homie.hpp"
#include "ConfigurationNode.h"

StreamLog::StreamLog() {
	// TODO Auto-generated constructor stub

}


void StreamLog::PublishCurrentLogString() {
	Serial.printf("MQTT-Logger **PCLS** %s (%d byte)\n", this->buffer, this->length());
	Serial.flush();
	config.log("SL", ConfigurationNode::INFO, *this);
	Homie.setNodeProperty(config, "log", this->buffer, false);
	invalidate();
}


size_t StreamLog::write(const uint8_t *buffer, size_t size) {
	size_t rc = Print::write(buffer, size);
	if(this->operator [](this->length()-1) == '\n') {
		PublishCurrentLogString();
	}
	return rc;
}

StreamLog sLog;
