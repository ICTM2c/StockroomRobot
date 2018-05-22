// 
// 
// 

#include "Stockroom.h"

void Stockroom::addCoordinate(int x, int y) {
	coordinate *temp = new coordinate;

	temp->x = x;
	temp->y = y;
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

void Stockroom::nextCoordinate() {
	coordinate *temp = new coordinate;
	temp = current;
	current = temp->next;
	delete temp;
}

void Stockroom::finished() {
	while (head != NULL) {
		coordinate *temp = new coordinate;
		temp = head;
		head = head->next;
		delete temp;
	}
}

bool Stockroom::start() {
	moveToStockroom();
	findProducts();
	moveToSorter();

	Serial.write("Done");
	return true;
}

void Stockroom::moveToStockroom() {
	int stockroomReached = 0;
	
	while (stockroomReached < 1) {
		if (stockroomReached == 1) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(150, Clockwise);
		}

		stockroomReached = _stockroomXLocater->targetPosition(1, stockroomReached);
	}
}

void Stockroom::findProducts() {
	if (current == NULL) {
		current = head;
	}

	while (current->next != NULL) {
		coordinate * next = current->next;

		Direction directionX = (next->x > current->x) ? Clockwise : Counterclockwise;
		Direction directionY = (next->y > current->y) ? Clockwise : Counterclockwise;

		int moveX = (directionX == Clockwise) ? (next->x - current->x) : (current->x - next->x);
		int moveY = (directionY == Clockwise) ? (next->y - current->y) : (current->y - next->y);
		
		move(moveX, moveY, directionX, directionY);

		pickUp();

		nextCoordinate();
	}
}

void Stockroom::move(int x, int y, Direction directionX, Direction directionY) {
	int positionsMovedX = 0;
	int positionsMovedY = 0;

	while (positionsMovedX < x || positionsMovedY < y) {
		if (positionsMovedX == x) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(150, directionX);
		}

		if (positionsMovedY == y) {
			_yAxes->stop();
		}
		else {
			_yAxes->run(150, directionY);
		}

		positionsMovedX = _stockroomXLocater->targetPosition(x, positionsMovedX);
		positionsMovedY = _stockroomYLocater->targetPosition(y, positionsMovedY);
	}

	_xAxes->stop();
	_yAxes->stop();
}

void Stockroom::pickUp() {
	_spoon->write(90);
	delay(1000);
	_spoon->write(0);
}

void Stockroom::moveToSorter() {
	int positionsMovedX = 0;
	int positionsMovedY = 0;

	while (positionsMovedX < current->x || positionsMovedY < current->y) {
		if (positionsMovedX == current->x) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(150, Counterclockwise);
		}

		if (positionsMovedY == current->y) {
			_yAxes->stop();
		}
		else {
			_yAxes->run(150, Counterclockwise);
		}

		positionsMovedX = _stockroomXLocater->targetPosition(current->x, positionsMovedX);
		positionsMovedY = _stockroomYLocater->targetPosition(current->y, positionsMovedY);
	}

	_xAxes->stop();
	_yAxes->stop();

	int sorterReached = 0;

	while (sorterReached < 1) {
		if (sorterReached == 1) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(150, Counterclockwise);
		}

		sorterReached = _positionLocater->targetPosition(1, sorterReached);
	}

	int atDropHeight = 0;

	while (atDropHeight < 1) {
		if(atDropHeight == 1) {
			_yAxes->stop();
		}
		else {
			_yAxes->run(150, Clockwise);
		}

		atDropHeight = _positionLocater->targetPosition(1, atDropHeight);
	}

	finished();
}

bool Stockroom::dropCargo() {
	Serial.write("Okay");

	_spoon->write(90);
	delay(1000);
	_spoon->write(0);

	return true;
}