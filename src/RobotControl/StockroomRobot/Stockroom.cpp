// 
// 
// 

#include "Stockroom.h"

/**
* Adds a coordinate to the coordinate linked list
* If no coordinates have been added yet, set head to x = 1 & y = 1
*/
void Stockroom::addCoordinate(int x, int y) {
	_coordinates.push_back(new Coordinate(x, y));

	Serial.println("DEBUG: addCoordinate " + (String)x + "," + (String)y + ".");
}

/**
* Sets the new coordinate as the head
* Picks the next coordinate to go to out of the list and set current to it
*/
void Stockroom::nextCoordinate() {
	_coordinates.erase(_coordinates.begin(), _coordinates.begin() + 1);
}

/**
* Deletes the linked list when all products have been gathered
*/
void Stockroom::finished() {
	Serial.write("done");
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
	for(int i = 0; i < _coordinates.size(); i++) {
		Direction directionX = (_coordinates[i + 1]->getX() > _coordinates[i]->getX()) ? Counterclockwise : Clockwise;
		Direction directionY = (_coordinates[i + 1]->getY() > _coordinates[i]->getY()) ? Counterclockwise : Clockwise;

		int moveX = (directionX == Counterclockwise) ? (_coordinates[i + 1]->getX() - _coordinates[i]->getX()) : (_coordinates[i]->getX() - _coordinates[i + 1]->getX());
		int moveY = (directionY == Counterclockwise) ? (_coordinates[i + 1]->getY() - _coordinates[i]->getX()) : (_coordinates[i]->getY() - _coordinates[i + 1]->getY());

		Serial.println("DEBUG: Moving " + (String)moveX + " x " + (String) moveY);

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
	Serial.println("DEBUG: Moving " + (String)x + "x" + (String)y + " positions.");
	int positionsMovedX = 0;
	int positionsMovedY = 0;

	while (positionsMovedX <= x) {
		//Serial.println("DEBUG: " + (String) positionsMovedX + " of " + (String) x);
		
		if (positionsMovedX == x) {
			_xAxes->stop();
		}
		else {
			positionsMovedX = _stockroomXLocater->targetPosition(x, positionsMovedX);
			//Serial.println("DEBUG: Now " + (String)positionsMovedX + " moved on the X axes");
			_xAxes->run(150, directionX);
		}
	}

	while (positionsMovedY <= y) {
		if (positionsMovedY == y) {
			_yAxes->stop();
		}
		else {
			positionsMovedY = _stockroomYLocater->targetPosition(y, positionsMovedY);

			Serial.println("Now " + (String)positionsMovedY + " moved on the Y axes");

			if (directionY == Counterclockwise) {
				_yAxes->run(255, directionY);
			}
			else {
				_yAxes->run(150, directionY);
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

	int moveX = (_coordinates.back()->getX() - 1);
	while (positionsMovedX < moveX || positionsMovedY < (_coordinates.back()->getY() - 1)) {
		positionsMovedX = _stockroomXLocater->targetPosition((_coordinates.back()->getX() - 1), positionsMovedX);
		positionsMovedY = _stockroomYLocater->targetPosition((_coordinates.back()->getY() - 1), positionsMovedY);

		if (positionsMovedX == (_coordinates.back()->getX() - 1)) {
			_xAxes->stop();
		}
		else {
			_xAxes->run(255, Counterclockwise);
		}

		if (positionsMovedY == (_coordinates.back()->getY() - 1)) {
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
		if (atDropHeight == 1) {
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