#include "Car.h"

Car::Car()
{
	this->manufacturer = "";
	this->model = "";
	this->year = 0;
	this->color = "";
}

Car::Car(const std::string& manufacturer, const std::string& model, int year, const std::string& color)
	: manufacturer{ manufacturer }, model{ model }, year{ year }, color{ color }{ 
}

std::string Car::getManufacturer() const
{
	return this->manufacturer;
}

std::string Car::getModel() const
{
	return this->model;
}

int Car::getYear() const
{
	return this->year;
}

std::string Car::getColor() const
{
	return this->color;
}

std::string Car::toString()
{
	return this->manufacturer + " | " + this->model + " | " + std::to_string(this->year) + " | " + this->color;
}

void Car::setManufacturer(std::string manufacturer)
{
	this->manufacturer = manufacturer;
}

void Car::setModel(std::string model)
{
	this->model = model;
}

void Car::setYear(int year)
{
	this->year = year;
}

void Car::setColor(std::string color)
{
	this->color = color;
}

bool Car::operator==(const Car& c)
{
	return this->manufacturer == c.manufacturer && this->model == c.model && this->year == c.year && this->color == c.color;
}
