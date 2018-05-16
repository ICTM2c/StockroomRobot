#include "Stockroom.h"
#include "Command.h"
#include "Component.h"
#include "Engine.h"
#include "LightSensor.h"

Engine * xAxes = new Engine(0, 1);
Engine * yAxes = new Engine(1, 2);
LightSensor * stockroomLocater = new LightSensor(3);
Engine * spoon = new Engine(4, 5);
Engine * sorter = new Engine(6,7);

Command * commands = new Command(xAxes, yAxes, stockroomLocater, spoon, sorter);

void setup() {
	Serial.begin(9600);
	loop();
}

void loop() {
	while (1) {
		if (Serial.available() > 0) {
			String acquiredCommand = Serial.readString();
			queueCommand(acquiredCommand);
		}
	}
}

void queueCommand(String acquiredCommand) {
	String command;
	int parameter = NULL;

	int depth = 0;
	for (int i = 0; i < acquiredCommand.length(); i++) {
		if (depth == 0) {
			if (acquiredCommand[i] == ' ') {
				depth++;
			}
			else {
				command += acquiredCommand[i];
			}
		}
		else {
			if (acquiredCommand[i] == ' ') {
				break;
			}
			else {
				parameter += acquiredCommand[i];
			}
		}
	}

	commands->addCommand(command, parameter);
}