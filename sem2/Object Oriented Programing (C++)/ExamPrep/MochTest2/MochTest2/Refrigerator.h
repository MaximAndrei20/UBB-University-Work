#pragma once
#include "Apliance.h"
class Refrigerator : public Appliance
{
public:
	bool hasFreezer;
private:
	std::string electricityUsageClass;

public:
	Refrigerator(const std::string& id, bool hasFreezer, const std::string& electricityUsageClass)
		: Appliance(id), hasFreezer(hasFreezer), electricityUsageClass(electricityUsageClass) {
	}
	double consumedElectricity() override;
	std::string toString() override;
};

