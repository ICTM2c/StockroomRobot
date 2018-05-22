#pragma once

#include "Servo.h"
#include "Stockroom.h"
#include "Command.h"
#include "Engine.h"
#include "LightSensor.h"
#include <Servo.h>

Engine * xAxes = new Engine(0, 1);
Engine * yAxes = new Engine(1, 2);
LightSensor * stockroomXLocater = new LightSensor(3);
LightSensor * stockroomYLocater = new LightSensor(9);
Servo * spoon = new Servo();
LightSensor * positionLocater = new LightSensor(10);

Command * commands = new Command(xAxes, yAxes, stockroomXLocater, stockroomYLocater, spoon, positionLocater);

void setup() {
	Serial.begin(9600);
	spoon->attach(8);
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