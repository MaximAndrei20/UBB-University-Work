#pragma once
#include <vector>
#include "Weather.h"
class Repository
{
private:
	std::vector<Weather> weathers;
public:
	std::vector<Weather> getAllWeathers() const;
	void readFromFile();
};

