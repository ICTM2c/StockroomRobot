#include "Command.h"
#include "Component.h"
#include "Sorter.h"
#include "Engine.h"
#include "LightSensor.h"
#include <Servo\src\Servo.h>

Engine * sorter;

Command * commands = new Command(sorter);

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
		if (commands->doingNothing()) {
			commands->executeCommand();
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