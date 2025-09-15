#pragma once
#include "Observer.h"
#include <vector>
class Subject
{
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}
	void notifyObservers() {
		for (Observer* observer : observers) {
			observer->update();
		}
	}
};

