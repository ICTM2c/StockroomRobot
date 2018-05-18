// 
// 
// 

#include "Command.h"

void Command::addCommand(String command, int parameter) {
	if (command.compareTo("addToBin") || command.compareTo("start")) {
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
	if (head->command.compareTo("addToBin")) {
		_outgoing->addProduct(head->parameter);

		actionCompleted();
	}
	else if (head->command.compareTo("start")) {
		while (!_outgoing->start()) {
			busy = true;
		}

		actionCompleted();
	}
}