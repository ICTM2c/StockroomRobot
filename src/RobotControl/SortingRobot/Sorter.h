#pragma once

struct bin {
	int dropin;
	bin * next;
};

class Sorter
{
private:
	bin * head, * tail, * current;

	Engine * _sorter;
public:
	Sorter(Engine * sorter) : _sorter(sorter) {

	}

	void addProduct(int bin);

	void nextProduct();

	void finished();

	bool start();

	void sort(int bin);
};