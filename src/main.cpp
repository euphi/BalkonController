#include <Homie.h>

#include "Safety.h"
//#include "ValveNode.h"
#include "RGBWNode.h"
#include "ControllerNode.h"
#include "ConfigurationNode.h"

//#include "BewaesserungFSM.h"

//#include "SensorNode.h"
#include <HomieBME280Node.h>

#include <RelaisNode.h>
#include <LoggerNode.h>


#include "buildnumber.h"
#define FW_NAME "Balkoncontroller"
#define FW_VERSION "5." COMMIT_COUNTER "." BUILD_NUMBER


//Safety safety(ioext);

LoggerNode LN;
RGBWNode ledstrip( "RGB" , 15,  2,  0, 16);
RGBWNode ledstrip2("RGB2", 14, 12, 13, RGBWNode::NOPIN);

ControllerNode controller;
HomieBME280Node sensor;

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

RelaisNode relais(0x0000, 0x0003, 0x0F00);  // init all to zero (OFF), invert IO 1 and 2 (0x0003), and configure 9-12 (0x0F00) as INPUT

void setup() {
//	safety.init();
	Homie_setFirmware(FW_NAME, FW_VERSION);
	Homie.disableResetTrigger();
	Homie.disableLedFeedback();

	Serial.begin(74880);
	Serial.println("Setup");
	Serial.flush();

	Wire.begin(SDA, SCL);
	Wire.setClockStretchLimit(1000);
	Homie.setLoggingPrinter(&Serial);
	LN.setLoglevel(LoggerNode::DEBUG);
	Homie.setup();

	//bew_fsm.begin(controller, relais);
	//bew_fsm.onSwitch();
}

void loop() {
	//automaton.run();
//    safety.loop();
	//bew_fsm.cycle();
	Homie.loop();
}
