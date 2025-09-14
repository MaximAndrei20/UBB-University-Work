#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	int currentPos;     // Current position in the elements array
	int currentCount;   // How many times we've returned the current element

	BagIterator(const Bag& c);

public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
