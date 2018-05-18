#include "Arduino.h"
#include "LightSensor.h"


int LightSensor::targetPosition(int movePositions, int positionsMoved) {
	if (positionsMoved < movePositions) {
		if (GetDifference() > 200) {
			positionsMoved++;
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
int LightSensor::GetDifference() {
	return abs(GetCurrentValue() - _initialValue);
}