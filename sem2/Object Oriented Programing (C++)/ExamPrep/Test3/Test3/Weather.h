#pragma once
#include <string>
class Weather
{
private:
	int start;
	int end;
	int temperature;
	int precipitation;
	std::string description;
public:
	Weather(int start, int end, int temperature, int precipitation, const std::string& description)
		: start(start), end(end), temperature(temperature), precipitation(precipitation), description(description) {
	}
	int getStart() const { return start; }
	int getEnd() const { return end; }
	int getTemperature() const { return temperature; }
	int getPrecipitation() const { return precipitation; }
	const std::string& getDescription() const { return description; }

	friend std::istream& operator>>(std::istream& is, Weather& weather);
};

