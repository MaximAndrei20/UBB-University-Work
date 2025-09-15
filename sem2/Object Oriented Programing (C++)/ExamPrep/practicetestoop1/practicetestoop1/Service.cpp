#include "Service.h"

bool Service::addCar(const std::string& manufacturer, const std::string& model, int year, const std::string& color)
{
	Car c{ manufacturer, model, year, color };
	for (int i = 0; i < this->repo.getSize(); i++)
	{
		Car c = this->repo.getCars()[i];
		if (c.getModel() == model && c.getYear() == year)
			return false;
	}
	this->repo.addCar(c);
	return true;
}

bool Service::removeCar(std::string model, int year)
{
	DynamicVector<Car> cars = this->repo.getCars();
	for (int i = 0; i < cars.getSize(); i++)
	{
		Car c = cars[i];
		if (c.getModel() == model && c.getYear() == year)
		{
			this->repo.removeCar(i);
			return true;
		}
	}
	return false;
}
