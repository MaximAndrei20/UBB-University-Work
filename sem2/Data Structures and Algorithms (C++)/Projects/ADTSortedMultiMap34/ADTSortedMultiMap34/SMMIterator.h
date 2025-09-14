#pragma once
#include "SortedMultiMap.h"

class SMMIterator {
    friend class SortedMultiMap;
private:
    const SortedMultiMap& map;
    TElem* elements;       // Array of all elements (sorted)
    int currentPos;        // Current position in array
    int totalElements;     // Total elements in map

    // Collect and sort all elements
    void collectAndSort();
	// Helper: Merge two sorted subarrays
	void merge(TElem* arr, int left, int mid, int right, Relation rel);
	// Helper: Merge sort implementation
	void mergeSort(TElem* arr, int left, int right, Relation rel);

public:
    SMMIterator(const SortedMultiMap& m);
    ~SMMIterator();
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};