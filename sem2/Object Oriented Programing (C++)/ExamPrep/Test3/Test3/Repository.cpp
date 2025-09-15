#include "Repository.h"
#include <fstream>

std::vector<Weather> Repository::getAllWeathers() const
{
    return this->weathers;
}

void Repository::readFromFile()
{
	std::ifstream file("data.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file data.txt");
	}

	Weather weather(0, 0, 0, 0, "");
	while (file >> weather) {
		this->weathers.push_back(weather);
	}

	file.close();
}
