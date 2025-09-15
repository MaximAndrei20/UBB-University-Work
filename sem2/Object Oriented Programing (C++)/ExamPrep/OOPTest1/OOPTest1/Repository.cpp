#include "Repository.h"
#include <exception>

void Repository::addStation(WeatherStation station)
{
	//if station with same name and location already exists, do not add it
	for (int i = 0; i < this->stations.getSize(); i++)
		if (this->stations[i].getLocation() == station.getLocation()
			&& this->stations[i].getName() == station.getName())
			throw std::exception("Station already exists!");

	this->stations.add(station);
}

void Repository::removeStation(std::string location)
{
	for (int i = 0; i < this->stations.getSize(); i++)
		if (this->stations[i].getLocation() == location)
		{
			this->stations.remove(i);
			return;
		}
}

DynamicVector<WeatherStation> Repository::getStations()
{
	return this->stations;
}
