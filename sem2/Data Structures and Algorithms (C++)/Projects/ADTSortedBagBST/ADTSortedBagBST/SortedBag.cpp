#include "SortedBag.h"
#include "SortedBagIterator.h"

// BC: Theta(1), WC: Theta(1), TC: Theta(1)
SortedBag::SortedBag(Relation r) : root(nullptr), relation(r), count(0) {
}

// BC: Theta(1), WC: Theta(n), TC: O(n)
void SortedBag::add(TComp e) {
	
	this->count++; // Increment the count of elements in the sorted bag

	Node* newNode = new Node(e);
	if (!root) {
		root = newNode;
		return;
	}

	Node* current = root;
	Node* parent = nullptr;
	while (current) {
		parent = current;
		if (current->element == e) {
			current->frequency++; // If the element already exists, increment its frequency
			delete newNode; // No need to insert a new node, just increment frequency
			return;
		}
		else if (relation(e, current->element)) {
			current = current->left; // Go left if e is less than current element
		}
		else if (relation(current->element, e)) {
			current = current->right; // Go right if e is greater than current element
		}
	}
	if (relation(e, parent->element)) {
		parent->left = newNode; // Insert as left child if e is less than parent element
	}
	else {
		parent->right = newNode; // Insert as right child if e is greater than parent element
	}
	newNode->parent = parent; // Set the parent of the new node
}

// BC: Theta(1), WC: Theta(n), TC: O(n)
bool SortedBag::remove(TComp e) {
	Node* current = root;
	Node* parent = nullptr;
	while (current) {
		if (e == current->element) {
			{
				// Element found
				if (current->frequency > 1) {
					current->frequency--;
					this->count--;
					return true;
				}
				// Node with no children
				if (!current->left && !current->right) {
					if (parent) {
						if (parent->left == current) parent->left = nullptr;
						else parent->right = nullptr;
					}
					else {
						root = nullptr;
					}
					delete current;
					this->count--;
					return true;
				}
				// Node with one child
				else if (!current->left || !current->right) {
					Node* child = (current->left) ? current->left : current->right;
					if (parent) {
						if (parent->left == current) parent->left = child;
						else parent->right = child;
					}
					else {
						root = child;
					}
					if (child) child->parent = parent; // Update parent pointer
					delete current;
					this->count--;
					return true;
				}
				// Node with two children
				else {
					// Find the in-order successor (smallest in the right subtree)
					// Could've also used the in-order predecesor (greatest in the left subtree)
					Node* successorParent = current;
					Node* successor = current->right;
					while (successor->left) {
						successorParent = successor;
						successor = successor->left;
					}
					current->element = successor->element;
					current->frequency = successor->frequency;
					// Remove successor node
					if (successorParent != current) {
						successorParent->left = successor->right;
						if (successor->right) successor->right->parent = successorParent;
					}
					else {
						successorParent->right = successor->right;
						if (successor->right) successor->right->parent = successorParent;
					}
					delete successor;
					this->count--;
					return true;
				}
			}
		}
		else if (relation(e, current->element)) {
			parent = current;
			current = current->left;
		}
		else if (relation(current->element, e)) {
			parent = current;
			current = current->right;
		}
	}
	return false;
}


// BC: Theta(1), WC: Theta(n), TC: O(n)
bool SortedBag::search(TComp elem) const {
	
	Node* current = root;
	while (current) {
		if (current->element == elem) {
			return true; // Element found
		}
		else if (relation(elem, current->element)) {
			current = current->left; // Go left if elem is less than current element
		}
		else if (relation(current->element, elem)) {
			current = current->right; // Go right if elem is greater than current element
		}
	}

	return false;
}

// BC: Theta(1), WC: Theta(n), TC: O(n)
int SortedBag::nrOccurrences(TComp elem) const {
	Node* current = root;
	while (current) {

		if (current->element == elem) {
			return current->frequency; // Element found, return its frequency
		}
		else if (relation(elem, current->element)) {
			current = current->left; // Go left if elem is less than current element
		}
		else if (relation(current->element, elem)) {
			current = current->right; // Go right if elem is greater than current element
		}
	}
	return 0; // Element not found, return 0 occurrences

}


// BC: Theta(1), WC: Theta(1), TC: Theta(1)
int SortedBag::size() const {
	//TODO - Implementation
	return this->count; // Return the count of elements in the sorted bag
}

// BC: Theta(1), WC: Theta(1), TC: Theta(1)
bool SortedBag::isEmpty() const {
	return this->count == 0; // Check if the count of elements is zero
}

// BC: Theta(1), WC: Theta(1), TC: Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


// BC: Theta(1), WC: Theta(n), TC: O(n)
void SortedBag::destroyRecursive(Node* node) {
	if (node == nullptr) return;
	destroyRecursive(node->left);
	destroyRecursive(node->right);
	delete node;
}

// BC: Theta(1), WC: Theta(n^2), TC: O(n^2)
TElem SortedBag::mostFrequent() const
{
	auto it = this->iterator();
	int maxFrequency = 0;
	TElem mostFrequentElem = NULL_TCOMP;
	while (it.valid()) {
		TElem currentElem = it.getCurrent();
		int currentFrequency = this->nrOccurrences(currentElem);
		if (currentFrequency > maxFrequency) {
			maxFrequency = currentFrequency;
			mostFrequentElem = currentElem;
		}
		it.next();
	}
	if (maxFrequency == 0) {
		return NULL_TCOMP; // If no elements, return NULL_TCOMP
	}
	return mostFrequentElem; // Return the element with the highest frequency
}

// BC: Theta(1), WC: Theta(n), TC: O(n)
SortedBag::~SortedBag() {
	destroyRecursive(root);
}
