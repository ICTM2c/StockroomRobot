// LightSensor.h

#include "Arduino.h"

#pragma once

class LightSensor {
private:
	int _pin;
	long _initialValue;
public:

	LightSensor(int pin) {
		_pin = pin;
		setup();
	}

	void loop()
	{
		
	}

	/**
	* Set a basic value to differentiate from 
	*/
	void setup()
	{
		_initialValue = GetCurrentValue();
		Serial.println("DEBUG: LightSensor at pin " + (String)_pin + " initialized at " + (String)_initialValue + ".");
	}

	int targetPosition(int movePositions, int positionsMoved);

	int GetCurrentValue();

	unsigned int GetDifference();
};
