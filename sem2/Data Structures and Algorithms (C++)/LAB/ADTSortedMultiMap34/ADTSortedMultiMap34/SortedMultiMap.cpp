#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Constructor
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) : relation(r), capacity(10), _size(0) {
    buckets = new Node * [capacity]();  // Initialize all buckets to nullptr
}

// Destructor
// BC: Theta(1) WC: Theta(n) TC: O(n)
SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < capacity; i++) {
        Node* current = buckets[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] buckets;
}

// Add a key-value pair (O(1) avg)
// BC: Theta(1) WC: Theta(n) TC: O(n)
void SortedMultiMap::add(TKey c, TValue v) {
    if ((double)_size / capacity > maxLoadFactor) {
        resizeAndRehash();
    }

    int index = hash(c);
    Node* newNode = new Node(c, v);
    newNode->next = buckets[index];  // Insert at head of bucket
    buckets[index] = newNode;
    _size++;
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
std::vector<TValue> SortedMultiMap::search(TKey c) const {
    std::vector<TValue> values;
    int index = hash(c);
    Node* current = buckets[index];

    while (current != nullptr) {
        if (current->pair.first == c) {
            values.push_back(current->pair.second);
        }
        current = current->next;
    }
    return values;
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int index = hash(c);
    Node* prev = nullptr;
    Node* current = buckets[index];

    while (current != nullptr) {
        if (current->pair.first == c && current->pair.second == v) {
            if (prev == nullptr) {
                buckets[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            _size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// BC: Theta(1) WC: Theta(1) TC: Theta(1)
int SortedMultiMap::hash(TKey key) const
{
    return (key % capacity + capacity) % capacity;
}

// BC: Theta(n) WC: Theta(n) TC: O(n)
void SortedMultiMap::resizeAndRehash() {
    int newCapacity = capacity * 2;
    Node** newBuckets = new Node * [newCapacity]();
	int oldCapacity = capacity;
	capacity = newCapacity;

    for (int i = 0; i < oldCapacity; i++) {
        Node* current = buckets[i];
        while (current != nullptr) {
            Node* next = current->next;
            int newIndex = hash(current->pair.first);

            // Insert at head of new bucket
            current->next = newBuckets[newIndex];
            newBuckets[newIndex] = current;

            current = next;
        }
    }

    delete[] buckets;
    buckets = newBuckets;
    capacity = newCapacity;
}

// BC: Theta(1) WC: Theta(1) TC: Theta(1)
int SortedMultiMap::size() const { return _size; }
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
bool SortedMultiMap::isEmpty() const { return _size == 0; }

// BC: Theta(1) WC: Theta(n) TC: O(n)
void SortedMultiMap::replace(TKey k, TValue oldValue, TValue newValue)
{
    int index = hash(k);
    Node* current = buckets[index];
	while (current != nullptr) {
		if (current->pair.first == k && current->pair.second == oldValue) {
			current->pair.second = newValue;
			return;
		}
		current = current->next;
	}
}
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
SMMIterator SortedMultiMap::iterator() const { return SMMIterator(*this); }