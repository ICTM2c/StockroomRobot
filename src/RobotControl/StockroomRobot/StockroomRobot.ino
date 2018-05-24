#pragma once

#include <ArduinoSTL.h>
#include "Servo.h"
#include "Stockroom.h"
#include "Command.h"
#include "Engine.h"
#include "LightSensor.h"
#include <Servo.h>

Engine * xAxes = new Engine(6, 7);
Engine * yAxes = new Engine(5, 4);
LightSensor * stockroomXLocater = new LightSensor(A1);
LightSensor * stockroomYLocater = new LightSensor(A0);
Servo * spoon = new Servo();
LightSensor * positionLocater = new LightSensor(A2);

Command * commands = new Command(xAxes, yAxes, stockroomXLocater, stockroomYLocater, spoon, positionLocater);

/**
* Open the serial connection, attach the spoon object to a port and pull it in and finally run engine setups
*/
void setup() {
	Serial.begin(9600);
	//spoon->attach(3);
	//spoon->write(160);

	delay(1000);
	stockroomXLocater->setup();
	stockroomYLocater->setup();
	positionLocater->setup();
	delay(500);
}

/**
* Continuously loops to see if a command has been entered in the Serial or commands is giving permission to begin
* Sends a command to be queued if it receives ones
* Executes a command if no action is being performed
*/
void loop() {
	queueCommand("addProduct 1,2");
	queueCommand("addProduct 3,4");
	queueCommand("addProduct 4,5");
	queueCommand("start");

		if (Serial.available() > 0) {
			String acquiredCommand = Serial.readString();
			queueCommand(acquiredCommand);
		}
		if (commands->doingNothing()) {
			commands->executeCommand();
		}
}

/**
* Loops through the Serial input as a character array, splitting the command and parameters
* Passes the command and parameter to commands to be made into an action
*/
void queueCommand(String acquiredCommand) {
	String CommandItem;
	String parameter;

	int depth = 0;
	for (int i = 0; i < acquiredCommand.length(); i++) {
		if (depth == 0) {
			if (acquiredCommand[i] == ' ') {
				depth++;
			}
			else {
				CommandItem += acquiredCommand[i];
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

	commands->addCommand(CommandItem, parameter);
}