#include "Command.h"
#include "Sorter.h"
#include "Engine.h"
#include "LightSensor.h"

#pragma once

Engine * sorter;

Command * commands = new Command(sorter);

void setup() {
	Serial.begin(9600);
	sorter->setup();
	loop();
}

/**
* Continuously loops to see if a command has been entered in the Serial or commands is giving permission to begin
* Sends a command to be queued if it receives ones
* Executes a command if no action is being performed
*/
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

/**
* Loops through the Serial input as a character array, splitting the command and parameters
* Passes the command and parameter to commands to be made into an action
*/
void queueCommand(String acquiredCommand) {
	String command;
	String parameter;

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