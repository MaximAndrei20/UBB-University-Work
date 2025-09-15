#include "Repository.h"
#include <fstream>
#include <sstream>

Repository::Repository(std::string driversFile, std::string reportsFile) : driversFile(driversFile), reportsFile(reportsFile)
{
	loadDrivers();
	loadReports();
}

void Repository::loadDrivers()
{
	// format: name,status,latitude,longitude,score
	std::ifstream file(driversFile);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open drivers file: " + driversFile);
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string name,status,lat, lon, score;
		if (std::getline(iss, name, ',') &&
			std::getline(iss, status, ',') &&
			std::getline(iss, lat, ',') &&
			std::getline(iss, lon, ',') &&
			std::getline(iss, score)) {
			double latitude = std::stod(lat);
			double longitude = std::stod(lon);
			int scoreValue = std::stoi(score);
			drivers.emplace_back(name, status, std::make_pair(latitude, longitude), scoreValue);
		}
	}
}

void Repository::loadReports()
{
	// format: description|reporter|latitude|longitude|validated
	std::ifstream file(reportsFile);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open reports file: " + reportsFile);
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string description, reporter, lat, lon, validatedStr;
		if (std::getline(iss, description, '|') &&
			std::getline(iss, reporter, '|') &&
			std::getline(iss, lat, '|') &&
			std::getline(iss, lon, '|') &&
			std::getline(iss, validatedStr)) {
			double latitude = std::stod(lat);
			double longitude = std::stod(lon);
			bool validated = (validatedStr == "true");
			reports.emplace_back(description, reporter, std::make_pair(latitude, longitude), validated);
		}
	}
}

void Repository::saveDrivers()
{
	std::ofstream file(driversFile);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open drivers file for writing: " + driversFile);
	}
	for (const auto& driver : drivers) {
		file << driver.getName() << ","
			<< driver.getStatus() << ","
			<< driver.getLocation().first << ","
			<< driver.getLocation().second << ","
			<< driver.getScore() << "\n";
	}
}

void Repository::saveReports()
{
	std::ofstream file(reportsFile);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open reports file for writing: " + reportsFile);
	}
	for (const auto& report : reports) {
		file << report.getDescription() << "|"
			<< report.getReporter() << "|"
			<< report.getLocation().first << "|"
			<< report.getLocation().second << "|"
			<< (report.isValidated() ? "true" : "false") << "\n";
	}
}
