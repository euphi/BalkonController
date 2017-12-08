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


#include "buildnumber.h"
#define FW_NAME "Balkoncontroller"
#define FW_VERSION "4." COMMIT_COUNTER "." BUILD_NUMBER

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */


//Safety safety(ioext);

//ValveNode valves(ioext);
RGBWNode ledstrip( "RGB" , 15,  2,  0, 16);
RGBWNode ledstrip2("RGB2", 14, 12, 13, RGBWNode::NOPIN);

ControllerNode controller;
SensorNode sensor;

/* *** I/O Mapping *** *

  Ventile:
  X3 - 4: 14 (13)
     - 3: 15 (14)
     - 2: 16 (15)
     - 1: 13 (12)

  Relais:
  X9 - 1: ^01 (00)
     - 2: ^02 (01)

  Inputs:
  X8 - 1: GND
     - 2: 12 (11)
     - 3: 11 (10)
     - 4: 10 ( 9)
     - 5:  9 ( 8)

 * ******************* */

RelaisNode relais(0x0000, 0x0003, 0x0F00);

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
