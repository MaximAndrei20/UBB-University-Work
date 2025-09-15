#pragma once
#include "Apliance.h"
#include <vector>
class Service
{
private:
	std::vector<Appliance*> appliences;
public:
	double threshold = 0;
	Service() = default;
	~Service() {
		for (auto apliance : appliences) {
			delete apliance;
		}
	}
	void addApliance(Appliance* a);
	std::vector<Appliance*> getApliances();
	std::vector<Appliance*> getAllWithConsumedElectricityLessThan(double maxElectricity);
	void writeToFile(std::string fileName);

};

