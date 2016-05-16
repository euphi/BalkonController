#include <Homie.h>



#include "pcf8574.h"
#include "Safety.h"
#include "ValveNode.h"
#include "RGBWNode.h"
#include "SensorNode.h"

#include "BewaesserungFSM.h"

PCF8574 ioext(0x20);
Safety safety(ioext);

HomieNode pumpe("Pumpe", "switch");
bool pumpe_state(false);

HomieNode automode("Auto", "switch");
bool automatik = true;

ValveNode valves(ioext);
RGBWNode ledstrip;
SensorNode sensor;


bool pumpeHandler(String value) {
	Serial.print("DEBUG: pumpeHandler: ");
	Serial.println(value);
	bool rc = false;
	if (!automatik) {
		pumpe_state = (value == "true");
		rc = true;
		Homie.setNodeProperty(pumpe, "on", pumpe_state ? "true" : "false", false);
		ioext.write(0, pumpe_state);
	}
	else
	{
		Serial.println("Automatik on, ignoring command for pumpe");
	}
	return rc;
}

bool autoHandler(String value) {
	Serial.print("DEBUG: autoHandler: ");
	Serial.println(value);
	automatik = (value == "true");
	ioext.write(1, automatik);
	return true;
}

void setup() {
//	safety.init();

	Homie.disableResetTrigger();
	Homie.registerNode(pumpe);
	Homie.registerNode(automode);

	// HomieNode derived Nodes
	Homie.registerNode(ledstrip);
	Homie.registerNode(valves);
	Homie.registerNode(sensor);

	Homie.setup();

	pumpe.subscribe("on", pumpeHandler);
	automode.subscribe("on", autoHandler);
}

void loop() {
//	safety.loop();
	Homie.loop();
	//bewaesserung.cycle();
}
