#include "Service.h"
#include <fstream>

void Service::addApliance(Appliance* a)
{
	this->appliences.push_back(a);
}

std::vector<Appliance*> Service::getApliances()
{
	return this->appliences;
}

std::vector<Appliance*> Service::getAllWithConsumedElectricityLessThan(double maxElectricity)
{
	std::vector<Appliance*> result;
	for (auto appliance : this->appliences) {
		if (appliance->consumedElectricity() < maxElectricity) {
			result.push_back(appliance);
		}
	}
	return result;
}

void Service::writeToFile(std::string fileName)
{
	std::vector<Appliance*> appliances = this->getAllWithConsumedElectricityLessThan(this->threshold);
	std::ofstream file(fileName);
	for (auto appliance : appliances)
	{
		file << appliance->toString() << std::endl;
	}
}
