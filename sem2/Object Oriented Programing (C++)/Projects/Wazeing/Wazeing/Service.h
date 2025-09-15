#pragma once
#include "Subject.h"
#include <vector>
#include "Repository.h"
class Service :
    public Subject
{
private:
	Repository& repository;
public:
	Service(Repository& repo) : repository(repo) {}
	std::vector<Driver>& getDrivers() {
		return repository.getDrivers();
	}
	std::vector<Report>& getReports() {
		return repository.getReports();
	}
	std::vector<Report> getReportsNearDriver(const Driver& driver, int radius);
	bool isNear(const Driver& driver, const Report& report, int radius);
	void validateReport(Report& report, Driver& driver) {
		// get driver of the report
		std::string reporterName = report.getReporter();

		// find the driver in the repository
		auto& drivers = repository.getDrivers();
		auto it = std::find_if(drivers.begin(), drivers.end(),
			[&reporterName](const Driver& d) { return d.getName() == reporterName; });
		if (it == drivers.end()) {
			return;
		}
		Driver& reporter = *it;
		bool changed = false;
		if (!report.isValidated())
			changed = true;
		report.incrementValidations();
		if (!report.isValidated())
			changed = false;
		if (changed) {
			reporter.setScore(reporter.getScore()+1);
		}
	}
};

