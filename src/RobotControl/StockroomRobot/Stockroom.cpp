// 
// 
// 

#include "Stockroom.h"

void Stockroom::moveToStockroom() {
	while (!stockroomLocater->targetPosition(1)) {
		_xAxes->run(150, Clockwise);
	}
	_xAxes->stop();
}

void Stockroom::moveUp(int y) {
	while (!stockroomLocater->targetPosition(y)) {
		_yAxes->run(150, Clockwise);
	}
	_yAxes->stop();
}

void Stockroom::moveDown(int y) {
	while (!stockroomLocater->targetPosition(y)) {
		_yAxes->run(150, Counterclockwise);
	}
	_yAxes->stop();
}

void Stockroom::moveRight(int x) {
	while (!stockroomLocater->targetPosition(x)) {
		_xAxes->run(150, Clockwise);
	}
	_xAxes->stop();
}

void Stockroom::moveLeft(int x) {
	while (!stockroomLocater->targetPosition(x)) {
		_xAxes->run(150, Counterclockwise);
	}
	_xAxes->stop();
}

void Stockroom::pickUp() {
	spoon->run(150, Clockwise);
	delay(100);
	spoon->stop();
	delay(100);
	spoon->run(150, Counterclockwise);
	delay(100);
	spoon->stop();
}