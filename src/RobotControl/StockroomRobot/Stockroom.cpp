// 
// 
// 

#include "Stockroom.h"

/**
* Adds a coordinate to the coordinate linked list
* If no coordinates have been added yet, set head to x = 1 & y = 1
*/
void Stockroom::addCoordinate(int x, int y) {
	coordinate *temp = new coordinate;

	temp->x = x;
	temp->y = y;
	temp->next = NULL;

	if (head == NULL) {
		current = temp;
		
		head->x = 1;
		head->y = 1;
		head->next = current;

		tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}

	delete temp;

	Serial.println("DEBUG: addCoordinate head -> " + (String) head->x + ", " + (String) head->y + ", current -> " + (String) current->x + ", " + (String)current->y + ".");
}

/**
* Sets the new coordinate as the head
* Picks the next coordinate to go to out of the list and set current to it
*/
void Stockroom::nextCoordinate() {
	head = current;
	
	coordinate *temp = new coordinate;
	temp = head;
	head = temp->next;
	delete temp;
}

/** 
* Deletes the linked list when all products have been gathered
*/
void Stockroom::finished() {
	while (head != NULL) {
		coordinate *temp = new coordinate;
		temp = head;
		head = head->next;
		delete temp;
	}

	delete current;
}

/**
* Start the Stockroom procedure:
* Move to the stockroom
* Find the products in the linked list
* Move back to the sorter
*/
bool Stockroom::start() {
	Serial.println("DEBUG: Stockroom procedure started.");

	//moveToStockroom
	findProducts();
	//moveToSorter();

	Serial.write("Done");
	return true;
}

/**
* Move in the direction of the stockroom until the positionlocater finds a significant difference
*/
void Stockroom::moveToStockroom() {
	Serial.println("DEBUG: Moving to stockroom.");
	int stockroomReached = 0;
	
	while (stockroomReached < 1) {
		if (stockroomReached == 1) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(150, Clockwise);
		}

		stockroomReached = _positionLocater->targetPosition(1, stockroomReached);
	}
	Serial.println("DEBUG: Stockroom reached.");
}

/**
* Fetches the products in the coordinate list
* Direction is calculated by checking if the next coordinate is greater than the current
* Direction than determines an absolute value to pass to move, which moves the stockroomrobot to the next product
* Upon arrival pickUp will pick the product up
*/
void Stockroom::findProducts() {
	if (current == NULL) {
		current = head;
	}

	while (current->next != NULL) {
		Direction directionX = (current->x > head->x) ? Clockwise : Counterclockwise;
		Direction directionY = (current->y > head->y) ? Clockwise : Counterclockwise;

		int moveX = (directionX == Clockwise) ? (current->x - head->x) : (head->x - current->x);
		int moveY = (directionY == Clockwise) ? (current->y - head->y) : (head->y - current->y);
		
		move(moveX, moveY, directionX, directionY);

		pickUp();

		nextCoordinate();
	}
}

/**
* Moves diagonally in the direction and to the location specified
* Runs the engines until the positions moved for that engine is reached by targetPosition
*/
void Stockroom::move(int x, int y, Direction directionX, Direction directionY) {
	Serial.println("DEBUG: Moving " + (String) x + "x" + (String) y + " positions.");
	int positionsMovedX = 0;
	int positionsMovedY = 0;

	while (positionsMovedX < x || positionsMovedY < y) {
		positionsMovedX = _stockroomXLocater->targetPosition(x, positionsMovedX);
		positionsMovedY = _stockroomYLocater->targetPosition(y, positionsMovedY);

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
			if (directionY == Clockwise) {
				_yAxes->run(255, directionY);
			}
			else {
				_yAxes->run(180, directionY);
			}
		}
	}
}

/**
* Pick up an item
* Roll out the spoon, lift it up, pull it back in and go down a little bit
*/
void Stockroom::pickUp() {
	_spoon->write(0);
	delay(1000);

	_xAxes->run(100, Clockwise);
	delay(100);
	_xAxes->stop();
	
	_spoon->write(130);

	_xAxes->run(100, Counterclockwise);
	delay(100);
	_xAxes->stop();
	Serial.println("DEBUG: Picked up product.");
}

/**
* Move diagonally to coordinate xy(1,1), then move to the sorter, then finally move to drop height
*/
void Stockroom::moveToSorter() {
	Serial.println("DEBUG: Moving to sorter.");

	int positionsMovedX = 0;
	int positionsMovedY = 0;

	while (positionsMovedX < current->x || positionsMovedY < current->y) {
		positionsMovedX = _stockroomXLocater->targetPosition((current->x--), positionsMovedX);
		positionsMovedY = _stockroomYLocater->targetPosition((current->y--), positionsMovedY);

		if (positionsMovedX == current->x) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(255, Counterclockwise);
		}

		if (positionsMovedY == current->y) {
			_yAxes->stop();
		}
		else {
			_yAxes->run(180, Counterclockwise);
		}
	}

	Serial.println("DEBUG: 1,1 reached");

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

	Serial.println("DEBUG: Sorter reached.");

	int atDropHeight = 0;

	while (atDropHeight < 1) {
		if(atDropHeight == 1) {
			_yAxes->stop();
		}
		else {
			_yAxes->run(150, Clockwise);
		}

		atDropHeight = _stockroomYLocater->targetPosition(1, atDropHeight);
	}

	Serial.println("DEBUG: Now at dropheight.");

	finished();
}

/**
* Drop cargo:
* Move yAxes up
* Stick out the spoon
* Move yAxes down
* Pull back
* Give a signal that the cargo has been dropped
*/
bool Stockroom::dropCargo() {
	Serial.println("DEBUG: Dropping cargo.");

	_yAxes->run(100, Clockwise);
	delay(100);
	_yAxes->stop();

	_spoon->write(0);
	delay(1000);

	_yAxes->run(100, Counterclockwise);
	delay(100);
	_yAxes->stop();

	_spoon->write(130);

	Serial.println("DEBUG: Cargo dropped.");

	Serial.write("okay");
	return true;
}