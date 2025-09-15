#include "WeatherStation.h"

WeatherStation::WeatherStation()
{
	this->location = "";
	this->name = "";
	this->sensors = DynamicVector<std::string>();
}

WeatherStation::WeatherStation(std::string location, std::string name, DynamicVector<std::string> ListOfSensors)
{ 
	this->location = location;
	this->name = name;
	this->sensors = ListOfSensors;
}

WeatherStation::~WeatherStation()
{
}

std::string WeatherStation::getLocation()
{
	return this->location;
}

std::string WeatherStation::getName()
{
	return this->name;
}

DynamicVector<std::string> WeatherStation::getListOfSensors()
{
	return this->sensors;
}

void WeatherStation::setLocation(std::string location)
{
	this->location = location;
}

void WeatherStation::setName(std::string name)
{
	this->name = name;
}

void WeatherStation::setListOfSensors(DynamicVector<std::string> ListOfSensors)
{
	this->sensors = ListOfSensors;
}

void WeatherStation::addSensor(std::string sensor)
{
	this->sensors.add(sensor);
}

void WeatherStation::removeSensor(std::string sensor)
{
	for (int i = 0; i < this->sensors.getSize(); i++)
		if (this->sensors[i] == sensor)
		{
			this->sensors.remove(i);
			return;
		}
}

bool WeatherStation::hasSensor(std::string sensor)
{
	for (int i = 0; i < this->sensors.getSize(); i++)
		if (this->sensors[i] == sensor)
			return true;
	return false;
}

std::string WeatherStation::toString()
{
	// format ex: New York | Central Park | Thermometer, Barometer
	std::string str = this->location + " | " + this->name + " | ";
	for (int i = 0; i < this->sensors.getSize(); i++)
	{
		str += this->sensors[i];
		if (i < this->sensors.getSize() - 1)
			str += ", ";
	}
	return str;
}

