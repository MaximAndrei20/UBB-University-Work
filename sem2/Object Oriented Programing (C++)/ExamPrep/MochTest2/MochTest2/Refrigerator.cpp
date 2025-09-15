#include "Refrigerator.h"

double Refrigerator::consumedElectricity()
{
	double returnValue = 0;
    this->electricityUsageClass == "A" ? returnValue = 30 * 3 : returnValue = 30 * 2;
	return returnValue;
}

std::string Refrigerator::toString()
{
	return "Refrigerator: consumedElectricity(/month): " + std::to_string(consumedElectricity()) + " hasFreezer: " + std::to_string(hasFreezer) + " electricityUsageClass: " + electricityUsageClass;
}
