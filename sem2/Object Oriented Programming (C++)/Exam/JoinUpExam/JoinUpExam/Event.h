#pragma once
#include <string>
#include <utility>
class Event
{
private:
	std::string organiser;
	std::string name;
	std::string description;
	std::pair<double, double> location; // latitude, longitude
	std::string date; 
public:
	Event(std::string organiser, std::string name, std::string description, std::pair<double, double> location, std::string date)
		: organiser(std::move(organiser)), name(std::move(name)), description(std::move(description)), location(location), date(date) {
	}
	Event() : organiser(""), name(""), description(""), location({ 0.0, 0.0 }), date("") {
	}
	const std::string& getOrganiser() const { return organiser; }
	const std::string& getName() const { return name; }
	const std::string& getDescription() const { return description; }
	const std::pair<double, double>& getLocation() const { return location; }
	void setOrganiser(const std::string& newOrganiser) { organiser = newOrganiser; }
	void setName(const std::string& newName) { name = newName; }
	void setDescription(const std::string& newDescription) { description = newDescription; }
	void setLocation(const std::pair<double, double>& newLocation) { location = newLocation; }
	const std::string& getDate() const { return date; }
	void setDate(const std::string& newDate) { date = newDate; }
};

