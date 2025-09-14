#include "SMMIterator.h"
#include <algorithm>

// BC: Theta(n) WC: Theta(n) TC: Theta(n)
void SMMIterator::merge(TElem* arr, int left, int mid, int right, Relation rel) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    TElem* L = new TElem[n1];
    TElem* R = new TElem[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (rel(L[i].first, R[j].first)) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// BC: Theta(nlog(n)) WC: Theta(nlog(n)) TC: Theta(nlog(n))
void SMMIterator::mergeSort(TElem* arr, int left, int right, Relation rel) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, rel);
        mergeSort(arr, mid + 1, right, rel);
        merge(arr, left, mid, right, rel);
    }
}

// Constructor: Collect and sort all elements
// BC: Theta(1) WC: Theta(nlog(n)) TC: O(nlog(n))
SMMIterator::SMMIterator(const SortedMultiMap& m) : map(m), currentPos(0) {
    collectAndSort();
}

// Destructor
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
SMMIterator::~SMMIterator() {
    delete[] elements;
}

// Collect all elements and sort them
// BC: Theta(1) WC: Theta(nlog(n)) TC: O(nlog(n))
void SMMIterator::collectAndSort() {
    // Count total elements
    totalElements = 0;
    for (int i = 0; i < map.capacity; i++) {
        Node* current = map.buckets[i];
        while (current != nullptr) {
            totalElements++;
            current = current->next;
        }
    }

    // Allocate and fill array
    elements = new TElem[totalElements];
    int index = 0;
    for (int i = 0; i < map.capacity; i++) {
        Node* current = map.buckets[i];
        while (current != nullptr) {
            elements[index++] = current->pair;
            current = current->next;
        }
    }

    // Sort using the map's relation
    if (totalElements > 1) {
        mergeSort(elements, 0, totalElements - 1, map.relation);
    }
}

// Iterator functions
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
void SMMIterator::first() { currentPos = 0; }
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
void SMMIterator::next() 
{ 
    if (valid()) currentPos++; 
    else throw std::exception();
}
// BC: Theta(1) WC: Theta(1) TC: Theta(1)
bool SMMIterator::valid() const { return currentPos < totalElements; }

// BC: Theta(1) WC: Theta(1) TC: Theta(1)
TElem SMMIterator::getCurrent() const {
    if (!valid()) throw std::exception();
    return elements[currentPos];
}
