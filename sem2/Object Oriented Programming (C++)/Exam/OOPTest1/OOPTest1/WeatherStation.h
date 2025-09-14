#pragma once
#include <string>
#include "DynamicVector.h"
class WeatherStation
{
	// ex: New York | Central Park | Thermometer, Barometer
private:
	std::string location;
	std::string name;
	DynamicVector<std::string> sensors;

public:
	WeatherStation();
	WeatherStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors);
	~WeatherStation();
	std::string getLocation();
	std::string getName() ;
	DynamicVector<std::string> getListOfSensors();
	void setLocation(std::string location);
	void setName(std::string name);
	void setListOfSensors(DynamicVector<std::string> ListOfSensors);
	void addSensor(std::string sensor);
	void removeSensor(std::string sensor);
	bool hasSensor(std::string sensor);
	std::string toString();
};

