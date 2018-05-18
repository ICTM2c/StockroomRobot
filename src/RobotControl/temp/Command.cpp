// 
// 
// 

#include "Command.h"

void Command::addCommand(String command, int parameter) {
	if (command.compareTo("addProduct") || command.compareTo("start") || command.compareTo("moveDown") || command.compareTo("moveLeft")
		|| command.compareTo("moveRight") || command.compareTo("pickUp") || command.compareTo("addToBin")) {
		action *temp = new action;

		temp->command = command;
		temp->parameter = parameter;
		temp->next = NULL;

		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}
}

bool Command::doingNothing() {
	return busy;
}

void Command::actionCompleted() {
	action *temp = new action;
	temp = head;
	head = head->next;
	delete temp;

	busy = false;
}

void Command::executeCommand() {
	if (head->command.compareTo("addProduct")) {
		String parameter = head->parameter;
		int x = NULL;
		int y = NULL;
		int bin = NULL;

		int depth = 0;
		for (int i = 0; i < parameter.length(); i++) {
			if (depth == 0) {
				if (parameter[i] == ',' || !isdigit(parameter[i])) {
					depth++;
				}
				else {
					x += parameter[i];
				}
			}
			else if (depth == 1) {
				if (parameter[i] == ',' || !isdigit(parameter[i])) {
					depth++;
				}
				else {
					y += parameter[i];
				}
			}
			else {
				if (parameter[i] == ',' || !isdigit(parameter[i])) {
					break;
				}
				else {
					bin += parameter[i];
				}
			}
		}

		if (!x || !y || !bin) {
			
		}
		else {
			_stockroom->addCoordinate(x, y);
			_sorter->addBin(bin);
		}
	}

	if (head->command.compareTo("start")) {
		while (!_stockroom->start()) {
			busy = true;
		}

		actionCompleted();
	}

	else if (head->command.compareTo("addToBin")) {
		while (!_outgoing->sort(head->parameter)) {
			busy = true;
		}

		actionCompleted();
	}
}