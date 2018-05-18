struct action {
	String command;
	int parameter;
	action *next;
};

class Command {
private:
	action * head, * tail;

	Engine * _sorter;

	Sorter * _outgoing = new Sorter(_sorter);

	bool busy = false;

public:
	Command(Engine * sorter) :
		_sorter(sorter) {
		head = NULL;
		tail = NULL;
	}

	void addCommand(String command, int parameter);

	bool doingNothing();

	void actionCompleted();

	void executeCommand();
};