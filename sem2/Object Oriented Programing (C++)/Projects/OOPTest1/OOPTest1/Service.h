#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;

public:
	Service(const Repository& repo);

	// Adds a station to the repository.
	// Throws: exception, if a station with the same name and location already exists.
	// location - string, the location of the station.
	// name - string, the name of the station.
	// ListOfSensors - DynamicVector<string>, the list of sensors of the station.
	//void addStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors);
	void addStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors);
	void removeStation(std::string location);
	void updateStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors);
	WeatherStation getStation(std::string location);
	DynamicVector<WeatherStation> getStations();
	// Returns the locations of the stations that have a given sensor.
	// sensor - string, the sensor to search for.
	// parses through all the stations and checks if the sensor is in the list of sensors
	// returns a DynamicVector<string> with the locations of the stations that have the sensor.
	// where string[0] is count of stations with sensor
	DynamicVector<std::string > getLocationsWithSensor(std::string sensor);
	int getNumberOfStations();
	bool hasStation(std::string location);
};

