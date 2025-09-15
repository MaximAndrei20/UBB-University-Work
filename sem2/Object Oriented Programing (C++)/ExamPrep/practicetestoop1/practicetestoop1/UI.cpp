#include "UI.h"
#include <iostream>
#include <algorithm>
void UI::run()
{
	this->addTestData();

	while (true) {
		this->printMenu();

		int command = -1;
		std::cin >> command;
		std::cin.ignore();
		if (command == 0)
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Invalid command.\n";
			continue;
		}
		if (command == 5)
			break;
		if (command == 1)
		{
			std::string manufacturer, model, color;
			int year;
			std::cout << "Manufacturer: ";
			std::getline(std::cin, manufacturer);
			std::cout << "Model: ";
			std::getline(std::cin, model);
			std::cout << "Year: ";
			std::cin >> year;
			std::cin.ignore();
			std::cout << "Color: ";
			std::getline(std::cin, color);
			bool rez = this->service.addCar(manufacturer, model, year, color);
			if (rez == false)
				std::cout << "Car already exists.\n";
			else {
				std::cout << "Car added successfully.\n";
			}
		}
		if (command == 2)
		{
			std::string model;
			int year;
			std::cout << "Model: ";
			std::getline(std::cin, model);
			std::cout << "Year: ";
			std::cin >> year;
			std::cin.ignore();
			bool rez = this->service.removeCar(model, year);
			if (rez == false)
				std::cout << "Car does not exist.\n";
			else {
				std::cout << "Car removed successfully.\n";
			}
		}
		if (command == 3)
		{
			DynamicVector<Car> cars = this->service.getCars();
			//sort by manufacturer and model
			for (int i = 0; i < cars.getSize(); i++)
				for (int j = i + 1; j < cars.getSize(); j++)
					if (this->comparator(cars[i], cars[j]))
						std::swap(cars[i], cars[j]);
			for (int i = 0; i < cars.getSize(); i++)
			{
				Car c = cars[i];
				std::cout << c.toString() << "\n";
			}
		}
		if (command == 4)
		{
			DynamicVector<Car> cars = this->service.getCars();
			//sort by color
			for (int i = 0; i < cars.getSize(); i++)
				for (int j = i + 1; j < cars.getSize(); j++)
					if (cars[i].getColor() > cars[j].getColor())
						std::swap(cars[i], cars[j]);
			for (int i = 0; i < cars.getSize(); i++)
			{
				Car c = cars[i];
				if (c.getYear() < 2025 - 45)
					std::cout << c.toString() << "\n";
			}
		}

	}
}

void UI::printMenu()
{
	std::cout << "1. Add car.\n";
	std::cout << "2. Remove car.\n";
	std::cout << "3. Show all cars. (sorted by manufacturer and model)\n";
	std::cout << "4. Show all vintage cars. (those havin +45 years (sorted by color))\n";
	std::cout << "5. Exit.\n";
}

void UI::addTestData()
{
	this->service.addCar("Fiat", "Bravo", 2007, "red");
	this->service.addCar("Fiat", "Idea", 2003, "black");
	this->service.addCar("Audi", "A5", 2007, "blue");
	this->service.addCar("BMW", "Coupe", 2013, "pink");
	this->service.addCar("Ford", "Fiesta", 1976, "yellow");
}

bool UI::comparator(const Car& c1, const Car& c2)
{
	if (c1.getManufacturer() == c2.getManufacturer())
		return c1.getModel() > c2.getModel();
	return c1.getManufacturer() > c2.getManufacturer();
}
