#pragma once
#include "Repository.h"
class Service
{
private:
	Repository& repo;
public:
	Service(Repository& repo) : repo{ repo } {}
	bool addCar(const std::string& manufacturer, const std::string& model, int year, const std::string& color);
	bool removeCar(std::string model, int year);
	//void updateCar(int index, const std::string& manufacturer, const std::string& model, int year, const std::string& color);
	DynamicVector<Car> getCars() const { return this->repo.getCars(); }
	int getSize() const { return this->repo.getSize(); }
};

