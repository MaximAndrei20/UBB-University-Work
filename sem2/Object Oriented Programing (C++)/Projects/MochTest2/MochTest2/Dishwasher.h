#pragma once
#include "Apliance.h"
class Dishwasher : public Appliance
{
private:
	double consumedElectricityForOneHour;
public:
	Dishwasher(const std::string& id, double consumedElectricityForOneHour) : Appliance(id), consumedElectricityForOneHour(consumedElectricityForOneHour) {}
	double consumedElectricity() override;
	std::string toString() override;
};

