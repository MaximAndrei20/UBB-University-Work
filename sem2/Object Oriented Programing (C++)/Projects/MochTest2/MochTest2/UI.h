#pragma once
#include "Service.h"
class UI
{
private:
	Service& service;
public:
	UI(Service& service) : service(service) {}
	void run();
	void addApliance();
	void getAllWithConsumedElectricityLessThan();
	void writeToFile();
	void printApliances(std::vector<Appliance*> apliences);
	static void printMenu();
};

