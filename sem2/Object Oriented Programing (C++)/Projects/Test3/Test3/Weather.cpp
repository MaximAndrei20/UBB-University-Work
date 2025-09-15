#include "Weather.h"
#include <sstream>

std::istream& operator>>(std::istream& is, Weather& weather)
{
    // example: 6;9;10;13;foggy
	std::string line;
	if (std::getline(is, line)) {
		size_t pos = 0;
		size_t nextPos = 0;
		// Parse start
		nextPos = line.find(';', pos);
		weather.start = std::stoi(line.substr(pos, nextPos - pos));
		pos = nextPos + 1;
		// Parse end
		nextPos = line.find(';', pos);
		weather.end = std::stoi(line.substr(pos, nextPos - pos));
		pos = nextPos + 1;
		// Parse temperature
		nextPos = line.find(';', pos);
		weather.temperature = std::stoi(line.substr(pos, nextPos - pos));
		pos = nextPos + 1;
		// Parse precipitation
		nextPos = line.find(';', pos);
		weather.precipitation = std::stoi(line.substr(pos, nextPos - pos));
		pos = nextPos + 1;
		// Parse description
		weather.description = line.substr(pos);
	}
	return is;
}
