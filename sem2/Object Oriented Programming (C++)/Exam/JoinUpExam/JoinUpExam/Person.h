#pragma once
#include <string>
#include <utility>
class Person
{
private:
	std::string name;
	std::pair<double, double> location; // latitude, longitude
	bool organiser;
public:
	Person(std::string name, std::pair<double, double> location, bool organiser)
		: name(std::move(name)), location(location), organiser(organiser) {
	}
	const std::string& getName() const { return name; }
	const std::pair<double, double>& getLocation() const { return location; }
	bool isOrganiser() const { return organiser; }
	void setName(const std::string& newName) { name = newName; }
	void setLocation(const std::pair<double, double>& newLocation) { location = newLocation; }
	void setOrganiser(bool newOrganiser) { organiser = newOrganiser; }

};

