#include <Homie.h>

#include <Wire.h>

#define SENSORS_BMP180_ATTACHED
#include <Sensors.h>

#include <Wire.h>
#include "pcf8574.h"
#include "Safety.h"
#include "BewaesserungFSM.h"

static const float percent_to_pwm = PWMRANGE / 100;

PCF8574 ioext(0x20);
Safety safety(ioext);

bool stripHandler(String property, String value); // Forward declaration
bool valveHandler(String property, String value); // Forward declaration

void updateLED(); // Forward declaration


HomieNode pumpe("Pumpe", "switch");
bool pumpe_state(false);

HomieNode automode("Auto", "switch");
bool automatik = true;

HomieNode temperatur("Temperatur", "temp");
HomieNode pressure("Luftdruck", "press");

HomieNode stripNode("LEDs", "RGBW", stripHandler, true); // last true: subscribe to all properties
HomieNode valveNode("Ventil", "4Rel", valveHandler, true);

//BewaesserungFSM bewaesserung(ioext);

enum RGB_MAP {
	R, G, B, W
};

enum RGBW_PINMAP {
	REDPIN = 12, GREENPIN = 13, BLUEPIN = 14, WHITEPIN = 16
};

const uint8 rgbw_pins[4] = {REDPIN, GREENPIN, BLUEPIN, WHITEPIN};

uint16 rgbw_values[4] = { 0, 0, 0, 0 };
bool valves[4] = { false, false, false, false };


unsigned long lastLoop2000ms = 0;

bool stripHandler(String property, String value) {
	Serial.printf("Striphandler received  property %s (value=%s).\n", property.c_str(), value.c_str());
	int value_int = value.toInt();
	switch (property[0]) {
	case 'r':
		rgbw_values[R] = round(value_int * percent_to_pwm);
		break;

	case 'g':
		rgbw_values[G] = round(value_int * percent_to_pwm);
		break;

	case 'b':
		rgbw_values[B] = round(value_int * percent_to_pwm);
		break;

	case 'w':
		rgbw_values[W] = round(value_int * percent_to_pwm);
		break;
	default:
		return false;
	}
	updateLED();
	return true;
}

bool valveHandler(String property, String value) {

}


void updateLED() {
	Serial.print("Update LED [rgbw rgb]: ");
	for (uint_fast8_t i=0;i<4;i++)
	{
		analogWrite(rgbw_pins[i], rgbw_values[i]);
		Serial.print(rgbw_values[i]);
		Serial.print('\t');
	}
	Serial.println('.');
}

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
	for (uint_fast8_t i=0;i<4;i++)
	{
		pinMode(rgbw_pins[i], OUTPUT);
		digitalWrite(rgbw_pins[i], 0);
	}

//	Homie.disableResetTrigger();
	Homie.registerNode(pumpe);
	Homie.registerNode(automode);
	Homie.registerNode(temperatur);
	Homie.registerNode(pressure);
	Homie.registerNode(stripNode);
	Homie.registerNode(valveNode);
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
}

void loop() {
//	safety.loop();
	Homie.loop();
	//bewaesserung.cycle();
}
