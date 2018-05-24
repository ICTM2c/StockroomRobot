#include "LightSensor.h"

/**
* Track how many positions the stockroomrobot has moved
* Takes a move target and the number of positions the robot has already moved, so both axes can move simultaniously
*/
int LightSensor::targetPosition(int movePositions, int positionsMoved) {
	if (positionsMoved < movePositions) {
		if (GetDifference() > 200) {
			positionsMoved++;
			//Serial.println("DEBUG: LightSensor -> Significant measurement at pin " + (String)_pin + " of " + (String)GetDifference() + " measured. Now at " + (String)positionsMoved + ".");
		}
	}

	return positionsMoved;
}

/**
* Returns the analog value on the pin which the light sensor is attached to.
*/
int LightSensor::GetCurrentValue() {
	return analogRead(_pin);
}

/**
* Returns the absolute difference between the original value and the current value.
*/
unsigned int LightSensor::GetDifference() {
	return abs(_initialValue - GetCurrentValue());
}