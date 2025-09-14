#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <assert.h>

using namespace std;

bool rel0(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}

void testSearch() {
	cout << "Test search" << endl;
	PriorityQueue pq(rel0);
	for (int i = 0; i < 10; i++) {
		pq.push(i, i);
	}
	assert(pq.search(5) == true);
	assert(pq.search(10) == false);
	assert(pq.search(-1) == false);
	assert(pq.search(0) == true);
	assert(pq.search(9) == true);
}


int main() {
	testSearch();
	testAll();
	testAllExtended();

	cout << "End" << endl;
	system("pause");

}
