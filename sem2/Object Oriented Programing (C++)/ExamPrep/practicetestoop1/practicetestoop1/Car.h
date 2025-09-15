#pragma once
#include <string>
class Car
{
private:
	std::string manufacturer;
	std::string model;
	int year;
	std::string color;

public:
	Car();
	Car(const std::string& manufacturer, const std::string& model, int year, const std::string& color);
	std::string getManufacturer() const;
	std::string getModel() const;
	int getYear() const;
	std::string getColor() const;
	std::string toString();
	void setManufacturer(std::string manufacturer);
	void setModel(std::string model);
	void setYear(int year);
	void setColor(std::string color);
	bool operator==(const Car& c);
};

