#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


// Private helper functions
int Bag::getPosition(TElem e) const {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    if (this->elements == nullptr || e < this->minElem) return -1;
    int pos = e - this->minElem;
    if (pos >= this->capacity) return -1;
    return pos;
}

void Bag::resize(int newMin, int newMax) {
    // Time complexity: Best case: O(n), Average case: O(n), Worst case: O(n)
    // Space complexity: Best case: O(n), Average case: O(n), Worst case: O(n)
    int newCapacity = newMax - newMin + 1;
    int* newElements = new int[newCapacity](); // Initialize to 0

    if (this->elements != nullptr) {
        // Copy existing this->elements to their new positions
        int offset = this->minElem - newMin;
        for (int i = 0; i < this->capacity; i++) {
            if (this->elements[i] > 0) {
                newElements[i + offset] = this->elements[i];
            }
        }
        delete[] this->elements;
    }

    this->elements = newElements;
    this->minElem = newMin;
    this->capacity = newCapacity;
}


Bag::Bag() {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    this->elements = nullptr;
	this->minElem = 0;
	this->capacity = 0;
	this->bagSize = 0;
}


void Bag::add(TElem elem) {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(n) (due to resize)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(n)

    // Handle empty bag case
    if (this->elements == nullptr) {
        this->minElem = elem;
        this->capacity = 1;
        this->elements = new int[1]();
        this->elements[0] = 1;
        this->bagSize = 1;
        return;
    }

    // Check if we need to resize
    if (elem < this->minElem) {
        int newMin = elem;
        int newMax = this->minElem + this->capacity - 1;
        resize(newMin, newMax);
    }
    else if (elem >= this->minElem + this->capacity) {
        int newMin = this->minElem;
        int newMax = elem;
        resize(newMin, newMax);
    }

    // Add the element
    int pos = elem - this->minElem;
    this->elements[pos]++;
    this->bagSize++;
}


bool Bag::remove(TElem elem) {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(n) (due to resize)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(n)
    int pos = getPosition(elem);
    if (pos == -1 || this->elements[pos] == 0) {
        return false;
    }

    this->elements[pos]--;
    this->bagSize--;

    // Optional: resize if we removed the last occurrence of min or max
    // This is an optimization to save space
    if (this->elements[pos] == 0) {
        if (pos == 0) {
            // Find new min
            int newMin = this->minElem;
            while (newMin <= this->minElem + this->capacity - 1 && this->elements[newMin - this->minElem] == 0) {
                newMin++;
            }
            if (newMin > this->minElem + this->capacity - 1) {
                // Bag is empty
                delete[] this->elements;
                this->elements = nullptr;
                this->minElem = 0;
                this->capacity = 0;
            }
            else {
                int newMax = this->minElem + this->capacity - 1;
                resize(newMin, newMax);
            }
        }
        else if (pos == this->capacity - 1) {
            // Find new max
            int newMax = this->minElem + this->capacity - 1;
            while (newMax >= this->minElem && this->elements[newMax - this->minElem] == 0) {
                newMax--;
            }
            if (newMax < this->minElem) {
                // Bag is empty
                delete[] this->elements;
                this->elements = nullptr;
                this->minElem = 0;
                this->capacity = 0;
            }
            else {
                resize(this->minElem, newMax);
            }
        }
    }

    return true;
}


bool Bag::search(TElem elem) const {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    int pos = getPosition(elem);
    return pos != -1 && this->elements[pos] > 0;
}

int Bag::nrOccurrences(TElem elem) const {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    int pos = getPosition(elem);
    return pos == -1 ? 0 : this->elements[pos];
}


int Bag::removeOccurences(int nr, TElem elem)
{
	// Time complexity: Best case: O(1), Average case: O(1), Worst case: O(n) (due to remove)
	// Space complexity: Best case: O(1), Average case: O(1), Worst case: O(n)
	int nrRemoved = 0;
	while (this->remove(elem) && nrRemoved < nr) {
		nrRemoved++;
	}
	return nrRemoved;
}

int Bag::size() const {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    return this->bagSize;
}


bool Bag::isEmpty() const {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    return this->bagSize == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    // Time complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    // Space complexity: Best case: O(1), Average case: O(1), Worst case: O(1)
    if (this->elements != nullptr) {
        delete[] this->elements;
    }
}

