// 
// 
// 

#include "Command.h"

void Command::addCommand(String command, int parameter) {
	if (command.compareTo("moveToStockroom") || command.compareTo("moveUp") || command.compareTo("moveDown") || command.compareTo("moveLeft")
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

void Command::actionCompleted() {
	action *temp = new action;
	temp = head;
	head = head->next;
	delete temp;
}

void Command::executeCommand() {
	if (head->command.compareTo("moveToStockroom")) {
		_stockroom->moveToStockroom();
	}

	if (head->command.compareTo("moveUp")) {
		_stockroom->moveUp(head->parameter);
	}

	else if (head->command.compareTo("moveDown")) {
		_stockroom->moveDown(head->parameter);
	}

	else if (head->command.compareTo("moveLeft")) {
		_stockroom->moveLeft(head->parameter);
	}

	else if (head->command.compareTo("moveRight")) {
		_stockroom->moveRight(head->parameter);
	}

	else if (head->command.compareTo("pickUp")) {
		_stockroom->pickUp();
	}

	else if (head->command.compareTo("addToBin")) {
		_outgoing->sort(head->parameter);
	}
}