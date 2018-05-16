#pragma once
class Sorter
{
private:
	Engine * _sorter;
public:
	Sorter(Engine * sorter) : _sorter(sorter) {

	}

	void sort(int bin);
};