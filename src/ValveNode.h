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
#include "BewaesserungFSM.h"

#include <array>


class ValveNode: public HomieNode {

	//virtual bool handleInput(const String  &property, const HomieRange& range, const String &value) override;
    virtual bool handleInput(const HomieRange& range, const String& property, const String& value) override;


private:
	  std::array<bool, 4>  m_valves { { false, false, false, false } };
	  void updateValves();
	  void PublishStates() const;
	  void PublishState(uint8_t valve) const;

	  PCF8574& m_ioext;
	  bool updateNeccessary;

public:
	ValveNode(PCF8574& ioext);
	void setup();
	void loop();
	void On(uint8_t id);
	void Off(uint8_t id);
	void AllOff();
};

#endif /* SRC_VALVENODE_H_ */
