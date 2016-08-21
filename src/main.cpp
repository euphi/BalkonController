#include <Homie.h>

#include "pcf8574.h"
#include "Safety.h"
#include "ValveNode.h"
#include "RGBWNode.h"
#include "SensorNode.h"
#include "ControllerNode.h"
#include "ConfigurationNode.h"
#include "Display.h"

PCF8574 ioext(0x20);

//Safety safety(ioext);

ValveNode valves(ioext);
RGBWNode ledstrip;
//SensorNode sensor;
ControllerNode controller(ioext);

void setup() {
//	safety.init();
	Serial.begin(115200);
	Serial.println("Start");
	Serial.flush();
	delay(500);

	Homie.disableResetTrigger();

	Homie.setup();
	bew_fsm.begin(controller, valves);
	bew_fsm.onSwitch();
	disp.setup();
}

void loop() {
	automaton.run();
//    safety.loop();
	bew_fsm.cycle();
	Homie.loop();
	disp.loop();
}
