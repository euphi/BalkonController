# BalkonController
ESP8266 Irrigation control with 4 + 1 valves, a pump and as bonus RGB/White LED-Strip

## Software
- Build with platformio. platformio.ini contains dependencies to necessary libs, except Homie.
- This requires the latest GIT version of [Homie](https://github.com/marvinroger/homie-esp8266 (2.0 development))

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
- I2C on PINs 4/5
- BMP180 and PCF8574 connected to I2C
- ULN2803 (for LED PWM) connected to GPIO 12, 13, 14, 16
- Other 4 inputs of ULN2803 connected to Pin 3,4,5,6 of PCF8574
- Relais input (optocoppler) connected to Pin 1 & 2 of PCF8574
- COM of PCF8574 connected to 12V supply
- 1N4001 connected from each NO output of Relais to GND (Cathode at NO) (Freewheel diode - absolute mandatory!)
