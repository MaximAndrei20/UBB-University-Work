#pragma once
#include <vector>
#include <string>
#include "Driver.h"
#include "Report.h"
class Repository
{
private:
	std::vector<Driver> drivers; 
	std::vector<Report> reports;
	std::string driversFile;
	std::string reportsFile;

public:
	Repository(std::string driversFile, std::string reportsFile);

	void loadDrivers();
	void loadReports();

	void saveDrivers();
	void saveReports();

	std::vector<Driver>& getDrivers() { return drivers; }
	std::vector<Report>& getReports() { return reports; }
};

