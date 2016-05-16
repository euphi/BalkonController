#include <Homie.h>

#include <Wire.h>

#define SENSORS_BMP180_ATTACHED
#include <Sensors.h>

#include <Wire.h>
#include "pcf8574.h"
#include "Safety.h"
#include "ValveNode.h"
#include "RGBWNode.h"
#include "BewaesserungFSM.h"

PCF8574 ioext(0x20);
Safety safety(ioext);

HomieNode pumpe("Pumpe", "switch");
bool pumpe_state(false);

HomieNode automode("Auto", "switch");
bool automatik = true;

HomieNode temperatur("Temperatur", "temp");
HomieNode pressure("Luftdruck", "press");

ValveNode valves(ioext);
RGBWNode ledstrip;


unsigned long lastLoop2000ms = 0;


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

void loopHandler() {
	 if (millis() - lastLoop2000ms >= 8000UL || lastLoop2000ms == 0) {
		 float cur_temp = Sensors::getThermometer()->getTemperature();
		 float cur_press = Sensors::getBarometer()->getSealevelPressure(320.0);
		 lastLoop2000ms = millis();
		 Homie.setNodeProperty(temperatur, "degrees", String(cur_temp));
		 Homie.setNodeProperty(temperatur, "hPa", String(cur_press));
	 }
}

void setup() {
//	safety.init();

	Homie.disableResetTrigger();
	Homie.registerNode(pumpe);
	Homie.registerNode(automode);
	Homie.registerNode(temperatur);
	Homie.registerNode(pressure);

	// HomieNode derived Nodes
	Homie.registerNode(ledstrip);
	Homie.registerNode(valves);

	Homie.setLoopFunction(loopHandler);
	Homie.setup();

	pumpe.subscribe("on", pumpeHandler);
	automode.subscribe("on", autoHandler);

	Wire.begin();
	Sensors::initialize();
	char printbuf[50];
	snprintf(printbuf,sizeof(printbuf), "Initialized sensors at %x (Thermo), %x (Baro)",
			Sensors::getThermometer(), Sensors::getBarometer());
	Serial.println(printbuf);

	valves.setup();
	ledstrip.setup();
}

void loop() {
//	safety.loop();
	Homie.loop();
	//bewaesserung.cycle();
}
