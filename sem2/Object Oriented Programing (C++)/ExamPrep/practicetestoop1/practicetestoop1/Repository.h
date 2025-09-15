#pragma once
#include "DynamicVector.h"
#include "Car.h"
class Repository
{
private:
	DynamicVector<Car> cars;

public:
	void addCar(const Car& c);
	void removeCar(int index);
	void updateCar(int index, const Car& c);
	DynamicVector<Car> getCars() const { return this->cars; }
	int getSize() const { return this->cars.getSize(); }
};

