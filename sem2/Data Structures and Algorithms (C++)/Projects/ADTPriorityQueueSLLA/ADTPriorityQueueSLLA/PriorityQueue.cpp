
#include "PriorityQueue.h"
#include <exception>
using namespace std;

#define INIT_CAPACITY 10

// BC: Theta(1) WC: Theta(n) TC: O(n)
void PriorityQueue::resize()
{
	if (this->firstEmpty != -1) {
		return;
	}

	this->firstEmpty = this->capacity;
	int newCapacity = this->capacity * 2;
	Element* newElements = new Element[newCapacity];
	int* newNext = new int[newCapacity];
	for (int i = 0; i < this->capacity; i++) {
		newElements[i] = this->elements[i];
		newNext[i] = this->next[i];
	}
	for (int i = this->capacity; i < newCapacity - 1; i++) {
		newNext[i] = i + 1;
	}
	newNext[newCapacity - 1] = -1;
	delete[] this->elements;
	delete[] this->next;
	this->elements = newElements;
	this->next = newNext;
	this->capacity = newCapacity;
}

// BC: Theta(n) WC: Theta(n) TC: Theta(n)
PriorityQueue::PriorityQueue(Relation r) {
	this->capacity = INIT_CAPACITY;
	this->elements = new Element[this->capacity];
	this->next = new int[this->capacity];
	this->head = -1;
	this->firstEmpty = 0;
	for (int i = 0; i < this->capacity - 1; i++) {
		this->next[i] = i + 1;
	}
	this->next[this->capacity - 1] = -1;
	this->firstEmpty = 0;

	this->relation = r;
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
void PriorityQueue::push(TElem e, TPriority p) {
	// check if resize is needed
	if (this->firstEmpty == -1) {
		this->resize();
	}
	int newElement = this->firstEmpty;
	this->firstEmpty = this->next[this->firstEmpty];
	this->elements[newElement] = make_pair(e, p);
	
	//check empty queue case
	if (this->head == -1) {
		this->head = newElement;
		this->next[newElement] = -1;
		return;
	}

	//insert the new element in the queue
	int prev = -1;
	int current = this->head;
	while (current != -1 && this->relation(this->elements[current].second, p)) {
		prev = current;
		current = this->next[current];
	}
	if (prev == -1) {
		this->next[newElement] = this->head;
		this->head = newElement;
	}
	else {
		this->next[prev] = newElement;
		this->next[newElement] = current;
	}
}

//throws exception if the queue is empty
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
Element PriorityQueue::top() const {
	if (this->head == -1) {
		throw exception();
	}
	return this->elements[this->head];
}

//throws exception if the queue is empty
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
Element PriorityQueue::pop() {
	if (this->head == -1) {
		throw exception();
	}
	int current = this->head;
	this->head = this->next[this->head];
	this->next[current] = this->firstEmpty;
	this->firstEmpty = current;
	return this->elements[current];
}

// BC: Theta(1) WC: Theta(1) TC: Theta(1)
bool PriorityQueue::isEmpty() const {
	return this->head == -1;
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
bool PriorityQueue::search(TElem elem) const
{
	int current = this->head;
	while (current != -1) {
		if (this->elements[current].first == elem) {
			return true;
		}
		current = this->next[current];
	}
	return false;
}


// BC: Theta(1) WC: Theta(1) TC: Theta(1)
PriorityQueue::~PriorityQueue() {
	delete[] this->elements;
	delete[] this->next;
};

