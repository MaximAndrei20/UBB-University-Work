#include "Repo.h"
#include <algorithm>
#include <iterator>
#include <fstream>

void Repo::addEventToData(const Event e)
{
	events.push_back(e);
}
void Repo::deleteEvent(const std::string title)
{
	for (auto it = events.begin(); it != events.end(); ++it)
	{
		if (it->getTitle() == title)
		{
			events.erase(it);
			break;
		}
	}
}
std::vector<Event> Repo::getEvents() const
{
	return events;
}
std::vector<Event> Repo::getEventsForMonth(int month)
{
	std::vector<Event> eventsForMonth;
	std::copy_if(this->events.begin(), this->events.end(), std::back_inserter(eventsForMonth),
		[month](const Event& event) {
			std::string time = std::string(event.getDateTime());
			return (month == 0 || std::stoi(time.substr(5, 2)) == month);
		});

	return eventsForMonth;
}
int Repo::getNumberOfEvents() const
{
	return events.size();
}

void Repo::loadInitialData(const std::string& fileName)
{
	std::fstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + fileName);
	}
	Event event;
	while(file >> event)
	{
		events.push_back(event);
	}
}

void Repo::writeToFile(std::string filename)
{
	std::ofstream file(filename);
	for (auto event : events) {
		file << event << "\n";
	}
}
