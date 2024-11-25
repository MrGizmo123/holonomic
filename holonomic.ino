/* Code for PICT Robotics FE Workshop 2024
 *
 * Date: 7 Nov 2024
 *
 * This code incorporates the networking, motor driving, sensor code
 * for the Holonomic Bot build.
 *
 * Contributors: Hrushikesh, Kaushal, Nimish, Toshit
 *
 */

/* Required for Dabble */
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>
#include <Arduino.h>

/* custom headers (also .ino files motor.ino, network.ino) */
#include "definitions.h"				/* constants */
#include "motor.h"							/* motor functions */

/* "Out" state */
volatile bool isOut = false;

void setup() {
	Serial.begin(115200);

	/* Initialize motor direction pins */
	setup_motors();

	/* Initialize Hall sensor and LED pins */
	pinMode(HALL_SENSOR_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	
	/* initialize dabble and set Bluetooth Name */
	Dabble.begin("Holonomic Hunter"); 
}

void loop() {
	
	if (!isOut && digitalRead(HALL_SENSOR_PIN))
	{
	  isOut = true;								/* bot is out */
	  digitalWrite(LED_PIN, HIGH); /* led should glow */
    Serial.println("OUT");

    move_in_direction(0,0);
	}

	/* This function handles the communication between phone and
	 * esp32 */
	Dabble.processInput();

	/* Only move the bot if it is not out */
	if (!isOut)
	{
		double scaling  = 255.0 / 7.0; 
		double velx = scaling * GamePad.getXaxisData();
		double vely = scaling * GamePad.getYaxisData();
		
		move_in_direction(velx, vely);
	}

  if(isOut)
   move_in_direction(0, 0);
	
}
