#include <Homie.h>

#include "pcf8574.h"
#include "Safety.h"
#include "ValveNode.h"
#include "RGBWNode.h"
#include "SensorNode.h"
#include "ControllerNode.h"
//#include "ConfigurationNode.h"

PCF8574 ioext(0x20);
Safety safety(ioext);

ValveNode valves(ioext);
RGBWNode ledstrip;
SensorNode sensor;
ControllerNode controller(ioext);

void setup() {
	safety.init();

	Homie.disableResetTrigger();

	// HomieNode derived Nodes
	Homie.registerNode(ledstrip);
	Homie.registerNode(valves);
	Homie.registerNode(sensor);
	Homie.registerNode(controller);
//	Homie.registerNode(config);

	Homie.setup();
	bew_fsm.begin(controller, valves);
	bew_fsm.onSwitch();
}

void loop() {
	automaton.run();
    safety.loop();
//	bew_fsm.cycle();
	Homie.loop();
}
