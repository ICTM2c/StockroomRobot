// LightSensor.h

#ifndef _LIGHTSENSOR_h
#define _LIGHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

#include "Component.h"
#include "Arduino.h"

#pragma once

class Component;

//class Component;
//class Engine;

class LightSensor : public Component {
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

	bool targetPosition(int movePositions);

	int GetCurrentValue();

	int GetDifference();
};
