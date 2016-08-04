/*
 * SerialLog.h
 *
 *  Created on: 03.08.2016
 *      Author: ian
 */

#ifndef SRC_STREAMLOG_H_
#define SRC_STREAMLOG_H_

#include <Arduino.h>
#include <StreamString.h>


class StreamLog: public StreamString {
public:
	StreamLog();

	void flush() {PublishCurrentLogString();};
	size_t write(const uint8_t *buffer, size_t size);

private:
	void PublishCurrentLogString();

};


extern StreamLog sLog;

#endif /* SRC_STREAMLOG_H_ */
