#pragma once
class Sorter
{
private:
	Engine * _sorter;
public:
	Sorter(Engine * sorter) : _sorter(sorter) {

	}

	bool sort(int bin);
};