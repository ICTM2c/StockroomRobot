// Engine.h
#include "arduino.h"

#pragma once

enum Direction {
	Clockwise,
	Counterclockwise,
};

class Engine {
private:
	int _powerPin;
	int _directionPin;
	int _maxOutputPercentage = 100;
public:
	Engine(int powerPin, int directionPin) {
		_powerPin = powerPin;
		_directionPin = directionPin;
	}

	// No additional setup required
	void setup() {
		pinMode(_powerPin, OUTPUT);
		pinMode(_directionPin, OUTPUT);
	}

	/**
	* Sets maximum output percentage.
	* Whenever the run method is called the actual speed will be calculated using the percentage.
	*/
	void setOutputPercentage(int percentage) {
		_maxOutputPercentage = percentage;
	}

	void loop();

	/**
	* Tells the engine to run at a certain speed in a specific direction.
	* The resulting speed will be a percentage of the configured maximum output percentage.
	* This can be overriden with the percentageOverride parameter
	*/
	void run(int speed, Direction direction, int percentageOverride = -1);

	/**
	* Completely stops the engine
	*/
	void stop();
};