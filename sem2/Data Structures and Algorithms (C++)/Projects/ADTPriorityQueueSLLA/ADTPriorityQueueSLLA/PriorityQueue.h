#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

class PriorityQueue {
private:
	//Representation done using single linked list array
	// example: 
	// elements: 5|-|8|4|-|6|-|-|9|
	// next:     5|4|0|-1|6|8|7|-1|3|
	// we keep track of the first element and the first position in the array
	int head, firstEmpty;
	Element* elements;
	int* next;
	int capacity;

	//the relation used to order the elements in the queue
	Relation relation;

	//resizes the queue
	void resize();

public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//checks if elem is in the PriorityQueue or not
	bool search(TElem elem) const;

	//destructor
	~PriorityQueue();

};