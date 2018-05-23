#include "Engine.h"
#include "LightSensor.h"
#include "Server.h"
#include "Stockroom.h"

#pragma once

struct action {
	String command;
	String parameter;
	action *next;
};

class Command {
private:
	action * head, * tail;

	Engine * _xAxes;
	Engine * _yAxes;
	LightSensor * _stockroomXLocater;
	LightSensor * _stockroomYLocater;
	Servo * _spoon;
	LightSensor * _positionLocater;

	Stockroom * _stockroom = new Stockroom(_xAxes, _yAxes, _stockroomXLocater, _stockroomYLocater, _spoon, _positionLocater);

	bool busy = false;

public:
	Command(Engine * xAxes, Engine * yAxes, LightSensor * stockroomXLocater, LightSensor * stockroomYLocater, Servo * spoon, LightSensor * positionLocater) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomXLocater(stockroomXLocater),
		_stockroomYLocater(stockroomYLocater),
		_spoon(spoon),
		_positionLocater(positionLocater) {
		head = NULL;
		tail = NULL;
	}

	void addCommand(String command, String parameter);

	bool doingNothing();

	void actionCompleted();

	void executeCommand();
};