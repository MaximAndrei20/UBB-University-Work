#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	// R4 Representation - Dynamic array where:
	// - Index represents element value (offset by minElem)
	// - Value at index represents frequency count
	int* elements;      // Dynamic array storing frequencies
	int minElem;        // Minimum element in the bag
	int capacity;       // Current capacity of the array (maxElem = minElem + capacity - 1)
	int bagSize;        // Total number of elements in the bag

	// Helper function to get array position for an element
	int getPosition(TElem e) const;

	// Helper function to resize the array when needed
	void resize(int newMin, int newMax);

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//removes nr occurrences of elem. If the element appears less than nr times, all occurrences will be removed.
	//returns the number of times the element was removed
	//throws an exception if nr is negative
	int removeOccurences(int nr, TElem elem);

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};