#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

struct Node {
    TElem pair;      // key-value pair (TKey, TValue)
    Node* next;      // pointer to next node in the bucket

    Node(TKey k, TValue v) : pair({ k, v }), next(nullptr) {}
};

class SortedMultiMap {
	friend class SMMIterator;
    private:
        Node** buckets;         // Array of linked lists (buckets)
        int capacity;           // Size of the buckets array
        int _size;              // Number of key-value pairs
        Relation relation;     // Sorting rule (asc/desc)
        const double maxLoadFactor = 0.7;  // Resize when size/capacity > 0.7

        // Hash function
        int hash(TKey key) const;
        
        // Resize and rehash logic (to be implemented later)
        void resizeAndRehash();

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // replaces the value currently mapped to a key k, with value newValue, only if the current value is equal to oldValue.
    // if the current value is not oldValue, or if k is not in the sortedmap, nothing changes.
	void replace(TKey k, TValue oldValue, TValue newValue);

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
