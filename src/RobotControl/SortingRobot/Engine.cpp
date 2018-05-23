#include "Arduino.h"
#include "Engine.h"

void Engine::loop() {

}

void Engine::run(int speed, Direction direction, int overridePercentage) {
	int percentage = overridePercentage == -1 ? _maxOutputPercentage : overridePercentage;
	digitalWrite(_directionPin, direction == Direction::Clockwise ? HIGH : LOW);
	analogWrite(_powerPin, speed / 100 * percentage);

	Serial.println("Engine at pin + " + (String)_powerPin + " running at " + (String)speed + ".");
}

void Engine::stop() {
	digitalWrite(_directionPin, LOW);
	analogWrite(_powerPin, 0);
	Serial.println("Engine stopped.");
}
