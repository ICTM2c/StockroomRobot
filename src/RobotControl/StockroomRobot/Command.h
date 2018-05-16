struct action {
	String command;
	int parameter;
	action *next;
};

class Command {
private:
	action * head, *tail;

	Engine * _xAxes;
	Engine * _yAxes;
	LightSensor * _stockroomLocater;
	Engine * _spoon;
	Engine * _sorter;

	Stockroom * _stockroom = new Stockroom(_xAxes, _yAxes, _stockroomLocater, _spoon);
	Sorter * _outgoing = new Sorter(_sorter);

public:
	Command(Engine * xAxes, Engine * yAxes, LightSensor * stockroomLocater, Engine * spoon, Engine * sorter) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomLocater(stockroomLocater),
		_spoon(spoon),
		_sorter(sorter) {
		head = NULL;
		tail = NULL;
	}

	void addCommand(String command, int parameter);

	void actionCompleted();

	void executeCommand();
};