#include "UI.h"
#include <iostream>
#include "Dishwasher.h"
#include "Refrigerator.h"


void UI::run()
{
	while (true) {
		this->printMenu();
		std::string option;
		std::cin >> option;
		if (option == "1") {
			this->addApliance();
		}
		else if (option == "2") {
			this->printApliances(this->service.getApliances());
		}
		else if (option == "3") {
			this->getAllWithConsumedElectricityLessThan();
		}
		else if (option == "4") {
			this->writeToFile();
		}
		else if (option == "0") {
			break;
		}
		else {
			std::cout << "Invalid option. Try again." << std::endl;
		}
	}
}

void UI::addApliance()
{
	std::cout << "Enter appliance type (Refrigerator - 1/Dishwasher - 2): ";
	std::string type;
	std::cin >> type;
	if (type == "1") {
		std::string id;
		std::cout << "Enter appliance ID: ";
		std::cin >> id;
		bool hasFreezer;
		std::cout << "Does it have a freezer? (1 - Yes, 0 - No): ";
		std::cin >> hasFreezer;
		std::string electricityUsageClass;
		std::cout << "Enter electricity usage class: ";
		std::cin >> electricityUsageClass;
		this->service.addApliance(new Refrigerator(id, hasFreezer, electricityUsageClass));
	}
	else if (type == "2") {
		double consumedElectricityForOneHour;
		std::string id;
		std::cout << "Enter appliance ID: ";
		std::cin >> id;
		std::cout << "Enter consumed electricity for one hour: ";
		std::cin >> consumedElectricityForOneHour;
		this->service.addApliance(new Dishwasher(id, consumedElectricityForOneHour));
	}
	else {
		std::cout << "Invalid appliance type." << std::endl;
	}
}

void UI::getAllWithConsumedElectricityLessThan()
{
	std::cout << "Enter max electricity consumption: ";
	double maxElectricity;
	std::cin >> maxElectricity;
	auto appliances = this->service.getAllWithConsumedElectricityLessThan(maxElectricity);
	this->printApliances(appliances);
}

void UI::writeToFile()
{
	std::string fileName;
	double maxElectricity;
	std::cout << "Enter file name: ";
	std::cin >> fileName;
	std::cout << "Enter max electricity consumption: ";
	std::cin >> maxElectricity;

	this->service.threshold = maxElectricity;
	this->service.writeToFile(fileName);
	std::cout << "Data saved to file: " << fileName << std::endl;

}

void UI::printApliances(std::vector<Appliance*> apliences)
{
	for (auto appliance : apliences) {
		std::cout << appliance->toString() << std::endl;
	}
}

void UI::printMenu()
{
	std::cout << "1. Add Apliance" << std::endl;
	std::cout << "2. Display all appliances" << std::endl;
	std::cout << "3. Display inneficient appliances (consume > 100KW)" << std::endl;
	std::cout << "4. Save to file quality appliances" << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << "Choose an option: ";
}
