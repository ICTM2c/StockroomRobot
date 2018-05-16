// Stockroom.h

class Stockroom {
private:
	Engine * _xAxes;
	Engine * _yAxes;
	LightSensor * _stockroomLocater;
	Engine * _spoon;

public:
	Stockroom(Engine * xAxes, Engine * yAxes, LightSensor * stockroomLocater, Engine * spoon) :
		_xAxes(xAxes),
		_yAxes(yAxes),
		_stockroomLocater(stockroomLocater),
		_spoon(spoon) {

	}

	void moveToStockroom();

	void moveUp(int y);

	void moveDown(int y);

	void moveLeft(int x);

	void moveRight(int x);

	void pickUp();
};