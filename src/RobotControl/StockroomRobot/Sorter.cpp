#include "Sorter.h"

void Sorter::sort(int bin) {
	Direction direction = (bin == 1) ? Clockwise : Counterclockwise;
	_sorter->run(150, direction);
}