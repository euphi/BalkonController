# BalkonController
ESP8266 Irrigation control with 4 + 1 valves, a pump and as bonus RGB/White LED-Strip

**This is work in progress and there is no release yet! However, it already works fine for me.**

## Software
### Building
- Build with platformio. platformio.ini contains dependencies to necessary libs.
  - Configured to use with Eclipse
  - or use command line:
    `pio run`
  

### Features
- Able to switch valves and main pump and/or main valve over MQTT according to [Homie Convention](https://github.com/marvinroger/homie) using a PFC8574 I/O extension.
- Automatic mode (Proof of concept, under development) using the [Automaton framework](https://github.com/tinkerspy/Automaton)
- OpenHAB integration possible.
- 4 PWM outputs, configured for RGB led strip + white led strip.
- Support for BMP180 pressure and temperature sensor
- Logging  over MQTT (Thanks to the new [AsyncMQTT library for ESP](https://github.com/marvinroger/async-mqtt-client))


## Hardware
### Overview
- ESP8266 ESP-ADC DIL18 (http://wiki.in-circuit.de/index.php5?title=ESP8266EX)
- IO-Extension PCF8574 (I2C)
- BMP180 Temperature & Pressure sensor (I2C)
- 2 Relais Module
- ULN2803
- DC/DC Converter (set to 12V->3,3V)
- Waterpump 12V (actually 24V but works fine with 12V)
- 4x magnet valve
- 1x magnet valve
- IP68 Case
- various WAGO clamps
- CP1202 for programming

### Wiring
- I2C-Bus on PINs 4/5
- BMP180 and PCF8574 connected to I2C
- ULN2803 (for LED PWM) connected to GPIO 12, 13, 14, 16
- Other 4 inputs of ULN2803 connected to Pin 3,4,5,6 of PCF8574
- Relais input (optocoppler) connected to Pin 1 & 2 of PCF8574
- COM of PCF8574 connected to 12V supply
- 1N4001 connected from each NO output of Relais to GND (Cathode at NO) *(Freewheel diode - absolute mandatory!)*
  - ESP8266 is extremely sensitive to distortions on power supply (VCC / GND). Without the diodes I experienced resets even when switching on the relays and even with seperated 12V power supply for the relais.
  
## OpenHAB integration
**TO DO!** (works for me, but not yet published. To be documented here or in the Wiki.)
