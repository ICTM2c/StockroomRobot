#include "Sorter.h"

void Sorter::addProduct(int dropin) {
	bin *temp = new bin;

	temp->dropin = dropin;
	temp->next = NULL;

	if (head == NULL) {
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

void Sorter::nextProduct() {
	bin *temp = new bin;
	temp = current;
	current = temp->next;
	delete temp;
}

void Sorter::finished() {
	while (head != NULL) {
		bin *temp = new bin;
		temp = head;
		head = head->next;
		delete temp;
	}

	Serial.write("Sorting completed.");
}

bool Sorter::start() {
	current = head;
	while (current != NULL) {
		sort(current->dropin);
		nextProduct();
	}
	finished();

	return true;
}

void Sorter::sort(int bin) {
	Direction direction = (bin == 1) ? Clockwise : Counterclockwise;

	_sorter->run(150, direction);
	delay(500);
	_sorter->stop();
}