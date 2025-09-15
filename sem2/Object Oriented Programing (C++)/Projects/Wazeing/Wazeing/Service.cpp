#include "Service.h"
#include <cmath>

std::vector<Report> Service::getReportsNearDriver(const Driver& driver, int radius)
{
	std::vector<Report> nearbyReports;
	for (const auto& report : repository.getReports()) {
		if (isNear(driver, report, radius)) {
			nearbyReports.push_back(report);
		}
	}
	return nearbyReports;
}

bool Service::isNear(const Driver& driver, const Report& report, int radius)
{
	double driverLat = driver.getLocation().first;
	double driverLon = driver.getLocation().second;
	double reportLat = report.getLocation().first;
	double reportLon = report.getLocation().second;
	double distance = std::sqrt(std::pow(driverLat - reportLat, 2) + std::pow(driverLon - reportLon, 2));
	return distance <= radius;
}
