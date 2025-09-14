#include "Dishwasher.h"

double Dishwasher::consumedElectricity()
{
	// per month
	return consumedElectricityForOneHour * 20;
}

std::string Dishwasher::toString()  
{  
	return "Dishwasher: consumedElectricityForOneHour: " + std::to_string(consumedElectricityForOneHour) + " consumedElectricity(/month): " + std::to_string(consumedElectricity()) + "\n";
}
