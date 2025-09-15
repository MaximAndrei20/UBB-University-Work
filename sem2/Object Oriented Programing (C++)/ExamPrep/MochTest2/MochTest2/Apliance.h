#pragma once
#include <string>
class Appliance
{
protected:
	std::string id;

public:
	virtual ~Appliance() = default;
	Appliance(std::string id) : id(id) {}
	virtual double consumedElectricity() = 0;
	virtual std::string toString() {	return "Apliance ID: " + id;	}
};

