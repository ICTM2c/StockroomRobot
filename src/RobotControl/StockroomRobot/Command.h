#include "Engine.h"
#include "LightSensor.h"
#include "Server.h"
#include "Stockroom.h"
#include <vector>

#pragma once

struct CommandItem {
	String _command;
	String _parameter;

	CommandItem(String command, String parameter) {
		_command = command;
		_parameter = parameter;
	}

	String getCommand() {
		return _command;
	}

	String getParameter() {
		return _parameter;
	}
};

class Command {
private:
	Engine * _xAxes;
	Engine * _yAxes;
	LightSensor * _stockroomXLocater;
	LightSensor * _stockroomYLocater;
	Servo * _spoon;
	LightSensor * _positionLocater;

	Stockroom * _stockroom = new Stockroom(_xAxes, _yAxes, _stockroomXLocater, _stockroomYLocater, _spoon, _positionLocater);

	bool _busy = false;
	std::vector <CommandItem*> _commandList = std::vector<CommandItem*>();

public:
	Command(Engine * xAxes, Engine * yAxes, LightSensor * stockroomXLocater, LightSensor * stockroomYLocater, Servo * spoon, LightSensor * positionLocater) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomXLocater(stockroomXLocater),
		_stockroomYLocater(stockroomYLocater),
		_spoon(spoon),
		_positionLocater(positionLocater) {

	}

	void addCommand(String CommandItem, String parameter);

	bool doingNothing();

	void actionCompleted();

	void executeCommand();
};