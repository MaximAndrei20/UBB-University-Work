#include "Repository.h"

void Repository::addCar(const Car& c)
{
	this->cars.add(c);
}

void Repository::removeCar(int index)
{
	this->cars.remove(index);
}

void Repository::updateCar(int index, const Car& c)
{
	this->cars.remove(index);
	this->cars.add(c);
}
