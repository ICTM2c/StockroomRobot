#pragma once

#include "Engine.h"
#include "LightSensor.h"
#include "Servo.h"

// Stockroom.h

struct Coordinate {
	int _x;
	int _y;
	
	Coordinate(int x, int y) {
		_x = x;
		_y = y;
	}

	int getX() {
		return _x;
	}

	int getY() {
		return _y;
	}
};

class Stockroom {
private:
	Engine * _xAxes;
	Engine * _yAxes;
	LightSensor * _stockroomXLocater;
	LightSensor * _stockroomYLocater;
	Servo * _spoon;
	LightSensor * _positionLocater;

	bool _busy = false;
	std::vector<Coordinate&> _coordinates = std::vector<Coordinate&>();

public:
	Stockroom(Engine * xAxes, Engine * yAxes, LightSensor * stockroomXLocater, LightSensor * stockroomYLocater, Servo * spoon, LightSensor * positionLocater) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomXLocater(stockroomXLocater),
		_stockroomYLocater(stockroomYLocater),
		_spoon(spoon),
		_positionLocater(positionLocater) {
		
	}

	void addCoordinate(int x, int y);

	void nextCoordinate();

	void finished();

	bool start();

	void moveToStockroom();

	void findProducts();

	void move(int x, int y, Direction directionX, Direction directionY);

	void pickUp();
	
	void moveToSorter();

	bool dropCargo();
};