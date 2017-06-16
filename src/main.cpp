#include <Homie.h>

#include "Safety.h"
//#include "ValveNode.h"
#include "RGBWNode.h"
#include "ControllerNode.h"
#include "ConfigurationNode.h"

#include "BewaesserungFSM.h"

#include "SensorNode.h"
#include <RelaisNode.h>
#include <LoggerNode.h>


//Safety safety(ioext);

//ValveNode valves(ioext);
RGBWNode ledstrip("RGB", 15, 2, 0, 16);
RGBWNode ledstri2("RGB2", 14, 12, 13);

ControllerNode controller;
RelaisNode relais;
SensorNode sensor;

#include "buildnumber.h"
#define FW_NAME "Balkoncontroller"
#define FW_VERSION "4.0." BUILD_NUMBER

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */


/* *** Ventile ***

(von links nach rechts)
  X3 - 4: ^14
     - 3: ^15
     - 2: ^16
     - 1: ^13

  Relais:
  X9 - 1: 01
     - 2: 02
 ***************** */

void setup() {
//	safety.init();
	Homie_setFirmware(FW_NAME, FW_VERSION);
	Homie.disableResetTrigger();
	Homie.disableLedFeedback();

	Serial.begin(74880);
	Serial.println("Setup");
	Serial.flush();

	Homie.setLoggingPrinter(&Serial);
	LN.setLoglevel(LoggerNode::DEBUG);
	Homie.setup();

	bew_fsm.begin(controller, relais);
	bew_fsm.onSwitch();
}

void loop() {
	automaton.run();
//    safety.loop();
	bew_fsm.cycle();
	Homie.loop();
}
