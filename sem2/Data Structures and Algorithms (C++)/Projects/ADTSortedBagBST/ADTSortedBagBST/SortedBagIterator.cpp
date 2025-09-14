#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// BC: Theta(1) WC: Theta(n) TC: O(n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
Node* SortedBagIterator::leftMost(Node* node) {
	if (node == nullptr) return nullptr;
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

// BC: Theta(1) WC: Theta(1) TC: Theta(1)
TComp SortedBagIterator::getCurrent() {
    if (!valid()) throw std::exception();
    return currentNode->element;
}


// BC: Theta(1) WC: Theta(1) TC: Theta(1)
bool SortedBagIterator::valid() {
    return currentNode != nullptr;
}

// BC: Theta(1) WC: Theta(n), TC: O(n)
void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    // Handle multiple occurrences
    if (--currentCount > 0) return;

    // Standard in-order successor with parent pointer
    if (currentNode->right != nullptr) {
        // Case 1: Has right child - successor is leftmost in right subtree
        currentNode = leftMost(currentNode->right);
    }
    else {
        // Case 2: No right child - walk up parents until we come from left
        Node* p = currentNode->parent;
        while (p != nullptr && currentNode == p->right) {
            currentNode = p;
            p = p->parent;
        }
        currentNode = p;
    }

    currentCount = currentNode ? currentNode->frequency : 0;
}

// BC: Theta(1) WC: Theta(n) TC: O(n)
void SortedBagIterator::first() {
	currentNode = leftMost(bag.root);
	currentCount = currentNode ? currentNode->frequency : 0;
}

