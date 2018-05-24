// 
// 
// 

#include "Command.h"

/**
* Checks whether the acquired string is actually a command for the stockroomrobot
* If so, adds the command to the action linked list
*/
void Command::addCommand(String command, String parameter) {
	if (command.compareTo("addProduct") || command.compareTo("start") || command.compareTo("okay")) {
		_commandList.push_back(new CommandItem(command, parameter));
		Serial.println("DEBUG: " + command + " " + parameter + " added.");
	}
}

/**
* Check if there are actions in progress 
* This way the program doesn't continue while another action has not been completed
*/
bool Command::doingNothing() {
	return !_busy;
}

/**
* Confirm that an action has been completed
* Sets the next action as the new head of the list
* Sets busy to false, so the next action can be executed
*/
void Command::actionCompleted() {
	
}

/**
* Executes the first command in the list
* Checks what command it has received
* If addProduct: Loop through the parameter and split the coördinates, then pass them to Stockroom
* If start: start the Stockroom procedures
* If next: tell the Stockroom to drop one of the products on the spoon
*/
void Command::executeCommand() {
	String command = _commandList.front().getCommand();
	String parameter = _commandList.front().getParameter();

	if (parameter.compareTo("addProduct")) {
		int x = NULL;
		int y = NULL;

		int depth = 0;
		for (int i = 0; i < parameter.length(); i++) {
			if (depth == 0) {
				if (parameter[i] == ',' || !isdigit(parameter[i])) {
					depth++;
				}
				else {
					x += (int)parameter[i];
				}
			}
			else if (depth == 1) {
				if (parameter[i] == ',' || !isdigit(parameter[i])) {
					break;
				}
				else {
					y += (int)parameter[i];
				}
			}
		}

		if (!x || !y) {

		}
		else {
			_stockroom->addCoordinate(x, y);
		}
	}
	else if (command.compareTo("start")) {
		Serial.println("DEBUG: Stockroom procedure started.");
		
		while (!_stockroom->start()) {
			_busy = false;
		}

		Serial.println("DEBUG: Stockroom procedure ended.");

		actionCompleted();
	}
	else if (command.compareTo("next")) {
		Serial.println("DEBUG: Dropping cargo.");

		while (!_stockroom->dropCargo()) {
			_busy = true;
		}

		Serial.println("DEBUG: Cargo dropped.");

		actionCompleted();
	}
}