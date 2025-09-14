#include "Service.h"
#include <vector>
Service::Service(const Repository& repo)
{
	this->repo = repo;
}

void Service::addStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors)
{
	WeatherStation station{ location, name, ListOfSensors };
	this->repo.addStation(station);
}

DynamicVector<WeatherStation> Service::getStations()
{
	return this->repo.getStations();
}

DynamicVector<std::string> Service::getLocationsWithSensor(std::string sensor)
{
	DynamicVector<WeatherStation> stations = this->repo.getStations();
	DynamicVector<std::string> locations;
	std::vector<int> counts;
	for (int i = 0; i <= stations.getSize(); i++)
	{
		WeatherStation station = stations[i];
		DynamicVector<std::string> sensors = station.getListOfSensors();
		if (sensors.contains(sensor))
		{
			if (locations.contains(station.getLocation()))
			{
				int index = locations.find(station.getLocation());
				counts[index]++;
			}
			else
			{
				locations.add(station.getLocation());
				counts.push_back(1);
			}
		}
	}
	DynamicVector<std::string> locations2;
	for (int i = 0; i < locations.getSize(); i++)
	{
		std::string count = std::to_string(counts[i]);
		count += locations[i];
		locations2.add(count);
	}return locations2;
}
