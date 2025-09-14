#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

/*
	ADT SortedBag - using a BST with linked representation with dynamic memory allocation. 
	In the BST(unique element, frequency) pairs are stored.
 */ 

struct Node {
	TElem element;
	int frequency;
	Node* left;
	Node* right;
	Node* parent;
	Node(TElem e) : element(e), frequency(1), left(nullptr), right(nullptr), parent(nullptr) {} // Constructor for a new node
};

class SortedBag {
	friend class SortedBagIterator;

private:
	Node* root;
	int count;
	Relation relation; // the relation that defines the order of the elements in the sorted bag

	void destroyRecursive(Node* node); // Helper function to recursively destroy the BST
public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	// returns the TComp with the greatest frequency from the sortedBag (if there are multiple elements with the same frequency, any one can be returned)
	// if the SortedBag is empty it returns NULL_TCOMP
	TElem mostFrequent() const;

	//destructor
	~SortedBag();
};