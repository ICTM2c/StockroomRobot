#include "Sorter.h"

bool Sorter::sort(int bin) {
	Direction direction = (bin == 1) ? Clockwise : Counterclockwise;

	_sorter->run(150, direction);
	delay(500);
	_sorter->stop();

	return true;
}