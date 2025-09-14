#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->first();
}

void BagIterator::first() {
	// Start at the beginning of the array
	this->currentPos = 0;
	this->currentCount = 0;

	// Find the first element with non-zero frequency
	while (this->currentPos < this->bag.capacity && this->bag.elements[this->currentPos] == 0)
		this->currentPos++;

	// If found, initialize count
	if (currentPos < bag.capacity) {
		currentCount = 1;
	}
}


void BagIterator::next() {
	if (!this->valid())
		throw std::exception();

	// If we have more occurrences of current element
	if (this->currentCount < this->bag.elements[this->currentPos]) {
		this->currentCount++;
		return;
	}
	else {
		// Move to next element with non-zero frequency
		this->currentPos++;
		this->currentCount = 1;
		while (this->currentPos < this->bag.capacity && this->bag.elements[this->currentPos] == 0)
			this->currentPos++;
	}
}


bool BagIterator::valid() const {
	return this->currentPos < this->bag.capacity;
}



TElem BagIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();
	return this->bag.minElem + this->currentPos;
}
