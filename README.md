IDIYA Grand Opening
===========

March 2015  
[Jenna deBoisblanc](http://jdeboi.com)

Ultrasonic Neopixel
-------------------

**Description**  
This circuit is designed to be an interactive badge for the IDIYA Grand Opening. The Neopixel is turned off until someone approaches. The Neopixel cycles through colors from green to red as someone/thing approaches the sensor. To set off the rainbow function (in order to demo the capabilities of the Neopixel), hold you hand close to the sensor. **To get it to work, upload GrandOpen1.ino and check out the circuit I've left at IDIYA.**

**Parts**:  
- Arduino
- 9V battery
- 9V battery clip
- breadboard
- Neopixel
- MaxSonar ultrasonic sensor
- 300-500Ω resistor connected to the data-in pin on the Neopixel (may not be 100% necessary)
- lots of jumpers

**Notes**:  
- 2 types of sensors to measure distance:
	1. The HC-SR04 sensor (two speaker bulbs) ---> Use GrandOpen0.ino
	2. The MaxSonar sensor (one speaker, pulled from robot car) ---> **Use GrandOpen1.ino**

- If using the MaxSensor (**recommended** since this is what I actually tested), two ways to measure distance via the code:
	1. Using an analog measurement (the only thing I got to work)- **connect pin3** on the sensor to an analog input pin on the Arduino.
	2. Using a PWM pin- connect pin2 on the sensor to a digital input pin on the Arduino and use the "pulseIn()" function to measure distance (currently commented out) 