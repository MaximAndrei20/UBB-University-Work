
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
	// Best case - Theta(1) Worst case - Theta(1) 
	this->head = NULL;
	this->relation = r;
}


void PriorityQueue::push(TElem e, TPriority p) {
	//Best case - Theta(1) Worst case - Theta(n) TC O(n)
	if (this->head == NULL) {
		Node* newNode = new Node;
		newNode->elem = e;
		newNode->priority = p;
		newNode->next = NULL;
		this->head = newNode;
	}
	else {
		Node* currentNode = this->head;
		Node* previousNode = NULL;
		while (currentNode != NULL && this->relation(currentNode->priority, p)) {
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		Node* newNode = new Node;
		newNode->elem = e;
		newNode->priority = p;
		newNode->next = currentNode;
		if (previousNode == NULL) {
			this->head = newNode;
		}
		else {
			previousNode->next = newNode;
		}
	}
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	// Best case - Theta(1) Worst case - Theta(1) TC Theta(1)
	if (this->head == NULL) {
		throw exception("Queue is empty");
	}
	return make_pair(this->head->elem, this->head->priority);
}

Element PriorityQueue::pop() {
	//Best case - Theta(1) Worst case - Theta(1) TC Theta(1)
	if (this->head != NULL) {
		Node* nodeToDelete = this->head;
		Element element = make_pair(nodeToDelete->elem, nodeToDelete->priority);
		this->head = this->head->next;
		delete nodeToDelete;
		return element;
	}
	throw exception("Queue is empty");
}

bool PriorityQueue::isEmpty() const {
	//Best case - Theta(1) Worst case - Theta(1) TC Theta(1)
	return this->head == NULL;
}

bool PriorityQueue::search(TElem elem) const
{
	//Best case - Theta(1) Worst case - Theta(n)
	Node* currentNode = this->head;
	while (currentNode != NULL) {
		if (currentNode->elem == elem) {
			return true;
		}
		currentNode = currentNode->next;
	}
	return false;
}


PriorityQueue::~PriorityQueue() {
	//Best case - Theta(1) Worst case - Theta(n)
	while (this->head != NULL) {
		Node* nodeToDelete = this->head;
		this->head = this->head->next;
		delete nodeToDelete;
	}
};

