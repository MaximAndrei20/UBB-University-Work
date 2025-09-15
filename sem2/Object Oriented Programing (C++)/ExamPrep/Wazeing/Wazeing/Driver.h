#pragma once
#include <utility>
#include <string>
class Driver
{
private:
	std::string name;
	std::string status; // baby/grown-up/knight
	std::pair<double, double> location; // latitude, longitude
	int score; // 0-10 baby 10-15 grown-up 15+ knight
public:
	Driver(const std::string& name, const std::string& status, const std::pair<double, double>& location, int score)
		: name(name), status(status), location(location), score(score) {
	}
	const std::string& getName() const { return name; }
	const std::string& getStatus() const { return status; }
	const std::pair<double, double>& getLocation() const { return location; }
	int getScore() const { return score; }
	void setStatus(const std::string& newStatus) { status = newStatus; }
	void setLocation(const std::pair<double, double>& newLocation) { location = newLocation; }
	void setScore(int newScore) { 
		score = newScore; 
		if (score < 10) {
			status = "baby";
		}
		else if (score < 15) {
			status = "grown-up";
		}
		else {
			status = "knight";
		}
	}
};

