// LightSensor.h

#ifndef _LIGHTSENSOR_h
#define _LIGHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

#pragma once

class LightSensor {
private:
	int _pin;
	int _initialValue;
public:

	LightSensor(int pin) {
		_pin = pin;
	}

	void loop()
	{
		
	}

	void setup()
	{
		_initialValue = GetCurrentValue();
	}

	int targetPosition(int movePositions, int positionsMoved);

	int GetCurrentValue();

	int GetDifference();
};
