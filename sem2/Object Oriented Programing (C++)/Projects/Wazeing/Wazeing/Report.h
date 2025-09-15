#pragma once
#include <string>
#include <utility>
class Report
{
private:
	std::string description;
	std::string reporter; // name of the driver
	std::pair<double, double> location; // latitude, longitude
	bool validated;
	int nrOfValidations;
public:
	Report(const std::string& description, const std::string& reporter, const std::pair<double, double>& location, bool validated = false)
		: description(description), reporter(reporter), location(location), validated(validated) {
		nrOfValidations = validated ? 10 : 0;
	}
	const std::string& getDescription() const { return description; }
	const std::string& getReporter() const { return reporter; }
	const std::pair<double, double>& getLocation() const { return location; }
	bool isValidated() const { return validated; }
	void setValidated(bool newValidated) { validated = newValidated; }

	int getNrOfValidations() const { return nrOfValidations; }
	void incrementValidations() { nrOfValidations++; 
	if (nrOfValidations >= 2) {
		validated = true; 
	}
	}
};

