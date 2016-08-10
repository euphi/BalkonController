/*
 * SerialLog.cpp
 *
 *  Created on: 03.08.2016
 *      Author: ian
 */

#include "StreamLog.h"
#include "LoggerNode.h"

StreamLog::StreamLog() {

}


void StreamLog::PublishCurrentLogString() {
	LN.log("SL", LoggerNode::INFO, *this);
	invalidate();
}


size_t StreamLog::write(const uint8_t *buffer, size_t size) {
	size_t rc = Print::write(buffer, size);
	if(this->operator [](this->length()-1) == '\n') {
		this->remove(this->length()-1);
		PublishCurrentLogString();
	}
	return rc;
}

StreamLog sLog;
