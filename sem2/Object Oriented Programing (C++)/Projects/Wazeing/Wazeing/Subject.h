#pragma once
#include <vector>
#include "Observer.h"
class Subject
{
private:
	std::vector<Observer*> observers;
public:
	virtual ~Subject() = default;
	void addObserver(Observer* observer);
	void notifyObservers();
};

