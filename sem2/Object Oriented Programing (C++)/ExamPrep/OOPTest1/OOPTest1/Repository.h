#pragma once
#include "DynamicVector.h"
#include "WeatherStation.h"
class Repository
{
private:
	DynamicVector<WeatherStation> stations;

public:
	Repository() {}
	Repository(DynamicVector<WeatherStation> stations) : stations{ stations } {}
	
	// Adds a station to the repository.
	// Throws: exception, if a station with the same name and location already exists.
	// station - WeatherStation, the station to add.
	// return void
	void addStation(WeatherStation station);
	void removeStation(std::string location);
	void updateStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors);
	WeatherStation getStation(std::string location);
	DynamicVector<WeatherStation> getStations();
	int getNumberOfStations();
	bool hasStation(std::string location);
};

