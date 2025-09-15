#include "UI.h"
#include <iostream>
#include <string>



void UI::run()
{
	this->addTestData();

	while (true) {
		this->printMenu();
		std::string command;
		std::cin >> command;
		if (command == "0")
			break;
		if (command == "1") {
			try {
				this->addStation();
				std::cout << "Station added successfully!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
		else if (command == "2") {
			DynamicVector<WeatherStation> stations = this->service.getStations();
			for (auto it = stations.begin(); it != stations.end(); it++)
				std::cout << it->toString() << std::endl;
		}
		else if (command == "3") {
			std::string sensor;
			std::cout << "Sensor: ";
			std::cin.ignore();
			std::getline(std::cin, sensor);
			DynamicVector<std::string> locations = this->service.getLocationsWithSensor(sensor);
			//locations[0] = count
			for (int i = 0; i < locations.getSize(); i++)
			{
				for (int j = 1; j < locations[i].size(); j++)
					std::cout << locations[i][j];
				std::cout << " (" << locations[i][0] << "), ";
			}
			std::cout << std::endl;
		}
	}
}

void UI::printMenu()
{
	std::cout << "1. Add a new station.\n";
	std::cout << "2. Show all stations, with all their information.\n";
	std::cout << "3. Given a sensor type, show how many stations in each location have it.\n";
	std::cout << "0. Exit.\n";
}

void UI::addStation()
{
	std::string location, name;
	std::cout << "Location: ";
	std::cin.ignore();
	std::getline(std::cin, location);
	std::cout << "Name: ";
	std::getline(std::cin, name);
	std::string sensor;
	DynamicVector<std::string> sensors;
	while (true) {
		std::cout << "Sensor (0 - to stop adding): ";
		std::getline(std::cin, sensor);
		if (sensor == "0")
			break;
		sensors.add(sensor);
	}
	this->service.addStation(location, name, sensors);
}

void UI::addTestData()
{
	DynamicVector<std::string> sensors;
	sensors.add("Thermometer");
	sensors.add("Barometer");
	this->service.addStation("New York", "Central Park", sensors);
	sensors.add("Wind Vane");
	this->service.addStation("New York", "JFK Airport", sensors);
	sensors.add("Barometer");
	this->service.addStation("London", "Greenwich", sensors);
}
