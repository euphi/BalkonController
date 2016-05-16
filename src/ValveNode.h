/*
 * ValveNode.h
 *
 *  Created on: 16.05.2016
 *      Author: ian
 */

#ifndef SRC_VALVENODE_H_
#define SRC_VALVENODE_H_

class ValveNode: public HomieNode {

	  virtual bool InputHandler(String property, String value);

private:
	  void updateValves();

public:
	ValveNode();
	virtual ~ValveNode();
};

#endif /* SRC_VALVENODE_H_ */
