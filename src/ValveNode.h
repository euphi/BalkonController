/*
 * ValveNode.h
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#ifndef SRC_VALVENODE_H_
#define SRC_VALVENODE_H_

#include "HomieNode.hpp"
#include "pcf8574.h"


class ValveNode: public HomieNode {

	  virtual bool InputHandler(String property, String value);

private:
	  bool m_valves[4] = { false, false, false, false };
	  void updateValves();
	  void PublishStates() const;
	  void PublishState(uint8_t valve) const;

	  PCF8574& m_ioext;

public:
	ValveNode(PCF8574& ioext);
	virtual ~ValveNode();
	void setup();
};

#endif /* SRC_VALVENODE_H_ */
