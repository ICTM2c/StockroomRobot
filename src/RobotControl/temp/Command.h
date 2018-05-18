struct action {
	String command;
	int parameter;
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
	Engine * _sorter;
	LightSensor * _positionLocater;

	Stockroom * _stockroom = new Stockroom(_xAxes, _yAxes, _stockroomXLocater, _stockroomYLocater, _spoon, _positionLocater);
	Sorter * _outgoing = new Sorter(_sorter, _positionLocater);

	bool busy = false;

public:
	Command(Engine * xAxes, Engine * yAxes, LightSensor * stockroomXLocater, Servo * spoon, Engine * sorter, LightSensor * positionLocater) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomXLocater(stockroomXLocater),
		_spoon(spoon),
		_sorter(sorter),
		_positionLocater(positionLocater) {
		head = NULL;
		tail = NULL;
	}

	void addCommand(String command, int parameter);

	bool doingNothing();

	void actionCompleted();

	void executeCommand();
};