/*
 * Safety.h
 *
 *  Created on: 15.05.2016
 *      Author: ian
 */

#ifndef SRC_SAFETY_H_
#define SRC_SAFETY_H_

#include "pcf8574.h"

class Safety {
private:
	PCF8574& ioext;
	bool initialized;


public:
	Safety(PCF8574& io);
	virtual ~Safety();
	void init();
	void loop();
};

#endif /* SRC_SAFETY_H_ */
